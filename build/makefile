ENV:
	..\Local\ENV.bat
Server_DBG:
	cl /Fe"..\bin\Server_DBG" ..\src\Server.c ..\src\com_setup.c 
Client_DBG:
	cl /Fe"..\bin\Client_DBG" ..\src\Client.c ..\src\com_setup.c 
clean_all: clean
	del ..\bin\*.exe
clean:
	del *.obj *.pdb *.ilk
