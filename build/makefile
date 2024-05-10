ENV:
	..\Local\ENV.bat
Server_DBG:
	cl /Fe"..\bin\Server_DBG" ..\src\Server.c ..\src\com_setup.c 
Client_DBG:
	cl /Fe"..\bin\Client_DBG" ..\src\Client.c ..\src\com_setup.c 
clean:
	del *.obj *.pdb *.ilk *.exe
clean_all:
	del *.obj *.pdb *.ilk *.exe
	del ..\include\*.obj *.pdb *.ilk *.exe
	del ..\src\*.obj *.pdb *.ilk *.exe
	del ..\Test\*.obj *.pdb *.ilk *.exe
