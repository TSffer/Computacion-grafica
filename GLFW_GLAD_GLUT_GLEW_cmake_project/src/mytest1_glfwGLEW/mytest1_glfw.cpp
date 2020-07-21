#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdio>

#include <math.h>
#include <SOIL.h>

#include <cstdlib>
#include <unistd.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "matriz.cpp"
#include "shader.h"

#include <iostream>
using namespace std;
using namespace glm;

// Set up camera vectors
vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

glm::mat4 projection, view;
// Time between current frame and last frame
GLfloat deltaTime = 0.0f;
// Time at last frame: subtract from current frame's time to get deltaTimes
GLfloat lastFrame = 0.0f;   
GLfloat lastX = 400, lastY = 300;
// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector 
// pointing to the right (due to how Eular angels work) so we initially rotate a bit to the left.
GLfloat yaw1 = -90.0f;  
GLfloat pitch1 = 0.0f;


float alpha = 0;

float eyex = 1;
float eyey = 1;
float eyez = 1;

float v_eye[3];


float up[3];

float vc[3];

matriz trans;

void controls(GLFWwindow* window, int key, int scancode, int action, int mods);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(yoffset>0) {
        if (v_eye[0]!=0)
        {
          if (v_eye[0]>0)
          {
            v_eye[0]=v_eye[0]-0.05;
          }
          else if (v_eye[0]<0)
          {
            v_eye[0]=v_eye[0]+0.05;
          }
        }
        if (v_eye[1]!=0)
        {
          if (v_eye[1]>0)
          {
            v_eye[1]=v_eye[1]-0.05;
          }
          else if (v_eye[1]<0)
          {
            v_eye[1]=v_eye[1]+0.05;
          }
        }
        if (v_eye[2]!=0)
        {
          if (v_eye[2]>0)
          {
            v_eye[2]=v_eye[2]-0.05;
          }
          else if (v_eye[2]<0)
          {
            v_eye[2]=v_eye[2]+0.05;
          }
        }
    }

    if(yoffset<0) {
        if (v_eye[0]!=0)
        {
          if (v_eye[0]>0)
          {
            v_eye[0]=v_eye[0]+0.05;
          }
          else if (v_eye[0]<0)
          {
            v_eye[0]=v_eye[0]-0.05;
          }
        }
        if (v_eye[1]!=0)
        {
          if (v_eye[1]>0)
          {
            v_eye[1]=v_eye[1]+0.05;
          }
          else if (v_eye[1]<0)
          {
            v_eye[1]=v_eye[1]-0.05;
          }
        }
        if (v_eye[2]!=0)
        {
          if (v_eye[2]>0)
          {
            v_eye[2]=v_eye[2]+0.05;
          }
          else if (v_eye[2]<0)
          {
            v_eye[2]=v_eye[2]-0.05;
          }
        }
    }

}

GLFWwindow* initWindow(const int resX, const int resY)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, controls);
    glfwSetScrollCallback(window, scroll_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}
