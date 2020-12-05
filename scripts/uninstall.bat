call project_settings.bat
set lib_path="%userprofile%\Documents\Arduino\libraries"
if [%proj_name%] == [] exit
if exist %lib_path%\%proj_name% start /wait cmd /c rmdir %lib_path%\%proj_name% /s /q