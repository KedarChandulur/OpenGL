#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "VertexBufferLayout.h"
#include "CallBackBridge.h"
#include "Time.h"
#include "Cursor.h"

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

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.settings.aspectRatio = (float)screenWidth / (float)screenHeight;
    camera.mouseMoveData.lastPositions = glm::vec2((float)(screenWidth / 2), (float)(screenHeight / 2));

    CallBackBridge callBackBridge;
    //glfwSetWindowUserPointer(window, &callBackBridge);
    callBackBridge.SetWindowResizeCallback(window);
    callBackBridge.SetMouseCallbacks(window, camera);

    Cursor cursor(window);

    glm::vec3 lightPos(1.2f, 10.0f, 2.0f);

    //Adding extra scope for clean up.
    {
        //Texture::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        VertexBufferLayout vertexBufferLayout;

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
              -0.5f, -0.5f, -0.5f,
               0.5f, -0.5f, -0.5f,
               0.5f,  0.5f, -0.5f,
               0.5f,  0.5f, -0.5f,
              -0.5f,  0.5f, -0.5f,
              -0.5f, -0.5f, -0.5f,

              -0.5f, -0.5f,  0.5f,
               0.5f, -0.5f,  0.5f,
               0.5f,  0.5f,  0.5f,
               0.5f,  0.5f,  0.5f,
              -0.5f,  0.5f,  0.5f,
              -0.5f, -0.5f,  0.5f,

              -0.5f,  0.5f,  0.5f,
              -0.5f,  0.5f, -0.5f,
              -0.5f, -0.5f, -0.5f,
              -0.5f, -0.5f, -0.5f,
              -0.5f, -0.5f,  0.5f,
              -0.5f,  0.5f,  0.5f,

               0.5f,  0.5f,  0.5f,
               0.5f,  0.5f, -0.5f,
               0.5f, -0.5f, -0.5f,
               0.5f, -0.5f, -0.5f,
               0.5f, -0.5f,  0.5f,
               0.5f,  0.5f,  0.5f,

              -0.5f, -0.5f, -0.5f,
               0.5f, -0.5f, -0.5f,
               0.5f, -0.5f,  0.5f,
               0.5f, -0.5f,  0.5f,
              -0.5f, -0.5f,  0.5f,
              -0.5f, -0.5f, -0.5f,

              -0.5f,  0.5f, -0.5f,
               0.5f,  0.5f, -0.5f,
               0.5f,  0.5f,  0.5f,
               0.5f,  0.5f,  0.5f,
              -0.5f,  0.5f,  0.5f,
              -0.5f,  0.5f, -0.5f
        };

        vertexBufferLayout.Push<float>(3); //positions.

        VertexBuffer vertexBuffer(vertexBufferArray, sizeof(vertexBufferArray));
        VertexArray objectVertexArray;
        objectVertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

        VertexArray lightVertexArray;
        lightVertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

        Shader objectShader("res/Shaders/Basic.shader");
        objectShader.Bind();

        glm::mat4 model(1.0f), view(model), projection(model);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(camera.settings.fov), camera.settings.aspectRatio, camera.settings.near, camera.settings.far);

        objectShader.SetUniformMat4fp("model", glm::value_ptr(model));
        objectShader.SetUniformMat4f("view", view);
        objectShader.SetUniformMat4f("projection", projection);

        objectShader.SetVec3("lightColor", 1.0f);
        objectShader.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);

        Shader lightShader("res/Shaders/Light.shader");
        lightShader.Bind();

        objectVertexArray.UnBind();
        lightVertexArray.UnBind();

        vertexBuffer.UnBind();

        objectShader.UnBind();
        lightShader.UnBind();


        while (!glfwWindowShouldClose(window))
        {
            Time::Update();

            Renderer::ProcessInput(window);
            camera.ProcessInput(window);

            Renderer::Clear();
            Renderer::Draw(objectVertexArray, objectShader);

            //Updating projection matrix again because fov is being changed through mouse scroll.
            projection = glm::perspective(glm::radians(camera.settings.fov), camera.settings.aspectRatio, camera.settings.near, camera.settings.far);
            view = camera.GetViewMatrix();
            objectShader.SetUniformMat4f("projection", projection);
            objectShader.SetUniformMat4f("view", view);

            // world transformation
            glm::mat4 model_L = glm::mat4(1.0f);
            objectShader.SetUniformMat4fp("model", glm::value_ptr(model_L));

            Renderer::Draw(lightVertexArray, lightShader);

            lightShader.SetUniformMat4f("projection", projection);
            lightShader.SetUniformMat4f("view", view);
            
            //model_L = glm::mat4(1.0f);
            model_L = glm::translate(model_L, lightPos);
            model_L = glm::scale(model_L, glm::vec3(0.2f));
            lightShader.SetUniformMat4fp("model", glm::value_ptr(model_L));

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}