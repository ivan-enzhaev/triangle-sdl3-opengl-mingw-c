# triangle-sdl3-opengl-mingw-c

A project template for building and running an SDL3 application with OpenGL and GLAD on Windows using MinGW 13.1 and CMake.

## 📖 Full Tutorial
For the complete step-by-step instructions on setting up the environment, adding SDL3 to your system PATH, and configuring the project, follow the guide here:

👉 **[Setting up SDL3 with OpenGL and GLAD (MinGW)](https://ivan-enzhaev.github.io/tutorials/sdl3-opengl/mingw/setting-up-sdl3-opengl-mingw/?lang=en)**

*Читать на русском:* **[Настройка SDL3 с OpenGL и GLAD (MinGW)](https://ivan-enzhaev.github.io/tutorials/sdl3-opengl/mingw/setting-up-sdl3-opengl-mingw/?lang=ru)**

## 🚀 Quick Start
If you already have your environment configured:

1. Clone the repository.
2. Ensure you have the required libraries in place:
   - SDL3 development files at `C:/libs/SDL3-devel-3.4.8-mingw`
   - SDL3 runtime binaries at `C:/libs/SDL3-3.4.8-win32-x64` (and added to your User **Path** variable)
   - GLAD (OpenGL 3.3) generated and extracted to `C:/libs/glad-0.1.36/opengl-3.3`
3. Use the provided automation scripts to manage your build:
   - `config-exe.bat` — Configures the project using CMake.
   - `build-exe.bat` — Compiles the binary into the build directory.
   - `run-exe.bat` — Launches the compiled executable.
