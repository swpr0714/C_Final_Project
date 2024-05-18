All: Server_DBG Client_DBG
	ECHO "Buildup Complete."
ENV:
	..\Local\ENV.bat
Server_DBG:
	cl /Fe"..\bin\Server_DBG" ..\src\Server.c ..\src\com_setup.c ..\src\poker.c ..\src\server_func.c
Client_DBG:
	cl /Fe"..\bin\Client_DBG" ..\src\Client.c ..\src\com_setup.c ..\src\poker.c ..\src\client_func.c
clean_all: clean
	del ..\bin\*.exe
clean:
	del *.obj *.pdb *.ilk
