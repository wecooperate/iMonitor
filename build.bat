@ECHO OFF & PUSHD %~DP0 & TITLE iMonitor Build Command

If "%QT_DIR32%"=="" (
Echo QT_DIR32 is not set, use the default value: "D:\Qt\Qt5.12.11\5.12.11\msvc2017\lib\cmake\Qt5"
Set QT_DIR32=D:\Qt\Qt5.12.11\5.12.11\msvc2017\lib\cmake\Qt5
)

If "%QT_DIR64%"=="" (
Echo QT_DIR64 is not set, use the default value: "D:\Qt\Qt5.12.11\5.12.11\msvc2017_64\lib\cmake\Qt5"
Set QT_DIR64=D:\Qt\Qt5.12.11\5.12.11\msvc2017_64\lib\cmake\Qt5
)

:Menu
Echo.&Echo  1.GenerateSolution
Echo.&Echo  2.BuildDebug
Echo.&Echo  3.BuildRelease
Echo.&Echo  4.Windeployqt
Echo.&Echo  5.Format
Echo.&Echo.

set /p a=Input Number:
If Not "%a%"=="" Set a=%a:~0,1%
If "%a%"=="1" Goto GenerateSolution
If "%a%"=="2" Goto BuildDebug
If "%a%"=="3" Goto BuildRelease
If "%a%"=="4" Goto Windeployqt
If "%a%"=="5" Goto Format
Exit

:GenerateSolution
Set QT_DIR=%QT_DIR64%
cmake %vcpkg_param% -G "Visual Studio 16 2019" -A "x64" -T "v142" CMakeLists.txt -B build/64 -DQT_ENABLE_TRANSLATION=1

Set QT_DIR=%QT_DIR32%
cmake %vcpkg_param% -G "Visual Studio 16 2019" -A "Win32" -T "v142" CMakeLists.txt -B build/32 -DQT_ENABLE_TRANSLATION=1
Goto Menu

:BuildDebug
cmake --build build/64 --config Debug
cmake --build build/32 --config Debug
Goto Menu

:BuildRelease
cmake --build build/64 --config Release
cmake --build build/32 --config Release
Goto Menu

:Windeployqt
windeployqt.exe bin\64\iMonitor.exe
windeployqt.exe bin\32\iMonitor.exe
Goto Menu

:Format
node tools/format.js
Goto Menu