/*
class cubo
{
public:
    float l=0.5;
    float xi, yi, zi;
    int esquina=0;
    GLfloat vertices[72];
    GLfloat colors[72];
    GLfloat textures[48];
    unsigned int texture;

    cubo(float _xi, float _yi, float _zi, float _ini){
        xi=_xi;     yi=_yi;     zi=_zi;
        for (int i = 0; i < 72; ++i)
        {
            vertices[i]=0.0;
            colors[i]=0.0;
        }

        vertices[0]=xi;     vertices[1]=yi;     vertices[2]=zi;     vertices[3]=xi-l;       vertices[4]=yi;     vertices[5]=zi;     vertices[6]=xi-l;   vertices[7]=yi-l;       vertices[8]=zi;     vertices[9]=xi;     vertices[10]=yi-l;      vertices[11]=zi;
        vertices[12]=xi;    vertices[13]=yi;    vertices[14]=zi+l;  vertices[15]=xi-l;      vertices[16]=yi;    vertices[17]=zi+l;  vertices[18]=xi-l;  vertices[19]=yi-l;      vertices[20]=zi+l;  vertices[21]=xi;    vertices[22]=yi-l;      vertices[23]=zi+l;
        vertices[24]=xi;     vertices[25]=yi;     vertices[26]=zi;  vertices[27]=xi-l;      vertices[28]=yi;    vertices[29]=zi;    vertices[30]=xi-l;  vertices[31]=yi;        vertices[32]=zi+l;  vertices[33]=xi;    vertices[34]=yi;        vertices[35]=zi+l; 
        vertices[36]=xi-l;   vertices[37]=yi-l;   vertices[38]=zi;  vertices[39]=xi;        vertices[40]=yi-l;  vertices[41]=zi;    vertices[42]=xi;    vertices[43]=yi-l;      vertices[44]=zi+l;  vertices[45]=xi-l;  vertices[46]=yi-l;      vertices[47]=zi+l;
        vertices[48]=xi;     vertices[49]=yi;     vertices[50]=zi;  vertices[51]=xi;        vertices[52]=yi;    vertices[53]=zi+l;  vertices[54]=xi;    vertices[55]=yi-l;      vertices[56]=zi+l;  vertices[57]=xi;    vertices[58]=yi-l;      vertices[59]=zi;
        vertices[60]=xi-l;   vertices[61]=yi;     vertices[62]=zi;  vertices[63]=xi-l;      vertices[64]=yi;    vertices[65]=zi+l;  vertices[66]=xi-l;  vertices[67]=yi-l;      vertices[68]=zi+l;  vertices[69]=xi-l;  vertices[70]=yi-l;      vertices[71]=zi;
        dar_color(_ini);
        dar_textura();
    }
    void dar_color(float xini){
        GLfloat colores[]={
            1, 0, 0,      1, 0, 0,      1, 0, 0,      0, 0, 0,
            0, 1, 0,      0, 1, 0,      0, 1, 0,      0, 0, 0,
            0, 0, 1,      0, 0, 1,      0, 0, 1,      0, 0, 0,
            1, 1, 1,      1, 1, 1,      1, 1, 1,      0, 0, 0,
            1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0,    0, 0, 0,
            1, 1, 0,      1, 1, 0,      1, 1, 0,      0, 0, 0
        };

        for (int i = 0; i < 72; i=i+12)
        {
            float inv[12];
            for (int j = 0; j < 12; ++j)
            {
                inv[j]=0;
            }
            int pos=0;
            for (int j = i; j < i+12; ++j)
            {
                inv[pos]=vertices[j];
                pos++;
            }
            if (comprobar(inv, xini))
            {
                for (int k = i; k < i+12; ++k)
                {
                    colors[k]=colores[k];                
                }
            }
            else{
                for (int k = i; k < i+12; ++k)
                {
                    colors[k]=0.5;               
                }
            }
        }
        
    }
    bool comprobar(float vec[12], float xini){
        if ((vec[0]==xini || vec[0]==-xini) && (vec[3]==xini || vec[3]==-xini) && (vec[6]==xini || vec[6]==-xini) && (vec[9]==xini || vec[9]==-xini))
        {
            return true;
        }
        else if ((vec[1]==xini || vec[1]==-xini) && (vec[4]==xini || vec[4]==-xini) && (vec[7]==xini || vec[7]==-xini) && (vec[10]==xini || vec[10]==-xini))
        {
            return true;
        }
        else if ((vec[2]==xini || vec[2]==-xini) && (vec[5]==xini || vec[5]==-xini) && (vec[8]==xini || vec[8]==-xini) && (vec[11]==xini || vec[11]==-xini))
        {
            return true;
        }
        else return false;
    }
    void dar_textura(){
        GLfloat texV[]={
            1.0f, 1.0f,     1.0f, 0.0f,     0.0f, 0.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 0.0f,     0.0f, 0.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 0.0f,     0.0f, 0.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 0.0f,     0.0f, 0.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 0.0f,     0.0f, 0.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 0.0f,     0.0f, 0.0f,     0.0f, 1.0f
        };
    }
    void drawCube(float xini)
    {
                
        //attempt to rotate cube
        glRotatef(alpha, 0, 0, -1);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        glDrawArrays(GL_QUADS, 0, 24);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void rotarZ(float angulo){
        float vec[4];
        for (int i = 0; i < 24; ++i)
        {
            vec[0]=vertices[(i*3)+0];
            vec[1]=vertices[(i*3)+1];
            vec[2]=vertices[(i*3)+2];
            vec[4]=0;

            trans.mul_rotZ(vec, angulo);

            vertices[(i*3)+0]=vec[0];
            vertices[(i*3)+1]=vec[1];
            vertices[(i*3)+2]=vec[2];

        }
    }
    void rotarY(float angulo){
        float vec[4];
        for (int i = 0; i < 24; ++i)
        {
            vec[0]=vertices[(i*3)+0];
            vec[1]=vertices[(i*3)+1];
            vec[2]=vertices[(i*3)+2];
            vec[4]=0;

            trans.mul_rotY(vec, angulo);

            vertices[(i*3)+0]=vec[0];
            vertices[(i*3)+1]=vec[1];
            vertices[(i*3)+2]=vec[2];

        }
    }

    void rotarX(float angulo){
        float vec[4];
        for (int i = 0; i < 24; ++i)
        {
            vec[0]=vertices[(i*3)+0];
            vec[1]=vertices[(i*3)+1];
            vec[2]=vertices[(i*3)+2];
            vec[4]=0;

            trans.mul_rotX(vec, angulo);

            vertices[(i*3)+0]=vec[0];
            vertices[(i*3)+1]=vec[1];
            vertices[(i*3)+2]=vec[2];

        }
    }

    ~cubo(){};
    
};
*/


