#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "matrix.cpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
Matrix4x4 transform1;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window,key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = 
    {
         0.5f, -0.5f, 0.0f,  
         0.0f,  0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f,  
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int vertexColorLocation1 = glGetUniformLocation(shaderProgram, "transform");
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUniformMatrix4fv(vertexColorLocation1, 1, GL_FALSE, transform1.m_matrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window,GL_TRUE);
    else if(key == GLFW_KEY_R && action == GLFW_PRESS) // T RxRyRz S Rx
    {
        transform1.Control(64,0,0,0,1);             //RotationX
        transform1.print();
        transform1.Control(0,1,1.25,1.25,5);        //Scala
        transform1.print();
        transform1.Control(91,0,0,0,3);             //RotationZ
        transform1.print();
        transform1.Control(53,0,0,0,2);             //RotationY
        transform1.print();
        transform1.Control(64,0,0,0,1);             //RotationX
        transform1.print();
        transform1.Control(0,0.34,0.63,0.525,4);    //Traslation
        transform1.print();
    }
    else if(key == GLFW_KEY_1 && action == GLFW_PRESS) // Por pasos -> T RxRyRz S Rx
    {
        transform1.Control(64,0,0,0,1);             //RotacionX
        transform1.print();
    }
    else if(key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        transform1.Control(0,1,1.25,1.25,5);        //Scala
        transform1.print();
    }
    else if(key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        transform1.Control(91,0,0,0,3);             //RotacionZ
        transform1.print();
    }
    else if(key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        transform1.Control(53,0,0,0,2);             //RotacionY
        transform1.print();
    }
    else if(key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        transform1.Control(64,0,0,0,1);             //RotacionX
        transform1.print();
    }
    else if(key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        transform1.Control(0,0.34,0.63,0.525,4);    //Traslation
        transform1.print();
    }
    else if(key == GLFW_KEY_L && action == GLFW_PRESS)  // T Rx S Ry 
    {
        transform1.Control(53,0,0,0,2);             //RotationY
        transform1.print();
        transform1.Control(0,1,1.25,1.25,5);        //Scala
        transform1.print();
        transform1.Control(64,0,0,0,1);             //RotationX
        transform1.print();
        transform1.Control(0,0.34,0.63,0.525,4);    //Traslation
        transform1.print();
    }
}
