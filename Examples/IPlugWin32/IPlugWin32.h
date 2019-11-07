#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "resource.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

using namespace iplug;

class IPlugWin32 : public Plugin
{
public:
  IPlugWin32(const InstanceInfo& info);
  void* OpenWindow(void* pParent) override;
  void CloseWindow() override;
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;

  BOOL Callback(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
  void OnParamChangeUI(int paramIdx, EParamSource source) override;
  void OnUIOpen() override;
private:
  void SetStaticText(int id, int paramIdx);
  HWND mControlHWND;
};
