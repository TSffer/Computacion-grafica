#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaders.h"

using namespace std;

float rot = 1;
GLfloat eyeloc = 4.0 ; 
GLuint vertexshader, fragmentshader, shaderprogram; 
GLuint projectionPos, modelviewPos, scalePos; 
glm::mat4 projection, modelview, scale; 

float radius = 5.0f;
float camX=2.0;
float camY=1.0;
float camZ=4.0;


glm::vec3 cameraPos = glm::vec3(0.0f,eyeloc, eyeloc);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.5f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, -1.0f);


const int numobjects = 3;  
const int numperobj  = 3;
GLuint VAOs[numobjects]; 
GLuint buffers[numperobj*numobjects]; 
GLuint objects[numobjects]; 
GLenum PrimType[numobjects]; 
GLsizei NumElems[numobjects]; 

enum {Vertices, Colors, Elements} ;  
enum {CUBE, PYRAMID, DIAMOND}; 

const GLfloat Cube[24][3] = {
	{-0.6, 0.0, 0.4}, {-0.6, 0.0, -0.4}, {-1.4, 0.0, -0.4}, {-1.4,0.0, 0.4},
	{-0.6, 0.8, 0.4}, {-0.6, 0.8, -0.4}, {-1.4, 0.8, -0.4}, {-1.4,0.8, 0.4},

	{-0.6, 0.0, 0.4}, {-0.6, 0.0, -0.4}, {-0.6, 0.8, 0.4}, {-0.6, 0.8, -0.4},
	{-1.4,0.0, 0.4}, {-1.4, 0.0, -0.4},{-1.4,0.8, 0.4}, {-1.4, 0.8, -0.4},

	{-1.4,0.0, 0.4}, {-0.6, 0.0, 0.4},  {-1.4,0.8, 0.4},  {-0.6, 0.8, 0.4},
	{-1.4, 0.0, -0.4}, {-0.6, 0.0, -0.4}, {-1.4, 0.8, -0.4}, {-0.6, 0.8, -0.4},

//	{0.5, 0.0, 0.5}, {0.5, 0.0, -0.5}, {-0.5, 0.0, -0.5}, {-0.5,0.0, 0.5},
//	{0.5, 1.0, 0.5}, {0.5, 1.0, -0.5}, {-0.5, 1.0, -0.5}, {-0.5,1.0, 0.5},

//	{0.5, 0.0, 0.5}, {0.5, 0.0, -0.5}, {-0.5, 0.0, -0.5}, {-0.5,0.0, 0.5},
//	{0.5, 1.0, 0.5}, {0.5, 1.0, -0.5}, {-0.5, 1.0, -0.5}, {-0.5,1.0, 0.5}

}; 

const GLfloat Cubecol[24][3] = {
  	{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0},
   	{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0},
	{0.0, 1.0, 1.0}, {0.0, 1.0, 1.0}, {0.0, 1.0, 1.0}, {0.0, 1.0, 1.0},
	{1.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 0.0},
	{1.0, 0.3, 0.0}, {1.0, 0.3, 0.0}, {1.0, 0.3, 0.0}, {1.0, 0.3, 0.0}
}; 

const GLubyte Cubeinds[6][6] = { 
									{0, 1, 2, 0, 3, 2}, {4, 5, 6, 4, 7, 6},
									{9, 8, 10, 9, 11, 10}, {13, 12, 14, 13, 15, 14},
									{17, 16, 18, 17, 19, 18}, {21, 20, 22, 21, 23, 22}
						          //{8, 9, 13, 8, 12, 13}, {11, 10, 14, 11, 15, 14}, 
								  //{16, 20, 23, 16, 19, 23}, {17, 21, 22, 17, 18, 22} 
								}; 


//////////////////////////////////////////////////////////////////7


const GLfloat Diamond[24][3] = {
	{0.6, 0.4, 0.4}, {1.4, 0.4, 0.4}, {1.0, 0.8, 0.0}, 
	{0.6, 0.4, -0.4}, {1.4, 0.4, -0.4}, {1.0, 0.8, 0.0}, 

	{0.6, 0.4, 0.4}, {0.6, 0.4, -0.4}, {1.0, 0.8, 0.0}, 
	{1.4, 0.4, 0.4}, {1.4, 0.4, -0.4}, {1.0, 0.8, 0.0}, 

	{0.6, 0.4, 0.4}, {1.4, 0.4, 0.4}, {1.0, 0.0, 0.0}, 
	{0.6, 0.4, -0.4}, {1.4, 0.4, -0.4}, {1.0, 0.0, 0.0},

	{0.6, 0.4, 0.4}, {0.6, 0.4, -0.4}, {1.0, 0.0, 0.0}, 
	{1.4, 0.4, 0.4}, {1.4, 0.4, -0.4}, {1.0, 0.0, 0.0}
}; 

