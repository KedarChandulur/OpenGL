#include <iostream>
#include <map>

#include "VertexBufferLayout.h"
#include "CallBackBridge.h"
#include "Time.h"
#include "Cursor.h"
#include "Texture.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#pragma region CallBackBridge_Method
//Reference taken from: https://github.com/glfw/glfw/issues/815#issuecomment-235986227
//CallBackBridge* Get_CallBackBridgeContext(GLFWwindow* window)
//{
//    return static_cast<CallBackBridge*>(glfwGetWindowUserPointer(window));
//};
#pragma endregion

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const uint32_t screenWidth = 640;
    const uint32_t screenHeight = 480;

    window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Window", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    GLCall(glViewport(0, 0, screenWidth, screenHeight));

    Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));
    camera.settings.aspectRatio = (float)screenWidth / (float)screenHeight;
    camera.mouseMoveData.lastPositions = glm::vec2((float)(screenWidth / 2), (float)(screenHeight / 2));

    CallBackBridge callBackBridge;
    //glfwSetWindowUserPointer(window, &callBackBridge);
    callBackBridge.SetWindowResizeCallback(window);
    callBackBridge.SetMouseCallbacks(window, camera);

    Cursor cursor(window, false);

    //Adding extra scope for clean up.
    {
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        GLCall(glEnable(GL_STENCIL_TEST));
        GLCall(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
        GLCall(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexBufferLayout vertexBufferLayout;

        float vertexBufferArray[] = {
            //Positions           //Texture Coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
                                  
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
                                  
            -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
                                  
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
                                  
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
                                  
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f
        };

        float planeVerticesArray[] = {
            //Positions           //Texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

             5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
             5.0f, -0.5f, -5.0f,  1.0f, 1.0f
        };

        float transparentVerticesArray[] = {
            //Positions          //Texture Coords (swapped y coordinates because texture is flipped upside down)
            0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
            0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
            1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

            0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
            1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
            1.0f,  0.5f,  0.0f,  1.0f,  0.0f
        };

        vertexBufferLayout.Push<float>(3); //Positions.
        vertexBufferLayout.Push<float>(2); //Texture coords.

        VertexBuffer vertexBuffer(vertexBufferArray, sizeof(vertexBufferArray)), planeBuffer(planeVerticesArray, sizeof(planeVerticesArray)), transparentBuffer(transparentVerticesArray, sizeof(transparentVerticesArray));

        VertexArray objectVertexArray, planeVertexArray, transparentVertexArray;
        objectVertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
        planeVertexArray.AddBuffer(planeBuffer, vertexBufferLayout);
        transparentVertexArray.AddBuffer(transparentBuffer, vertexBufferLayout);

        Shader borderColorShader("res/Shaders/FragColor.shader");
        Shader objectShader("res/Shaders/Adv-OpenGL.shader");

        Texture textureMarbel("res/Textures/marble.jpg");
        textureMarbel.Bind(0U);
        Texture textureMetal("res/Textures/metal.png");
        textureMetal.Bind(1U);
        Texture textureGrass("res/Textures/grass.png", false);
        //Texture textureGrass("res/Textures/blending_transparent_window.png");
        textureGrass.Bind(2U);

        std::vector<glm::vec3> windows
        {
            glm::vec3(-1.5f, 0.0f, -0.48f),
            glm::vec3(1.5f, 0.0f, 0.51f),
            glm::vec3(0.0f, 0.0f, 0.7f),
            glm::vec3(-0.3f, 0.0f, -2.3f),
            glm::vec3(0.5f, 0.0f, -0.6f)
        };

        objectShader.Bind();
        objectShader.SetUniform1i("texture1", 0);

        objectVertexArray.UnBind();
        planeVertexArray.UnBind();
        transparentVertexArray.UnBind();

        vertexBuffer.UnBind();
        planeBuffer.UnBind();
        transparentBuffer.UnBind();

        objectShader.UnBind();

        textureMarbel.UnBind();
        textureMetal.UnBind();

        glm::mat4 model(1.0f), view(model), projection(model);
        
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        float borderScale = 1.1f;

        while (!glfwWindowShouldClose(window))
        {
            Time::Update();

            Renderer::ProcessInput(window);
            camera.ProcessInput(window);

            Renderer::Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            std::map<float, glm::vec3> sorted;
            for (unsigned int i = 0; i < windows.size(); i++)
            {
                float distance = glm::length(camera.transform.position - windows[i]);
                sorted[distance] = windows[i];
            }

            //Updating projection matrix again because fov is being changed through mouse scroll.
            projection = glm::perspective(glm::radians(camera.settings.fov), camera.settings.aspectRatio, camera.settings.near, camera.settings.far);
            view = camera.GetViewMatrix();

            borderColorShader.Bind();
            borderColorShader.SetUniformMat4f("projection", projection);
            borderColorShader.SetUniformMat4f("view", view);

            objectShader.Bind();
            objectShader.SetUniformMat4f("projection", projection);
            objectShader.SetUniformMat4f("view", view);

            glStencilMask(0x00);
            textureMetal.Bind(0U);
            objectShader.SetUniformMat4f("model", glm::mat4(1.0f));
            Renderer::Draw(planeVertexArray, 6);

            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
            textureMarbel.Bind(0U);
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, 0.01f, -1.0f));
            objectShader.SetUniformMat4fp("model", glm::value_ptr(model));
            Renderer::Draw(objectVertexArray, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.01f, 0.0f));
            objectShader.SetUniformMat4fp("model", glm::value_ptr(model));
            Renderer::Draw(objectVertexArray, 36);

            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0x00);
            glDisable(GL_DEPTH_TEST);
            borderColorShader.Bind();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, 0.01f, -1.0f));
            model = glm::scale(model, glm::vec3(borderScale, borderScale, borderScale));
            borderColorShader.SetUniformMat4fp("model", glm::value_ptr(model));
            Renderer::Draw(objectVertexArray, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.01f, 0.0f));
            model = glm::scale(model, glm::vec3(borderScale, borderScale, borderScale));
            borderColorShader.SetUniformMat4fp("model", glm::value_ptr(model));
            Renderer::Draw(objectVertexArray, 36);
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            glEnable(GL_DEPTH_TEST);

            objectShader.Bind();
            textureGrass.Bind(0U);
            /*for (unsigned int i = 0; i < windows.size(); i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, windows[i]);
                objectShader.SetUniformMat4f("model", model);
                Renderer::Draw(transparentVertexArray, 6);
            }*/
            for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, it->second);
                objectShader.SetUniformMat4f("model", model);
                Renderer::Draw(transparentVertexArray, 6);
            }

            {
                ImGui::Begin("New Window");
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    glfwTerminate();
    return 0;
}