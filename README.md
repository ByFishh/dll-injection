<p>1. Open "x64 Native Tools Command Prompt" and cd in your working dir<br>
<br>
2. Create obj file<br>
<br>
cl /EHsc /c .\src\*.cpp /I .\include /Fo".\obj\\"<br>
<br>
PS: Don't forget to replace with the good path to your include folder.<br>
<br>
3. Create .dll with obj file<br>
<br>
link /DLL /OUT:injected.dll .\obj\*.obj .\lib\*.lib</p><br>
