1.Install Mingw
2.Install SDL libs in mingw  /bin /include /lib
3.Add SDL.dll to Windows/System32
4.Link Libraries:
	C:\MinGW\lib\libopengl32.a
	C:\MinGW\lib\SDL_image.lib
	C:\MinGW\lib\libSDL.dll.a
	C:\MinGW\lib\libSDLmain.a
	C:\MinGW\lib\libmingw32.a
5.Add option -mwindows to linker
6.Add C:\MinGW\include\SDL to compiler search directory 

(Code::Blocks)
