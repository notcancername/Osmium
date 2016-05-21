# Osmium
A MC clone in C, protocol-compatible with 1.9.4

Dependencies (Linux): 
- libpng
- libz
- libglfw3 (statically linked)
- libX11
- libdl
- libXrandr
- libXinerama
- libXi
- libXxf86vm
- libXcursor
- libpthread
- libm
- libGL
- libGLU

Dependencies (Windows): 
- libz
- glew32
- glfw3 (statically linked)
- opengl32
- glu32
- gdi32
- ws2_32
- libpng

Installation: 
1. Download executable from releases tab above.
2. Put in a folder of your choosing.
3. Open a 1.9.4 minecraft.jar from Mojang, and copy the assets folder into that directory. (ie INSTALLDIR/assets/minecraft/etc)
4. Run it!

Windows: 
Requires: MinGW, dependencies for windows listed above.
1. Go into (project root)/Osmium/Osmium/DebugWindows
2. Run 'make all'
3. Create an empty directory somewhere, this will be your installation directory.
4. Move the compiled executable into the directory (if there is no .exe extension, add it.)
5. Open a 1.9.4 minecraft.jar from Mojang, and copy the assets folder into that directory. (ie INSTALLDIR/assets/minecraft/etc)
6. Run it!

Linux: Requires GCC, depenendcies for linux listed above.
1. Go into (project root)/Osmium/Osmium/DebugLinux
2. Run 'make all'
3. Create an empty directory somewhere, this will be your installation directory.
4. Move the compiled executable into the directory
5. Open a 1.9.4 minecraft.jar from Mojang, and copy the assets folder into that directory. (ie INSTALLDIR/assets/minecraft/etc)
6. Run it!

