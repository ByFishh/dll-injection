@echo off
call "D:\MicrosoftCode\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc /c .\src\*.cpp /I .\include /Fo".\obj\\"
link /DLL /OUT:injected.dll .\obj\*.obj .\lib\*.lib
exit
%comspec% /k