# OpenGL

**Researching on OpenGL (Still a W.I.P)**

- Adding more code and abstracting where possible.
- Using [LearnOpenGL](https://learnopengl.com) as a part of research or for reference purpose.

---

## Prerequisites

- [Visual Studio 2019 or later](https://visualstudio.microsoft.com/) with **Desktop development with C++** workload installed
- [CMake 3.20 or later](https://cmake.org/download/)
- [Git](https://git-scm.com/)

---

## Getting Started

**1. Clone the repository with all submodules:**
```bash
git clone --recurse -submodules <repository-url>
```

If you already cloned without submodules:
```bash
git submodule update --init --recursive
```

**2. Open the project:**

Open the cloned folder in Visual Studio by right-clicking the folder and selecting **Open with Visual Studio**.
Visual Studio will automatically detect the CMakeLists.txt and configure the project.

Alternatively you can configure and build via the command line:
```bash
cmake -B build
cmake --build build
```

---

## Dependencies

All dependencies are included as git submodules under the `vendor/` folder and are automatically built — no manual downloads required.

| Library | Description |
|---|---|
| [GLFW](https://www.glfw.org/) | Window and input handling |
| [GLEW](https://github.com/Perlmint/glew-cmake) | OpenGL extension loading |
| [GLM](https://github.com/g-truc/glm) | Mathematics library for OpenGL |
| [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) | Image loading |
| [Dear ImGui](https://github.com/ocornut/imgui) | Immediate mode GUI |
| [Assimp](https://github.com/assimp/assimp) | 3D model importing |

---

## Mentions

- [TheCherno](https://www.youtube.com/@TheCherno)
- [LearnOpenGL](https://learnopengl.com)
