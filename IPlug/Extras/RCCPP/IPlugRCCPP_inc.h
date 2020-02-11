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
#include "RuntimeObjectSystem/RuntimeObjectSystem.h"

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
    else
    {
      RuntimeObjectSystem* pRuntimeObjectSystem = reinterpret_cast<RuntimeObjectSystem*>(PerModuleInterface::g_pRuntimeObjectSystem); \
      FileSystemUtils::Path basePath = pRuntimeObjectSystem->FindFile(GetConstructor()->GetFileName()).ParentPath();
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(basePath).c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(basePath/"resources").c_str());
      FileSystemUtils::Path iPlugDir = basePath.ParentPath().ParentPath();
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IPlug").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IGraphics").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IGraphics" / "Platforms").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IGraphics" / "Controls").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IGraphics" / "Drawing").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IPlug").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IPlug" / "APP").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IPlug" / "Extras").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "IPlug" / "Extras" / "RCCPP").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "WDL").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IPlug" / "RTAudio").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IPlug" / "RTMidi").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IGraphics" / "STB").c_str());
#if defined IGRAPHICS_NANOVG
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IGraphics" / "NanoVG" / "src").c_str());
#elif defined IGRAPHICS_SKIA
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia" / "include" / "core").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia" / "include" / "effects").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia" / "include" / "config").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia" / "include" / "utils").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia" / "include" / "utils" / "mac").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia" / "include" / "gpu").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "skia" / "experimental" / "svg" / "model").c_str());
#endif
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IGraphics" / "NanoSVG" / "src").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "src" / "rccpp" / "Aurora").c_str());
#ifdef OS_MAC
#ifdef IGRAPHICS_NANOVG
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IGraphics" / "MetalNanoVG" / "src").c_str());
#endif
      pRuntimeObjectSystem->AddLibraryDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "Build" / "mac" / "lib").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "WDL" / "swell").c_str());
      pRuntimeObjectSystem->SetAdditionalCompileOptions("-DIPLUG_RCCPP -DIPLUG_EDITOR -DIPLUG_DSP -DIGRAPHICS_SKIA -DIGRAPHICS_METAL -DAPP_API -std=c++14 -Wno-deprecated-declarations");
#elif defined OS_WIN
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IGraphics" / "glad_GL2" / "include").c_str());
      pRuntimeObjectSystem->AddIncludeDir(FileSystemUtils::Path(iPlugDir / "Dependencies" / "IGraphics" / "glad_GL2" / "src").c_str());
      pRuntimeObjectSystem->SetAdditionalCompileOptions("-DIPLUG_RCCPP -DIPLUG_EDITOR -DIPLUG_DSP -DIGRAPHICS_NANOVG -DIGRAPHICS_GL2 -DAPP_API -DNOMINMAX /wd4068 /std:c++14");
#endif
    }
  }
};

#define ENABLE_RCCPP REGISTERSINGLETON(IPLUGRCCPP, true)

#endif //IPLUG_RCCPP