class cubo
{
public:
    unsigned int VBO[6], VAO[6], EBO[6];
    Shader *ourShader;
    GLuint texture[6];
    unsigned char *data;
    cubo(){
        cout<<"hola"<<endl;
        ourShader = new Shader("/home/luis/Documentos/github/Computacion-grafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glfwGLEW/shaders/texture.vs", "/home/luis/Documentos/github/Computacion-grafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glfwGLEW/shaders/texture.frag"); 
        cout<<"hola"<<endl;
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
        
        dibujar_col_tex();
    }

    void dibujar_col_tex(){
        float vertices[] = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {  
            0, 1, 3, // first triangel
            1, 2, 3  // second triangel
        };

        for (int i = 0; i < 1; ++i)
        {
            glGenVertexArrays(1, &VAO[i]);
            glGenBuffers(1, &VBO[i]);
            glGenBuffers(1, &EBO[i]);

            glBindVertexArray(VAO[i]);

            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            // texture coord attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);


            // load and create a texture 
            // -------------------------
            glGenTextures(1, &texture[i]);
            glBindTexture(GL_TEXTURE_2D, texture[i]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
            // Set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // Set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Load image, create texture and generate mipmaps
            int width, height;
            unsigned char* image = SOIL_load_image("/home/luis/Documentos/github/Computacion-grafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glfwGLEW/shaders/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
            SOIL_free_image_data(image);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

        }
    }

    void dibujar(){
        // bind Texture
        for (int i = 0; i < 1; ++i)
        {
            //glBindTexture(GL_TEXTURE_2D, texture[i]);

            // render container
            ourShader->use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture[i]);
            glUniform1i(glGetUniformLocation(ourShader->Program, "ourTexture"), 0);

            GLint modelLoc = glGetUniformLocation(ourShader->Program, "model");
            GLint viewLoc = glGetUniformLocation(ourShader->Program, "view");
            GLint projLoc = glGetUniformLocation(ourShader->Program, "projection");
            // Pass the matrices to the shader
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


            glBindVertexArray(VAO[i]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    }

    ~cubo(){
        for (int i = 0; i < 1; ++i)
        {
            glDeleteVertexArrays(1, &VAO[i]);
            glDeleteBuffers(1, &VBO[i]);
            glDeleteBuffers(1, &EBO[i]);
        }

    }
    
};

vector<vector<vector<cubo*>>> rubik;


void rotarVecY(int pmedio){

    for (int i = 0; i < 2; ++i)
    {
        cubo *temp=rubik[0][pmedio][1];
        rubik[0][pmedio][1]=rubik[0][pmedio][0];

        cubo *temp2=rubik[0][pmedio][2];
        rubik[0][pmedio][2]=temp;

        temp=rubik[1][pmedio][2];
        rubik[1][pmedio][2]=temp2;

        temp2=rubik[2][pmedio][2];
        rubik[2][pmedio][2]=temp;

        temp=rubik[2][pmedio][1];
        rubik[2][pmedio][1]=temp2;

        temp2=rubik[2][pmedio][0];
        rubik[2][pmedio][0]=temp;

        temp=rubik[1][pmedio][0];
        rubik[1][pmedio][0]=temp2;

        rubik[0][pmedio][0]=temp;
    }
    
}


void rotarVecZ(int pmedio){

    for (int i = 0; i < 2; ++i)
    {
        cubo *temp=rubik[pmedio][0][1];
        rubik[pmedio][0][1]=rubik[pmedio][0][0];

        cubo *temp2=rubik[pmedio][0][2];
        rubik[pmedio][0][2]=temp;

        temp=rubik[pmedio][1][2];
        rubik[pmedio][1][2]=temp2;

        temp2=rubik[pmedio][2][2];
        rubik[pmedio][2][2]=temp;

        temp=rubik[pmedio][2][1];
        rubik[pmedio][2][1]=temp2;

        temp2=rubik[pmedio][2][0];
        rubik[pmedio][2][0]=temp;

        temp=rubik[pmedio][1][0];
        rubik[pmedio][1][0]=temp2;

        rubik[pmedio][0][0]=temp;
    }    

}


void rotarVecX(int pmedio){

    for (int i = 0; i < 2; ++i)
    {
        cubo *temp=rubik[1][0][pmedio];
        rubik[1][0][pmedio]=rubik[0][0][pmedio];

        cubo *temp2=rubik[2][0][pmedio];
        rubik[2][0][pmedio]=temp;

        temp=rubik[2][1][pmedio];
        rubik[2][1][pmedio]=temp2;

        temp2=rubik[2][2][pmedio];
        rubik[2][2][pmedio]=temp;

        temp=rubik[1][2][pmedio];
        rubik[1][2][pmedio]=temp2;

        temp2=rubik[0][2][pmedio];
        rubik[0][2][pmedio]=temp;

        temp=rubik[0][1][pmedio];
        rubik[0][1][pmedio]=temp2;

        rubik[0][0][pmedio]=temp;
    }    

}
vector<pair<float,float>> vecxy;
vector<pair<float,float>> vecxy2;
float inicio=0.75;
float angel=0;
int rot=0;


void movement(GLFWwindow* window)
{
    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}

void display( GLFWwindow* window )
{
/*
    vecxy.push_back(pair<float,float>(0.75,0.75));
    vecxy.push_back(pair<float,float>(0.25,0.75));
    vecxy.push_back(pair<float,float>(-0.25,0.75));
    vecxy.push_back(pair<float,float>(0.75,0.25));
    vecxy.push_back(pair<float,float>(0.25,0.25));
    vecxy.push_back(pair<float,float>(-0.25,0.25));
    vecxy.push_back(pair<float,float>(0.75,-0.25));
    vecxy.push_back(pair<float,float>(0.25,-0.25));
    vecxy.push_back(pair<float,float>(-0.25,-0.25));

    
    float z=-0.75;

    vector<vector<cubo*>> plano1;
    for (int i = 0; i < 3; ++i)
    {
        vector<cubo*> r;
        cubo *a=new cubo(vecxy[(i*3)+0].first, vecxy[(i*3)+0].second, z, 0.75);
        r.push_back(a);
        cubo *b=new cubo(vecxy[(i*3)+1].first, vecxy[(i*3)+1].second, z, 0.75);
        r.push_back(b);
        cubo *c=new cubo(vecxy[(i*3)+2].first, vecxy[(i*3)+2].second, z, 0.75);
        r.push_back(c);

        plano1.push_back(r);
    }

    rubik.push_back(plano1);


    z=-0.25;

    vector<vector<cubo*>> plano2;
    for (int i = 0; i < 3; ++i)
    {
        vector<cubo*> r;
        cubo *a=new cubo(vecxy[(i*3)+0].first, vecxy[(i*3)+0].second, z, 0.75);
        r.push_back(a);
        cubo *b=new cubo(vecxy[(i*3)+1].first, vecxy[(i*3)+1].second, z, 0.75);
        r.push_back(b);
        cubo *c=new cubo(vecxy[(i*3)+2].first, vecxy[(i*3)+2].second, z, 0.75);
        r.push_back(c);

        plano2.push_back(r);
    }
    rubik.push_back(plano2);


    z=0.25;
    vector<vector<cubo*>> plano3;
    for (int i = 0; i < 3; ++i)
    {
        vector<cubo*> r;
        cubo *a=new cubo(vecxy[(i*3)+0].first, vecxy[(i*3)+0].second, z, 0.75);
        r.push_back(a);
        cubo *b=new cubo(vecxy[(i*3)+1].first, vecxy[(i*3)+1].second, z, 0.75);
        r.push_back(b);
        cubo *c=new cubo(vecxy[(i*3)+2].first, vecxy[(i*3)+2].second, z, 0.75);
        r.push_back(c);

        plano3.push_back(r);
    }
    rubik.push_back(plano3);

*/

    v_eye[0]=0;
    v_eye[1]=1;
    v_eye[2]=3;

    up[0]=0;
    up[1]=1;
    up[2]=0;

    vc[0]=0;
    vc[1]=0;
    vc[2]=0;
    cubo an;

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // Draw stuff
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.1, 100 );
        gluLookAt(v_eye[0], v_eye[1], v_eye[2], vc[0], vc[1], vc[2], up[0], up[1], up[2]);

        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(0,0,0);
/*
        for (int k = 0; k < 3; ++k)
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    rubik[k][i][j]->drawCube(inicio);
                }
                
            }
        }*/

        an.dibujar();

            
        // Update Screen
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}

int dim=1;

int main(int argc, char** argv)
{
    cout<<endl;
    cout<<"                             Bienvenido a Rubik"<<endl;
    cout<<endl; 
    cout<<"                                 CONTROLES"<<endl;
    cout<<"Rotar camara:            Teclas de RIGHT - LEFT"<<endl;
    cout<<"Subir y bajar camara:    Teclas UP - DOWN"<<endl;
    cout<<"Acercar y Alejar camara: Scroll del Mouse"<<endl;
    cout<<"Rotar Camadas:           R   rotar en el eje Z"<<endl;
    cout<<"                         F   rotar en el eje Y"<<endl;
    cout<<"                         V   rotar en el eje X"<<endl;
    cout<<"Efecto de Explosion:     S"<<endl;
    cout<<endl;
    
    
    GLFWwindow* window = initWindow(1024, 620);
    if( NULL != window )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

float _an=90;

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        if(key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS )
    {
        float radius = 5.0f;
        v_eye[0] = sin(glfwGetTime())*radius;
        v_eye[2] = cos(glfwGetTime())*radius;

    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS )
    {
        float radius = 5.0f;
        v_eye[0] = sin(glfwGetTime())*radius;
        v_eye[1] = cos(glfwGetTime())*radius;
    }
/*
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS )
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                rubik[dim-1][j][i]->rotarZ(_an);
            }
        }
        rot=1;
        angel=angel+5;
        rotarVecZ(dim-1);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS )
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                rubik[j][dim-1][i]->rotarY(_an);
            }
        }
        rot=2;
        angel=angel+5;
        rotarVecY(dim-1);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS )
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                rubik[j][i][dim-1]->rotarX(_an);
            }
        }
        rot=3;
        angel=angel+5;
        rotarVecX(dim-1);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
    {
        vector<vector<vector<cubo*>>> rubik2;

        vecxy2.push_back(pair<float,float>(1,1));
        vecxy2.push_back(pair<float,float>(0.25,1));
        vecxy2.push_back(pair<float,float>(-0.5,1));
        vecxy2.push_back(pair<float,float>(1,0.25));
        vecxy2.push_back(pair<float,float>(0.25,0.25));
        vecxy2.push_back(pair<float,float>(-0.5,0.25));
        vecxy2.push_back(pair<float,float>(1,-0.5));
        vecxy2.push_back(pair<float,float>(0.25,-0.5));
        vecxy2.push_back(pair<float,float>(-0.5,-0.5));

        float z=-1.0;

        vector<vector<cubo*>> plano1;
        for (int i = 0; i < 3; ++i)
        {
            vector<cubo*> r;
            cubo *a=new cubo(vecxy2[(i*3)+0].first, vecxy2[(i*3)+0].second, z, 1.0);
            r.push_back(a);
            cubo *b=new cubo(vecxy2[(i*3)+1].first, vecxy2[(i*3)+1].second, z, 1.0);
            r.push_back(b);
            cubo *c=new cubo(vecxy2[(i*3)+2].first, vecxy2[(i*3)+2].second, z, 1.0);
            r.push_back(c);

            plano1.push_back(r);
        }

        rubik2.push_back(plano1);


        z=-0.25;

        vector<vector<cubo*>> plano2;
        for (int i = 0; i < 3; ++i)
        {
            vector<cubo*> r;
            cubo *a=new cubo(vecxy2[(i*3)+0].first, vecxy2[(i*3)+0].second, z, 1.0);
            r.push_back(a);
            cubo *b=new cubo(vecxy2[(i*3)+1].first, vecxy2[(i*3)+1].second, z, 1.0);
            r.push_back(b);
            cubo *c=new cubo(vecxy2[(i*3)+2].first, vecxy2[(i*3)+2].second, z, 1.0);
            r.push_back(c);

            plano2.push_back(r);
        }
        rubik2.push_back(plano2);


        z=0.5;
        vector<vector<cubo*>> plano3;
        for (int i = 0; i < 3; ++i)
        {
            vector<cubo*> r;
            cubo *a=new cubo(vecxy2[(i*3)+0].first, vecxy2[(i*3)+0].second, z, 1.0);
            r.push_back(a);
            cubo *b=new cubo(vecxy2[(i*3)+1].first, vecxy2[(i*3)+1].second, z, 1.0);
            r.push_back(b);
            cubo *c=new cubo(vecxy2[(i*3)+2].first, vecxy2[(i*3)+2].second, z, 1.0);
            r.push_back(c);

            plano3.push_back(r);
        }
        rubik2.push_back(plano3);

        for (int i = 0; i < rubik.size(); ++i)
        {
            rubik[i]=rubik2[i];
        }
        inicio=1.0;

    }
*/
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS )
      {
        vc[1]-=0.01;
      }
      
      if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS )
      {
        vc[1]+=0.01;
      }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS )
    {
        dim=1;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS )
    {
        dim=2;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS )
    {
        dim=3;
    }

    if(rot==1 && angel>90){
        rot=0;
    }
    else if(rot==2 && angel==90){
        rot=0;
    }
    else if(rot==3 && angel==90){
        rot=0;
    }

}
