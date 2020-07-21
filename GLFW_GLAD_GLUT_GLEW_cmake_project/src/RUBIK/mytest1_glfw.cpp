#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdio>
#include <iostream>
#include <math.h>
#include "matriz.cpp"

using namespace std;
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

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

class cubo
{
public:
    float l=0.5;
    float xi, yi, zi;
    GLfloat vertices[72];
    GLfloat colors[72];
    cubo(float _xi, float _yi, float _zi){
        xi=_xi;     yi=_yi;     zi=_zi;
        for (int i = 0; i < 72; ++i)
        {
            vertices[i]=0.0;
        }

        vertices[0]=xi;     vertices[1]=yi;     vertices[2]=zi;     vertices[3]=xi-l;       vertices[4]=yi;     vertices[5]=zi;     vertices[6]=xi-l;   vertices[7]=yi-l;       vertices[8]=zi;     vertices[9]=xi;     vertices[10]=yi-l;      vertices[11]=zi;
        vertices[12]=xi;    vertices[13]=yi;    vertices[14]=zi+l;  vertices[15]=xi-l;      vertices[16]=yi;    vertices[17]=zi+l;  vertices[18]=xi-l;  vertices[19]=yi-l;      vertices[20]=zi+l;  vertices[21]=xi;    vertices[22]=yi-l;      vertices[23]=zi+l;
        vertices[24]=xi;     vertices[25]=yi;     vertices[26]=zi;  vertices[27]=xi-l;      vertices[28]=yi;    vertices[29]=zi;    vertices[30]=xi-l;  vertices[31]=yi;        vertices[32]=zi+l;  vertices[33]=xi;    vertices[34]=yi;        vertices[35]=zi+l; 
        vertices[36]=xi-l;   vertices[37]=yi-l;   vertices[38]=zi;  vertices[39]=xi;        vertices[40]=yi-l;  vertices[41]=zi;    vertices[42]=xi;    vertices[43]=yi-l;      vertices[44]=zi+l;  vertices[45]=xi-l;  vertices[46]=yi-l;      vertices[47]=zi+l;
        vertices[48]=xi;     vertices[49]=yi;     vertices[50]=zi;  vertices[51]=xi;        vertices[52]=yi;    vertices[53]=zi+l;  vertices[54]=xi;    vertices[55]=yi-l;      vertices[56]=zi+l;  vertices[57]=xi;    vertices[58]=yi-l;      vertices[59]=zi;
        vertices[60]=xi-l;   vertices[61]=yi;     vertices[62]=zi;  vertices[63]=xi-l;      vertices[64]=yi;    vertices[65]=zi+l;  vertices[66]=xi-l;  vertices[67]=yi-l;      vertices[68]=zi+l;  vertices[69]=xi-l;  vertices[70]=yi-l;      vertices[71]=zi;
    }
    void drawCube()
    {
        GLfloat colors[]={
            1, 0, 0,      1, 0, 0,      1, 0, 0,      0, 0, 0,
            0, 1, 0,      0, 1, 0,      0, 1, 0,      0, 0, 0,
            0, 0, 1,      0, 0, 1,      0, 0, 1,      0, 0, 0,
            1, 1, 1,      1, 1, 1,      1, 1, 1,      0, 0, 0,
            1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0,    0, 0, 0,
            1, 1, 0,      1, 1, 0,      1, 1, 0,      0, 0, 0
        };

        
        //attempt to rotate cube
        glRotatef(alpha, 0, 0, -1);

        /* We have a color array and a vertex array */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        /* Send data : 24 vertices */
        glDrawArrays(GL_QUADS, 0, 24);

        /* Cleanup states */
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
void display( GLFWwindow* window )
{

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
        cubo *a=new cubo(vecxy[(i*3)+0].first, vecxy[(i*3)+0].second, z);
        r.push_back(a);
        cubo *b=new cubo(vecxy[(i*3)+1].first, vecxy[(i*3)+1].second, z);
        r.push_back(b);
        cubo *c=new cubo(vecxy[(i*3)+2].first, vecxy[(i*3)+2].second, z);
        r.push_back(c);

        plano1.push_back(r);
    }

    rubik.push_back(plano1);


    z=-0.25;

    vector<vector<cubo*>> plano2;
    for (int i = 0; i < 3; ++i)
    {
        vector<cubo*> r;
        cubo *a=new cubo(vecxy[(i*3)+0].first, vecxy[(i*3)+0].second, z);
        r.push_back(a);
        cubo *b=new cubo(vecxy[(i*3)+1].first, vecxy[(i*3)+1].second, z);
        r.push_back(b);
        cubo *c=new cubo(vecxy[(i*3)+2].first, vecxy[(i*3)+2].second, z);
        r.push_back(c);

        plano2.push_back(r);
    }
    rubik.push_back(plano2);


    z=0.25;
    vector<vector<cubo*>> plano3;
    for (int i = 0; i < 3; ++i)
    {
        vector<cubo*> r;
        cubo *a=new cubo(vecxy[(i*3)+0].first, vecxy[(i*3)+0].second, z);
        r.push_back(a);
        cubo *b=new cubo(vecxy[(i*3)+1].first, vecxy[(i*3)+1].second, z);
        r.push_back(b);
        cubo *c=new cubo(vecxy[(i*3)+2].first, vecxy[(i*3)+2].second, z);
        r.push_back(c);

        plano3.push_back(r);
    }
    rubik.push_back(plano3);



    v_eye[0]=0;
    v_eye[1]=1;
    v_eye[2]=3;

    up[0]=0;
    up[1]=1;
    up[2]=0;

    vc[0]=0;
    vc[1]=0;
    vc[2]=0;

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        // Scale to window size
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

        for (int k = 0; k < 3; ++k)
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    rubik[k][i][j]->drawCube();
                }
                
            }
        }
            
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

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS )
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                rubik[dim-1][j][i]->rotarZ(90);
            }
        }
        rotarVecZ(dim-1);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS )
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                rubik[j][dim-1][i]->rotarY(90);
            }
        }
        rotarVecY(dim-1);
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
            cubo *a=new cubo(vecxy2[(i*3)+0].first, vecxy2[(i*3)+0].second, z);
            r.push_back(a);
            cubo *b=new cubo(vecxy2[(i*3)+1].first, vecxy2[(i*3)+1].second, z);
            r.push_back(b);
            cubo *c=new cubo(vecxy2[(i*3)+2].first, vecxy2[(i*3)+2].second, z);
            r.push_back(c);

            plano1.push_back(r);
        }

        rubik2.push_back(plano1);


        z=-0.25;

        vector<vector<cubo*>> plano2;
        for (int i = 0; i < 3; ++i)
        {
            vector<cubo*> r;
            cubo *a=new cubo(vecxy2[(i*3)+0].first, vecxy2[(i*3)+0].second, z);
            r.push_back(a);
            cubo *b=new cubo(vecxy2[(i*3)+1].first, vecxy2[(i*3)+1].second, z);
            r.push_back(b);
            cubo *c=new cubo(vecxy2[(i*3)+2].first, vecxy2[(i*3)+2].second, z);
            r.push_back(c);

            plano2.push_back(r);
        }
        rubik2.push_back(plano2);


        z=0.5;
        vector<vector<cubo*>> plano3;
        for (int i = 0; i < 3; ++i)
        {
            vector<cubo*> r;
            cubo *a=new cubo(vecxy2[(i*3)+0].first, vecxy2[(i*3)+0].second, z);
            r.push_back(a);
            cubo *b=new cubo(vecxy2[(i*3)+1].first, vecxy2[(i*3)+1].second, z);
            r.push_back(b);
            cubo *c=new cubo(vecxy2[(i*3)+2].first, vecxy2[(i*3)+2].second, z);
            r.push_back(c);

            plano3.push_back(r);
        }
        rubik2.push_back(plano3);

        for (int i = 0; i < rubik.size(); ++i)
        {
            rubik[i]=rubik2[i];
        }

    }

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS )
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                rubik[j][i][dim-1]->rotarX(90);
            }
        }
        rotarVecX(dim-1);
    }

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

}