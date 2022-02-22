#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "Time.h"
#include "CallBackBridge.h"

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
    
    CallBackBridge callBackBridge;
    callBackBridge.SetWindowResizeCallback(window);
    callBackBridge.SetMouseCallbacks(window, camera);

    //Adding extra scope for clean up.
    {
        //Texture::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        VertexBufferLayout layout;

        //float vertexBufferArray[] = {
        //    //positions   //text coord  //colors            
        //    -0.5f, -0.5f, 0.0f, 0.0f,   //1.0f, 0.0f, 0.0f, //0
        //     0.5f, -0.5f, 1.0f, 0.0f,   //0.0f, 1.0f, 0.0f, //1
        //     0.5f,  0.5f, 1.0f, 1.0f,   //0.0f, 0.0f, 1.0f, //2
        //    -0.5f,  0.5f, 0.0f, 1.0f,   //0.0f, 0.0f, 0.0f  //3
        //};

        float vertexBufferArray[] = {
              -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
               0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
              -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
               0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
              -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

              -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
              -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
              -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
               0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
               0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
               0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
              -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

              -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
               0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
               0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
              -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
              -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        //layout.Push<float>(2); //positions.
        layout.Push<float>(3); //positions.
        layout.Push<float>(2); //text coord.
        //layout.Push<float>(3); //colors.

        VertexBuffer vb(vertexBufferArray, sizeof(vertexBufferArray));
        VertexArray va;
        va.AddBuffer(vb, layout);

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        IndexBuffer ib(indices, 6);

        Shader shader("res/Shaders/Basic.shader");
        shader.Bind();

        //Texture jpg_texture("res/Textures/wall.jpg");
        Texture jpg_texture("res/Textures/container.jpg");
        Texture png_logo_texture("res/Textures/awesomeface.png");
        jpg_texture.Bind(0U);
        png_logo_texture.Bind(1U);

        glm::mat4 model(1.0f), view(model), projection(model);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(camera.settings.fov), camera.settings.aspectRatio, camera.settings.near, camera.settings.far);

        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniform1i("u_Texture1", 1);
        shader.SetUniformMat4fp("model", glm::value_ptr(model));
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("projection", projection);

        glm::vec3 cameraTarget = glm::vec3(0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        const float radius = 10.0f;

        va.UnBind();
        vb.UnBind();
        ib.UnBind();
        shader.UnBind();

        while (!glfwWindowShouldClose(window))
        {
            Time::Update();

            Renderer::ProcessInput(window);
            camera.ProcessInput(window);

            Renderer::Clear();
            Renderer::Draw(va, ib, shader);

            //Updating projection matrix again because fov is be changed through mouse scroll.
            projection = glm::perspective(glm::radians(camera.settings.fov), camera.settings.aspectRatio, camera.settings.near, camera.settings.far);
            shader.SetUniformMat4f("projection", projection);

            view = camera.GetViewMatrix();
            shader.SetUniformMat4f("view", view);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}