#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "matrix.cpp"
#include <iostream>

using namespace std;

Matrix4x4 transformTriangulo;
Matrix4x4 transformCuadrado;
Matrix4x4 transformRombo;
bool ckk = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShader1Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";

const char *fragmentShader2Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";


const char *fragmentShader3Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n\0";


int main()
{

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


    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderTriangulo = glCreateShader(GL_FRAGMENT_SHADER); 
    unsigned int fragmentShaderCuadrado = glCreateShader(GL_FRAGMENT_SHADER); 
    unsigned int fragmentShaderRombo = glCreateShader(GL_FRAGMENT_SHADER); 

    unsigned int shaderProgramTriangulo  = glCreateProgram();
    unsigned int shaderProgramCuadrado = glCreateProgram(); 
    unsigned int shaderProgramRombo = glCreateProgram();
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    glShaderSource(fragmentShaderTriangulo, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderTriangulo);
    glShaderSource(fragmentShaderCuadrado, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderCuadrado);
    glShaderSource(fragmentShaderRombo, 1, &fragmentShader3Source, NULL);
    glCompileShader(fragmentShaderRombo);

    glAttachShader(shaderProgramTriangulo , vertexShader);
    glAttachShader(shaderProgramTriangulo, fragmentShaderTriangulo);
    glLinkProgram(shaderProgramTriangulo);

    glAttachShader(shaderProgramCuadrado, vertexShader);
    glAttachShader(shaderProgramCuadrado, fragmentShaderCuadrado);
    glLinkProgram(shaderProgramCuadrado);

    glAttachShader(shaderProgramRombo, vertexShader);
    glAttachShader(shaderProgramRombo, fragmentShaderRombo);
    glLinkProgram(shaderProgramRombo);

    float Triangle[] = {
        -0.1f, -0.1f, 0.0f, 
         0.1f, -0.1f, 0.0f, 
         0.0f,  0.1f, 0.0f,   
    };

    float Square[] = {
        -0.09f, -0.6f, 0.0f,  
        0.09f, -0.6f, 0.0f,  
        0.09f,  -0.4f, 0.0f,
        -0.09f, -0.4f, 0.0f    
    };

    unsigned int indices1[] = {
        0 , 1 , 2,
        0 , 2 , 3
    };

    float Diamond[] = {
        0.5f,  0.0f, 0.0f,  
        0.6f, -0.1f, 0.0f,  
        0.7f,  0.0f, 0.0f,
        0.6f,  0.1f, 0.0f    
    };

    unsigned int indices2[] = {
        0 , 1 , 3,
        1 , 2 , 3
    };

    unsigned int VBOs[3], VAOs[3] , EBOs[2];
    glGenVertexArrays(3, VAOs); 
    glGenBuffers(3, VBOs);
    glGenBuffers(2, EBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(VAOs[1]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(Square), Square, GL_STATIC_DRAW);
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[2]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(Diamond), Diamond, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);

    float tx = 0.0f, ty = 0.0f, ry = 0.0f, rx = 0.0f, rr = 0.0f;
    int act = 0;
    int acs = 0;
    float idx = 0;


    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(ckk)
        {
            //Escala del Triangulo
            if(act < 7000)
            {
                transformTriangulo.scale(1.00009f, 1.00009f, 1.0f);   //Aumenta el tamaño del triangulo
                act++;
            }
            else if(act == 7000 and acs < 7000)
            {
                transformTriangulo.scale(0.9999f, 0.9999f, 1.0f);     //Reduce el tamaño del triangulo
                acs++;  
            }
            if(acs == 7000){act = 0;acs = 0;}   //Reinicia las variables para el intercambio entre aumento y reduccion del tamaño

                // Traslacion en circulos del Cuadrado

            float theta = 2.0f * 3.1415926f * float(idx) / float(30);  // Se usa la formala para graficar una circunferencia
            float x = 0.1 * cos(theta);                                // Para realizar la rotacion alrededor del triangulo
            float y = 0.1 * sin(theta);                                // Con la formula se optinen los valores de los componetes
                                                                        // X y Y 
            transformCuadrado.translate(x, y, 0.0f);                   //Usamos la translacion para obtener este efecto
            idx++;
            if(idx == 30)
                idx = 0;

            // Traslacion del rombo 
            if(ty < 0.8f)  
            {
                ty += 0.0002; 
                transformRombo.translate(0.0f, 0.0002f, 0.0f); //Hacia  eje Y +
            }
            else if(tx < 1.2f)
            {
                tx += 0.0002; 
                transformRombo.translate(-0.0002f, 0.0f, 0.0f); //Hacia  eje X -
            }
            else if(ry < 1.6f)
            {
                ry += 0.0002;
                transformRombo.translate(0.0f, -0.0002f, 0.0f);  //Hacia eje Y -
            }
            else if(rx < 1.2f)
            {
                rx += 0.0002;
                transformRombo.translate(0.0002f, 0.0f, 0.0f);  //Hacia eje X +
            }
            else if(rr < 0.8f)
            {
                rr += 0.0002;
                transformRombo.translate(0.0f,0.0002f , 0.0f);  //Hacia eje Y +
            }
            if(rr >= 0.8f){ rx = 0.0f; ry = 0.0f; tx = 0.0f;ty = 0.0f; rr=0.0f;}
                
        }

        int vertexTransformLocation1 = glGetUniformLocation(shaderProgramTriangulo, "transform"); //Optenemos la variable transform del vertexshader
        glUseProgram(shaderProgramTriangulo);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	
        glUniformMatrix4fv(vertexTransformLocation1, 1, GL_FALSE, transformTriangulo.m_matrix); //Actualizacion de los vertices del triangulo con la transformacion

        int vertexTransformLocation2 = glGetUniformLocation(shaderProgramCuadrado, "transform");
        glUseProgram(shaderProgramCuadrado);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUniformMatrix4fv(vertexTransformLocation2, 1, GL_FALSE, transformCuadrado.m_matrix);	//Actualizacion de los vertices del cuadrado con la transformacion

        int vertexTransformLocation3 = glGetUniformLocation(shaderProgramRombo, "transform");
        glUseProgram(shaderProgramRombo);
        glBindVertexArray(VAOs[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUniformMatrix4fv(vertexTransformLocation3, 1, GL_FALSE, transformRombo.m_matrix); //Actualizacion de los vertices del rombo con la transformacion

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);
    glDeleteProgram(shaderProgramTriangulo);
    glDeleteProgram(shaderProgramCuadrado);

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

    else if(key == GLFW_KEY_P && action == GLFW_PRESS)  //Detiene la animacion
    {
        ckk = false;
    }
    else if(key == GLFW_KEY_I && action == GLFW_PRESS)  //Reanuda la animacion
    {
        ckk = true;
    }
}
