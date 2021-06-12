@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
del injected.dll .\obj\*.obj
cl /EHsc /c .\src\*.cpp /I .\include /Fo".\obj\\"
link /DLL /OUT:injected.dll .\obj\*.obj .\lib\*.lib

REM EXIT
REM Enlevez EXIT si vous avez besoin de debug

%comspec% /k