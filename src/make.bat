if not exist "build" mkdir "build"
if not exist "atmega2560" mkdir "atmega2560"
start /wait cmd /c compile.bat Dynamixel.cpp
start /wait cmd /c compile.bat DynamixelDevice.cpp
start /wait cmd /c compile.bat DynamixelInterface.cpp
start /wait cmd /c compile.bat DynamixelInterfaceArduinoImpl.cpp

cd build
start /wait cmd /c avr-ar -r "../atmega2560/libDxlMaster.a" "Dynamixel.cpp.o" "DynamixelDevice.cpp.o" "DynamixelInterface.cpp.o" "DynamixelInterfaceArduinoImpl.cpp.o"
cd ../
start /wait cmd /c rmdir build /s /q