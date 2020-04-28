#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float  IntensidadL(float color);
float  IntensidadR(float color);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float colorR=0.0f, colorG=0.0f, colorB=0.0f, alpha = 0.0f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(colorR, colorG, colorB, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        colorR = 1.0f;
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        colorG = 1.0f;
    else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        colorB = 1.0f;
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {   colorR = 0.0f;colorB = 0.0f;colorG = 0.0f;}
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {   colorR = IntensidadL(colorR);colorB = IntensidadL(colorB);colorG =IntensidadL(colorG);}
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {   colorR = IntensidadR(colorR);colorB = IntensidadR(colorB);colorG =IntensidadR(colorG);}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float  IntensidadL(float color)
{
    if(color > 0)
        return color -= 0.0001;
}

float  IntensidadR(float color)
{
    if(color != 0 && color < 1)
        return color += 0.0001;
}