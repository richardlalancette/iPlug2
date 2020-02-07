#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "IPlugRCCPP_InterfaceIds.h"
#include "RuntimeObjectSystem/IObject.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

class IPlugEffect : public Plugin
  #if IPLUG_RCCPP
  , public TInterface<IID_IPLUGEFFECT, IObject>
  #endif
{
public:
#if IPLUG_RCCPP
  IPlugEffect(); // for RCCPP
#endif
  IPlugEffect(const InstanceInfo& info);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif

#if IPLUG_RCCPP
  virtual void Init( bool isFirstInit );
  virtual PerTypeObjectId GetPerTypeId() const { return 0; };
  virtual IObjectConstructor* GetConstructor() const { return NULL; };
  virtual const char* GetTypeName() const { return NULL; };
#endif
};
