echo off

CALL "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_x64

IF "%1"=="" (
ECHO Error - specify a backend skia or cairo as the first argument
EXIT /b 1
) 

IF "%1"=="skia" (
SET BACKENDS="skia-backend"
SET SKIA_DIR=%CD:\=\\%\\..\\Build\\src\\skia
) ELSE (
SET BACKENDS="cairo-backend"
)

IF "%2"=="debug" (
SET LIBPATH=%CD:\=\\%\\..\\Build\\win\\x64\\Debug
SET BUILD_ARG
SET OUTPATH="target\debug"
) ELSE (
SET LIBPATH=%CD:\=\\%\\..\\Build\\win\\x64\\Release
SET BUILD_ARG="--release"
SET OUTPATH="target\release"
)

SET SKIA_LIB_DIR=%LIBPATH%

CD ..\Build\src\resvg\capi
IF EXIST .cargo RMDIR /q /s .cargo
MKDIR .cargo
ECHO [build] >> .cargo/config

IF %BACKENDS%=="skia-backend" (
ECHO rustflags = ["-C", "link-arg=/LIBPATH:%LIBPATH%", "-C", "target-feature=+crt-static", "-C", "link-arg=User32.lib"] >> .cargo/config
) ELSE (
ECHO rustflags = ["-C", "link-arg=/LIBPATH:%LIBPATH%", "-C", "link-arg=pixman.lib", "-C", "link-arg=freetype.lib", "-C", "link-arg=zlib.lib", "-C", "link-arg=Msimg32.lib", "-C", "link-arg=gdi32.lib", "-C", "link-arg=User32.lib", "-C", "target-feature=+crt-static"] >> .cargo/config
)
cargo build %BUILD_ARG% --features=%BACKENDS%
CD .. 

if EXIST %OUTPATH%\resvg.lib (
COPY %OUTPATH%\resvg.lib %LIBPATH%
)

CD ..\..\..\IGraphics

