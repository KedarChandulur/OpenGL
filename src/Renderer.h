#pragma once

#include "OpenGLErrorHandler.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"

class Renderer
{
public:
    static void Clear(glm::vec4 clearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void Draw(const VertexArray& va, const Shader& shader, GLsizei count = 36);
    static void Draw(const VertexArray& va, GLsizei count = 36);
    static void ProcessInput(GLFWwindow* window);

    Renderer(Renderer& other) = delete;
    void operator=(const Renderer&) = delete;
private:
    Renderer() = default;
    ~Renderer() = default;
};