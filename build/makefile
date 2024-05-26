All: Server Client
	ECHO "Buildup Complete."
ENV:
	..\Local\ENV.bat
Server: server_func.obj poker.obj com_setup.obj
	cl /Fe"..\bin\Server" /MP ..\src\Server.c /link server_func.obj poker.obj com_setup.obj
Client: client_func.obj poker.obj com_setup.obj
	cl /Fe"..\bin\Client" /MP ..\src\Client.c /link client_func.obj poker.obj com_setup.obj
server_func.obj:
	cl /c /MP ..\src\server_func.c
client_func.obj:
	cl /c /MP ..\src\client_func.c
poker.obj:
	cl /c /MP ..\src\poker.c
com_setup.obj:
	cl /c /MP ..\src\com_setup.c
clean_all: clean
	del ..\bin\*.exe
clean:
	del *.obj
