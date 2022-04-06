#include <iostream>

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

    Cursor cursor(window, true);

    //glm::vec3 lightPos(1.25f, 1.5f, 2.0f);
    //glm::vec3 lightPos(0.8f, 0.0f, 0.5f);
    //glm::vec3 lightPos(0.0f, 0.0f, 7.0f);

    //Adding extra scope for clean up.
    {
        //Texture::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        VertexBufferLayout vertexBufferLayout;

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f,  0.2f,  2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3(0.0f,  0.0f, -3.0f)
        };

        #pragma region OldBuffer_Reference
        //float vertexBufferArray[] = {
        //    //positions     //text coord   //colors            
        //    -0.5f, -0.5f,   0.0f, 0.0f,    //1.0f, 0.0f, 0.0f, //0
        //     0.5f, -0.5f,   1.0f, 0.0f,    //0.0f, 1.0f, 0.0f, //1
        //     0.5f,  0.5f,   1.0f, 1.0f,    //0.0f, 0.0f, 1.0f, //2
        //    -0.5f,  0.5f,   0.0f, 1.0f,    //0.0f, 0.0f, 0.0f  //3
        //};
        //vertexBufferLayout.Push<float>(2); //positions.
        //vertexBufferLayout.Push<float>(2); //text coord.
        //vertexBufferLayout.Push<float>(3); //colors.

        /*unsigned int indexBufferArray[] = {
            0, 1, 2,
            2, 3, 0
        };
        
        IndexBuffer indexBuffer(indexBufferArray, 6);*/
        #pragma endregion

        float vertexBufferArray[] = {
            //Positions           //Normals             //Texture Coords
            -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };

        vertexBufferLayout.Push<float>(3); //positions.
        vertexBufferLayout.Push<float>(3); //normals.
        vertexBufferLayout.Push<float>(2); //texture coords.

        VertexBuffer vertexBuffer(vertexBufferArray, sizeof(vertexBufferArray));
        VertexArray objectVertexArray;
        objectVertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

        Shader objectShader("res/Shaders/Basic.shader");
        objectShader.Bind();
        
        objectShader.SetUniform1i("material.diffuse", 0);
        objectShader.SetUniform1i("material.specular", 1);
        objectShader.SetUniform1f("material.shininess", 32.0f);

        objectShader.SetVec3("directionalLight.direction", -0.2f, -1.0f, -0.3f);
        objectShader.SetVec3("directionalLight.ambient", 0.05f, 0.05f, 0.05f);
        objectShader.SetVec3("directionalLight.diffuse", 0.4f, 0.4f, 0.4f);
        objectShader.SetVec3("directionalLight.specular", 0.5f, 0.5f, 0.5f);

        objectShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
        objectShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        objectShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        objectShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        objectShader.SetUniform1f("pointLights[0].constant", 1.0f);
        objectShader.SetUniform1f("pointLights[0].linear", 0.09f);
        objectShader.SetUniform1f("pointLights[0].quadratic", 0.032f);
        
        objectShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
        objectShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        objectShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        objectShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        objectShader.SetUniform1f("pointLights[1].constant", 1.0f);
        objectShader.SetUniform1f("pointLights[1].linear", 0.09f);
        objectShader.SetUniform1f("pointLights[1].quadratic", 0.032f);
        
        objectShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
        objectShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        objectShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        objectShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        objectShader.SetUniform1f("pointLights[2].constant", 1.0f);
        objectShader.SetUniform1f("pointLights[2].linear", 0.09f);
        objectShader.SetUniform1f("pointLights[2].quadratic", 0.032f);
        
        objectShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
        objectShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        objectShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        objectShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        objectShader.SetUniform1f("pointLights[3].constant", 1.0f);
        objectShader.SetUniform1f("pointLights[3].linear", 0.09f);
        objectShader.SetUniform1f("pointLights[3].quadratic", 0.032f);

        objectShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        objectShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        objectShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        objectShader.SetUniform1f("spotLight.constant", 1.0f);
        objectShader.SetUniform1f("spotLight.linear", 0.09f);
        objectShader.SetUniform1f("spotLight.quadratic", 0.032f);
        objectShader.SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(7.0f)));
        objectShader.SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(12.0f)));

        Shader lightShader("res/Shaders/Light.shader");
        lightShader.Bind();

        Texture containerTextureNormal("res/Textures/container2.png");
        containerTextureNormal.Bind(0U);

        Texture containerTextureSpecular("res/Textures/container2_specular.png");
        containerTextureSpecular.Bind(1U);

        objectVertexArray.UnBind();

        vertexBuffer.UnBind();

        objectShader.UnBind();
        lightShader.UnBind();

        containerTextureNormal.UnBind();
        containerTextureSpecular.UnBind();

        glm::mat4 model(1.0f), view(model), projection(model);

        unsigned int lightCubeVAO;
        GLCall(glGenVertexArrays(1, &lightCubeVAO));
        GLCall(glBindVertexArray(lightCubeVAO));
              
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.GetRendererID()));
        // note that we update the light's position attribute's stride to reflect the buffer data
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
        GLCall(glEnableVertexAttribArray(0));
        
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);
        ImGui::StyleColorsDark();

        while (!glfwWindowShouldClose(window))
        {
            Time::Update();

            Renderer::ProcessInput(window);
            camera.ProcessInput(window);

            Renderer::Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Renderer::Draw(objectVertexArray, objectShader);

            //Spawning 10 cubes for testing purpose.
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                //objectShader.SetUniformMat4fp("model", glm::value_ptr(model));
                objectShader.SetUniformMat4f("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            containerTextureNormal.Bind(0U);
            containerTextureSpecular.Bind(1U);

            #pragma region TestingCode

            /*lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
            lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
            objectShader.SetVec3("lightPos", lightPos);
            objectShader.SetVec3("viewPos", camera.transform.position);*/

            /*lightColor = glm::vec3(1.0f);
            lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0f));
            lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7f));
            lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3f));
            glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
            glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
            //objectShader.SetVec3("light.ambient", ambientColor);
            //objectShader.SetVec3("light.diffuse", diffuseColor);*/

            #pragma endregion

            objectShader.SetVec3("viewPos", camera.transform.position);
            objectShader.SetVec3("spotLight.position", camera.transform.position);
            objectShader.SetVec3("spotLight.direction", camera.cameraConstraints.front);

            //Updating projection matrix again because fov is being changed through mouse scroll.
            projection = glm::perspective(glm::radians(camera.settings.fov), camera.settings.aspectRatio, camera.settings.near, camera.settings.far);
            view = camera.GetViewMatrix();
            objectShader.SetUniformMat4f("projection", projection);
            objectShader.SetUniformMat4f("view", view);
            // world transformation
            glm::mat4 model_L = glm::mat4(1.0f);
            objectShader.SetUniformMat4fp("model", glm::value_ptr(model_L));

            lightShader.Bind();
            lightShader.SetUniformMat4f("projection", projection);
            lightShader.SetUniformMat4f("view", view);

            for (unsigned int i = 0; i < 4; i++)
            {
                model_L = glm::mat4(1.0f);
                model_L = glm::translate(model_L, pointLightPositions[i]);
                model_L = glm::scale(model_L, glm::vec3(0.2f));
                lightShader.SetUniformMat4fp("model", glm::value_ptr(model_L));
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
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

        GLCall(glDeleteVertexArrays(1, &lightCubeVAO));

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    glfwTerminate();
    return 0;
}