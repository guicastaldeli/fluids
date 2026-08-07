@echo off
set VCPKG_DIR=C:\Users\casta\OneDrive\Desktop\vscode\fluids\vcpkg\installed\x64-windows
set PATH=%VCPKG_DIR%\bin;%PATH%

echo Compiling...

g++ -std=c++20 ^
    -I"%VCPKG_DIR%\include" ^
    -I"C:/Users/casta/OneDrive/Desktop/glad/include" ^
    -I"C:/Users/casta/OneDrive/Desktop/glm-1.0.2" ^
    *.cpp ^
    "C:/Users/casta/OneDrive/Desktop/glad/src/glad.c" ^
    -o main.exe ^
    "%VCPKG_DIR%\lib\glfw3dll.lib" ^
    -lopengl32 ^
    -lgdi32

if %errorlevel% neq 0 (
    echo.
    echo Compilation failed!
    pause
    exit /b %errorlevel%
)

echo.
echo Compilation successful!
echo Running main.exe...
echo.
main.exe
pause