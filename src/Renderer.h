#pragma once

#include <GL/glew.h>
#include "GLFW\glfw3.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define GLCallHex(x) GLClearError();\
    x;\
    ASSERT(GLLogCallHex())

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

bool GLLogCallHex();

class Renderer
{
public:
    static void Clear(glm::vec4 clearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void Draw(const VertexArray& va, const Shader& shader);
    static void ProcessInput(GLFWwindow* window);

    Renderer(Renderer& other) = delete;
    void operator=(const Renderer&) = delete;
private:
    Renderer() = default;
    ~Renderer() = default;
};