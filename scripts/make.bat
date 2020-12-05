call project_settings.bat

if exist "output" start /wait cmd /c rmdir output /s /q
mkdir "output"

REM Compile all
set avr_tools="%ARDUINO_DIR%\hardware\tools\avr\bin"
if not exist "output\build" mkdir "output\build"
if not exist "output\atmega2560" mkdir "output\atmega2560"

for %%a in (%proj_src_files%) do (
   start /wait cmd /c compile.bat %%a
)

setlocal enabledelayedexpansion
set proj_obj_files=
for  %%a in (%proj_src_files%) do (
   set proj_obj_files=%%a.o !proj_obj_files!
)

REM Link all
cd output/build
%avr_tools%\avr-ar -r "../atmega2560/lib%proj_name%.a" %proj_obj_files%
cd ../
start /wait cmd /c rmdir build /s /q

REM Create library
if exist %proj_name% start /wait cmd /c rmdir %proj_name% /s /q
mkdir %proj_name%

cd %proj_name%
mkdir src
for %%a in (%proj_public_files%) do (
   copy ..\..\..\src\%%a src\
)

Xcopy /E /I "../atmega2560" "src/atmega2560"
Xcopy /E /I "../../../examples" "examples"
copy ..\..\precomp.library.properties library.properties
copy ..\..\..\keywords.txt keywords.txt

cd ..
start /wait cmd /c rmdir atmega2560 /s /q
cd ..
