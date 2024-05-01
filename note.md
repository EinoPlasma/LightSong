## 如何配置SDL2
1. 看视频https://www.bilibili.com/video/BV18f4y1d7nm/ 下载和up主一样的SDL2-2.0.22-MinGW版本,根据up主的方法修改sdl2-config.cmake和编写CMakeLists.txt
2. 添加环境变量 CPLUS_INCLUDE_PATH 值为 C:\Program\3rdlibs\SDL2-2.0.22-MinGW\x86_64-w64-mingw32\include
3. 添加环境变量 C_INCLUDE_PATH 值为 C:\Program\3rdlibs\SDL2-2.0.22-MinGW\x86_64-w64-mingw32\include
4. 添加环境变量 LIBRARY_PATH 值为 C:\Program\3rdlibs\SDL2-2.0.22-MinGW\x86_64-w64-mingw32\lib
5. 把C:\Program\3rdlibs\SDL2-2.0.22-MinGW\x86_64-w64-mingw32\bin目录下的SDL2.dll和sdl2-config拷贝到本项目的cmake-build-debug目录下(不加的话编译能通过但运行会闪退)
6. 重启CLion

