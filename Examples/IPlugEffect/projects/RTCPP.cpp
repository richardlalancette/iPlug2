
#include "RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "RuntimeObjectSystem/IObject.h"
#include "IPlugRCCPP_IUpdateable.h"
#include "IPlugRCCPP_InterfaceIds.h"
#include "IPlugLogger.h"
#include "IPlugEffect.h"
#include "IControl.h"

using namespace iplug;
using namespace igraphics;

class RuntimeObject01 : public TInterface<IID_IUPDATEABLE, IUpdateable>
{
public:
  void OnCompile(void* pPlug) override
  {
    IPlugEffect* pIPlug = static_cast<IPlugEffect*>(pPlug);
    IGraphics* pGraphics = pIPlug->GetUI();

    IPanelControl* pBGControl = dynamic_cast<IPanelControl*>(pGraphics->GetBackgroundControl());
    
    //pBGControl->SetPattern(IColor::GetRandomColor());
    //pBGControl->SetPattern(COLOR_YELLOW);
    pBGControl->SetPattern(COLOR_RED);
  }

  void Update(float deltaTime) override
  {
    //DBGMSG("update called\n");
     
  }
};

REGISTERCLASS(RuntimeObject01);