const GLfloat Diamondcol[24][3] = {
  	{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, 
	{0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, 

   	{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 
	{1.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, 

	{1.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, 
	{1.0, 0.0, 0.5}, {1.0, 0.0, 0.5}, {1.0, 0.0, 0.5},
		
	{0.0, 0.1, 0.1}, {0.0, 0.1, 0.1}, {0.0, 0.1, 0.1}, 
	{1.0, 0.5, 0.5}, {1.0, 0.5, 0.5}, {1.0, 0.5, 0.5}
}; 

const GLubyte Diamondinds[8][3] = { 
									{0, 1, 2}, {3, 4, 5},
									{6, 7, 8}, {9, 10, 11},
									{12, 13, 14}, {15, 16, 17},
									{18, 19, 20}, {21, 22, 23}
								}; 

///////////////////////////////////////////////////////////////////////

const GLfloat Pyramid[18][3] = {
	{-0.4, 0.0, 0.4}, {0.4, 0.0, 0.4}, {0.0, 0.8, 0.0}, 
	{-0.4, 0.0, -0.4}, {0.4, 0.0, -0.4}, {0.0, 0.8, 0.0}, 

	{-0.4, 0.0, 0.4}, {-0.4, 0.0, -0.4}, {0.0, 0.8, 0.0}, 
	{0.4, 0.0, 0.4}, {0.4, 0.0, -0.4}, {0.0, 0.8, 0.0}, 

	{-0.4, 0.0, 0.4}, {0.4, 0.0, 0.4}, {0.4, 0.0, -0.4}, 
	{-0.4, 0.0, 0.4}, {0.4, 0.0, 0.4}, {-0.4, 0.0, -0.4},
}; 

const GLfloat Pyramidcol[18][3] = {
  	{0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, 
	{0.5, 1.0, 1.0}, {0.5, 1.0, 1.0}, {0.5, 1.0, 1.0}, 

   	{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, 
	{0.0, 0.5, 1.0}, {0.0, 0.5, 1.0}, {0.0, 0.5, 1.0}, 

	{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 
	{1.0, 0.3, 0.0}, {1.0, 0.3, 0.0}, {1.0, 0.3, 0.0},
	
}; 

const GLubyte Pyramidinds[8][3] = { 
									{0, 1, 2}, {3, 4, 5},
									{6, 7, 8}, {9, 10, 11},
									{12, 13, 14}, {12, 17, 14},
								}; 

void deleteBuffers() 
{
	glDeleteVertexArrays(numobjects, VAOs);
	glDeleteBuffers(numperobj*numobjects, buffers);
}


void initobject(GLuint object, GLfloat * vert, GLint sizevert, GLfloat * col, GLint sizecol, GLubyte * inds, GLint sizeind, GLenum type)
{
  int offset = object * numperobj;
  glBindVertexArray(VAOs[object]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices+offset]) ; 
  glBufferData(GL_ARRAY_BUFFER, sizevert, vert,GL_STATIC_DRAW);
  // Use layout location 0 for the vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors+offset]) ; 
  glBufferData(GL_ARRAY_BUFFER, sizecol, col,GL_STATIC_DRAW);
  // Use layout location 1 for the colors
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements+offset]) ; 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeind, inds,GL_STATIC_DRAW);
  PrimType[object] = type;
  NumElems[object] = sizeind;
  // Prevent further modification of this VAO by unbinding it
  glBindVertexArray(0);
}

void drawobject(GLuint object) 
{
	glBindVertexArray(VAOs[object]);
	glDrawElements(PrimType[object], NumElems[object], GL_UNSIGNED_BYTE, 0); 
	glBindVertexArray(0);
}

void display(GLFWwindow* window)
{	
	glClear (GL_COLOR_BUFFER_BIT); 
	drawobject(CUBE);
	drawobject(PYRAMID); 
	drawobject(DIAMOND); 
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
	{
		deleteBuffers();
		glfwSetWindowShouldClose(window, true);
	}
   	else if(key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		rot = rot + 0.5;
		camX   = sin(rot) * radius;
        camZ   = cos(rot) * radius;
	}
	else if(key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		rot = rot - 0.5;
		camX   = sin(rot) * radius;
        camZ   = cos(rot) * radius;
	}
	else if(key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		rot = rot + 0.5;
		camY   = cos(rot) * radius;
      //  camZ   = sin(rot) * radius;
	}
	else if(key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		rot = rot - 0.5;
		camY   = cos(rot) * radius;
        //camZ   = sin(rot) * radius;
	}
	else if(key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		camX = 2.0;
		camY = 1.0;
		camZ = 4.0;
	}
}


void reshape_callback(GLFWwindow* window, int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	
	if (h > 0)
	{
		projection = glm::perspective(glm::radians(45.0f), (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
		glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
	}
}

void init (void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values  */
	projection = glm::mat4(1.0f); 
	scale = glm::mat4(1.0f);	

	// modelview = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.5, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelview = glm::lookAt(glm::vec3(2, 1, 4), glm::vec3(0.0f, 0.5, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f));

	glGenVertexArrays(numobjects, VAOs);
	glGenBuffers(numperobj*numobjects, buffers);

	// Initialize the floors
	initobject(CUBE, (GLfloat *) Cube, sizeof(Cube), (GLfloat *) Cubecol, sizeof (Cubecol), (GLubyte *) Cubeinds, sizeof (Cubeinds), GL_TRIANGLES) ; 
	initobject(DIAMOND, (GLfloat *) Diamond, sizeof(Diamond), (GLfloat *) Diamondcol, sizeof (Diamondcol), (GLubyte *) Diamondinds, sizeof (Diamondinds), GL_TRIANGLES) ; 
	initobject(PYRAMID, (GLfloat *) Pyramid, sizeof(Pyramid), (GLfloat *) Pyramidcol, sizeof (Pyramidcol), (GLubyte *) Pyramidinds, sizeof (Pyramidinds), GL_TRIANGLES) ; 

	std::string vertex_shader_path;
	std::string fragment_shader_path;

	#ifdef __unix__         
	vertex_shader_path = "/home/luis/Documentos/github/Computacion-grafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Ejercicio_LookAt/shaders/nop.vert";
	fragment_shader_path = "/home/luis/Documentos/github/Computacion-grafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Ejercicio_LookAt/shaders/nop.frag";

	#elif defined(_WIN32) || defined(WIN32) 
	vertex_shader_path = "/home/luis/Documentos/github/Computacion-grafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Ejercicio_LookAt/shaders/nop.vert";
	fragment_shader_path = "/home/luis/Documentos/github/Computacion-grafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Ejercicio_LookAt/shaders/nop.frag";
	#endif


	// Initialize the shader program
	vertexshader = initshaders(GL_VERTEX_SHADER, vertex_shader_path.c_str());
	fragmentshader = initshaders(GL_FRAGMENT_SHADER, fragment_shader_path.c_str());

	shaderprogram = initprogram(vertexshader, fragmentshader) ;

	// Get the positions of the uniform variables
	projectionPos = glGetUniformLocation(shaderprogram, "projection");
	modelviewPos = glGetUniformLocation(shaderprogram, "modelview");
	scalePos = glGetUniformLocation(shaderprogram, "scale");
	// Pass the projection and modelview matrices to the shader
	glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
	glUniformMatrix4fv(scalePos, 1, GL_FALSE, &scale[0][0]);
}

int main(int argc, char** argv)
{
	cout<<"A : Mover a la Izquierda "<<endl;
	cout<<"D : Mover a la Derecha "<<endl;
	cout<<"W : Mover Arriba "<<endl;
	cout<<"S : Mover Abajo "<<endl;
	cout<<"R : Reset "<<endl;
	cout<<"\n"<<endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(600, 550, "Simple Demo with Shaders", NULL, NULL);
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 200, 200);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	init (); 

	glfwSetFramebufferSizeCallback(window, reshape_callback);	
	glfwSetKeyCallback(window, key_callback);					

	
	reshape_callback(window, 600, 550);
	display(window); 
  
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)500 / (GLfloat)500, 1.0f, 100.0f);
	glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
	//cameraPos = glm::vec3(0.0f,eyeloc, eyeloc);
	//cameraFront = glm::vec3(0.0f, 0.5f, 0.0f);
	//cameraUp = glm::vec3(0.0f, 0.0f, -1.0f);
	int act = 0;
    int acs = 0;
	while (!glfwWindowShouldClose(window))  
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(window); 

		modelview = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.5, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//SCALE

		if(act < 5000)
        {
            scale = glm::scale(scale, glm::vec3(1.00009f, 1.00009f, 1.00009f));   //Aumenta el tamaño del triangulo
            act++;
        }
        else if(act == 5000 and acs < 5000)
        {
            scale = glm::scale(scale, glm::vec3(0.9999f, 0.9999f, 0.9999f));     //Reduce el tamaño del triangulo
            acs++;  
        }
        if(acs == 5000){act = 0;acs = 0;}

		glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
		glUniformMatrix4fv(scalePos, 1, GL_FALSE, &scale[0][0]);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	deleteBuffers(); 
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;   

}