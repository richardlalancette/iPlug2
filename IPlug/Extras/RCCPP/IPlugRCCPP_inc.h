#ifdef IPLUG_RCCPP
#include "config.h"

#include "RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "IPlugRCCPP_SystemTable.h"
#include "RuntimeObjectSystem/IObject.h"

RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/IPlugParameter", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/IPlugAPIBase", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/IPlugPluginBase", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/IPlugProcessor", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/APP/IPlugAPP", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/IGraphicsEditorDelegate", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/IGraphics", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/IControl", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Controls/IControls", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Controls/IPopupMenuControl", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Controls/ITextEntryControl", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../Dependencies/IPlug/RTAudio/RtAudio", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../Dependencies/IPlug/RTMidi/RtMidi", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/IPlugTimer", ".cpp");
#if defined OS_WIN
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/IPlugPaths", ".cpp");
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Platforms/IGraphicsWin", ".cpp");
#elif defined OS_MAC
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IPlug/IPlugPaths", ".mm");
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Platforms/IGraphicsMac", ".mm");
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Platforms/IGraphicsMac_view", ".mm");
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Platforms/IGraphicsCoreText", ".mm");
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Platforms/IGraphicsCoreText", ".mm");
#if defined IGRAPHICS_NANOVG
  RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../IGraphics/Drawing/IGraphicsNanoVG_src", ".m");
#endif
#elif defined OS_LINUX
  #error "Not yet implemented"
#endif

#include "RuntimeObjectSystem/RuntimeLinkLibrary.h"

#if defined OS_WIN
  RUNTIME_COMPILER_LINKLIBRARY("Gdi32.lib");
  RUNTIME_COMPILER_LINKLIBRARY("opengl32.lib");
  RUNTIME_COMPILER_LINKLIBRARY("User32.lib");
  RUNTIME_COMPILER_LINKLIBRARY("Shell32.lib");
  RUNTIME_COMPILER_LINKLIBRARY("Comdlg32.lib");
  RUNTIME_COMPILER_LINKLIBRARY("Shlwapi.lib");
  RUNTIME_COMPILER_LINKLIBRARY("Ole32.lib");
  RUNTIME_COMPILER_LINKLIBRARY("Comctl32.lib");
  RUNTIME_COMPILER_LINKLIBRARY("Wininet.lib");
#elif defined OS_MAC
  RUNTIME_COMPILER_LINKLIBRARY("-framework Cocoa -framework Carbon -framework CoreFoundation -framework CoreData -framework Foundation -framework CoreServices -framework Metal -framework MetalKit -framework QuartzCore -framework WebKit -framework OpenGL");
  #if defined IGRAPHICS_SKIA
  RUNTIME_COMPILER_LINKLIBRARY("-lskia");
  #endif
#elif defined OS_LINUX
  #error "Not yet implemented"
#endif

struct IPLUGRCCPP : IObject
{
  void Init(bool isFirstInit) override
  {
    if (!isFirstInit)
    {
      IPlugAPP* pPlug = reinterpret_cast<IPlugAPP*>(PerModuleInterface::g_pSystemTable->pPlug);
      pPlug->CloseWindow();
      pPlug = new PLUG_CLASS_NAME(InstanceInfo{ PerModuleInterface::g_pSystemTable->pAppHost });
      pPlug->OpenWindow(PerModuleInterface::g_pSystemTable->pParentWindow);
    }
  }
};

#define ENABLE_RCCPP REGISTERSINGLETON(IPLUGRCCPP, true)

#endif //IPLUG_RCCPP
