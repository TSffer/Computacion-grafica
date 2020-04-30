#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <cmath>
#include <stb_image.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace glm;

int NIVEL = 6;

unsigned char* data;
string FILENAME_TEXTURES = "";
string FILENAME_SHADERS = "";
int w, h, nrChannels, I = 0;
float axisX = 0.0f, axisY = 1.0f, axisZ = 0.0f, degrees_ = 10.0f;

const int WIDTH = 800, HEIGHT = 600;

vec3 TRIANGLE[3];

GLuint VAO, VBO;
unsigned int VBO2, VAO2;
int shaderProgram;
int shaderProgram2;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Triangle 
{
	public:
		vec3 pLeftButton, pRightButton, pTop;
		vec3 color = {0.0 , 0.0, 0.0};
		Triangle(float *triangle_vertex)
		{
			this->pLeftButton = vec3(triangle_vertex[0], triangle_vertex[1], triangle_vertex[2]);
			this->pRightButton = vec3(triangle_vertex[3], triangle_vertex[4], triangle_vertex[5]);
			this->pTop = vec3(triangle_vertex[6], triangle_vertex[7], triangle_vertex[8]);
		}

		void setColor(int i)
		{
			this->color[i] = 1.0;
		}
};

void readTexture(string arch)
{
	unsigned char* data = stbi_load( (FILENAME_TEXTURES + "img" + arch).c_str() ,&w, &h, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout<<"Failed to load texture"<<endl; 
	}
	stbi_image_free(data);
}

static char *readShaderSource(const char *filename_s) 
{
	FILE *File = fopen(filename_s, "rb");
	if (File == NULL) 
		return NULL;

	fseek(File, 0L, SEEK_END);
	long size = ftell(File);

	rewind(File);
	char *buffer = new char[size + 1];
	fread(buffer, 1, size, File);
	buffer[size] = '\0';
	fclose(File);

	return buffer;
}

void createTriangle() 
{
	float vertices[] = 
	{
		-0.7f, -0.7f, 0.0f,
		 0.7f, -0.7f, 0.0f,
		 0.0f,  0.7f, 0.0f
	};

	Triangle t(vertices);
	t.setColor(0);
	vector<Triangle> vcord;
	vcord.push_back(t);

	for (int i = 0; i < NIVEL; i++)
	{
		int s = vcord.size();

		for (int j = 0; j < s; j++)
		{
			vec3 p12 = (vcord.begin()->pLeftButton + vcord.begin()->pRightButton) / 2.0f;
			vec3 p13 = (vcord.begin()->pLeftButton + vcord.begin()->pTop) / 2.0f;
			vec3 p23 = (vcord.begin()->pRightButton + vcord.begin()->pTop) / 2.0f;

			GLfloat t1[] = {vcord.begin()->pLeftButton.x, vcord.begin()->pLeftButton.y, vcord.begin()->pLeftButton.z,p12.x, p12.y, p12.z, p13.x, p13.y, p13.z};
			GLfloat t2[] = {p12.x, p12.y, p12.z,vcord.begin()->pRightButton.x, vcord.begin()->pRightButton.y, vcord.begin()->pRightButton.z,p23.x, p23.y, p23.z};
			GLfloat t3[] = {p13.x, p13.y, p13.z, p23.x, p23.y, p23.z,vcord.begin()->pTop.x, vcord.begin()->pTop.y, vcord.begin()->pTop.z};
			
			Triangle tg1(t1); tg1.setColor(j%3);
			Triangle tg2(t2); tg2.setColor(j%3);
			Triangle tg3(t3); tg3.setColor(j%3);
			vcord.push_back(tg1); vcord.push_back(tg2); vcord.push_back(tg3);
			vcord.erase(vcord.begin());
		}
	}

	int size = vcord.size();
	float coords[size * 18];
	for (int i = 0; i < size; i++)
	{
		coords[i * 18 + 0] = vcord.begin()->pLeftButton.x;
		coords[i * 18 + 1] = vcord.begin()->pLeftButton.y;
		coords[i * 18 + 2] = vcord.begin()->pLeftButton.z;
		coords[i * 18 + 3] = vcord.begin()->color.x;
		coords[i * 18 + 4] = vcord.begin()->color.y;
		coords[i * 18 + 5] = vcord.begin()->color.z;
		coords[i * 18 + 6] = vcord.begin()->pRightButton.x;
		coords[i * 18 + 7] = vcord.begin()->pRightButton.y;
		coords[i * 18 + 8] = vcord.begin()->pRightButton.z;
		coords[i * 18 + 9] = vcord.begin()->color.x;
		coords[i * 18 + 10] = vcord.begin()->color.y;
		coords[i * 18 + 11] = vcord.begin()->color.z;
		coords[i * 18 + 12] = vcord.begin()->pTop.x;
		coords[i * 18 + 13] = vcord.begin()->pTop.y;
		coords[i * 18 + 14] = vcord.begin()->pTop.z;
		coords[i * 18 + 15] = vcord.begin()->color.x;
		coords[i * 18 + 16] = vcord.begin()->color.y;
		coords[i * 18 + 17] = vcord.begin()->color.z;
		vcord.erase(vcord.begin());
	}
	
	/////////////////////////////////////////
	float vertTexture[] = {
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f
	};

	unsigned int indices[] = {  
        0, 1, 3,
        1, 2, 3  
    };

	unsigned int EBO;
	glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertTexture), vertTexture, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
	////////////////////////////////

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void addShader(GLuint theProgram, const char *shaderFile, GLenum shaderType) 
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar *theCode[1];
	theCode[0] = readShaderSource(shaderFile);

	glShaderSource(theShader, 1, theCode, NULL);
	glCompileShader(theShader);

	glAttachShader(theProgram, theShader);
}

void compileShaders() 
{
	shaderProgram = glCreateProgram();
	addShader(shaderProgram, (FILENAME_SHADERS + "vshader.glsl").c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram, (FILENAME_SHADERS + "fshader.glsl").c_str(), GL_FRAGMENT_SHADER);
	glLinkProgram(shaderProgram);

	shaderProgram2 = glCreateProgram();
	addShader(shaderProgram2, (FILENAME_SHADERS +  "vshader_t.glsl").c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram2, (FILENAME_SHADERS + "fshader_t.glsl").c_str(), GL_FRAGMENT_SHADER);
	glLinkProgram(shaderProgram2);
	//glValidateProgram(shaderProgram2);
}

int main() 
{
	//COLOQUE LA RUTA DE LAS CARPETAS
	FILENAME_TEXTURES = "/home/luis/Documentos/Computacion-Grafica/Sierpinski_triangle/Textures/";
	FILENAME_SHADERS = "/home/luis/Documentos/Computacion-Grafica/Sierpinski_triangle/src/";

	auto t_start = chrono::high_resolution_clock::now();
	
	if (!glfwInit()) 
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *Window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);
	if (Window == NULL) 
	{
		cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(Window, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(Window);
	glfwSetKeyCallback(Window,key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

	glViewport(0, 0, bufferWidth, bufferHeight);

	createTriangle();
	compileShaders();

	//Texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	readTexture("0.jpg");

	GLint uniTrans = glGetUniformLocation(shaderProgram, "transform");
	while (!glfwWindowShouldClose(Window)) 
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto t_now = chrono::high_resolution_clock::now();
		float time = chrono::duration_cast<chrono::duration<float>>(t_now - t_start).count();
		//cout << time <<endl;
		mat4 transform = mat4(1.0f);
		transform = rotate(transform, time * radians(degrees_), vec3(axisX, axisY, axisZ));
		
		//glUniformMatrix4fv(uniTrans, 1, GL_FALSE, value_ptr(transform));

		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);

		int vertexColorLocation1 = glGetUniformLocation(shaderProgram, "transform");
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, pow(3, NIVEL + 1));
		//glUniform4f(vertexColorLocation1,transform));
		glUniformMatrix4fv(vertexColorLocation1, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window,GL_TRUE);
	else if(key == GLFW_KEY_X && action == GLFW_PRESS)
	{axisX = 1.0f; axisY = 0.0f; axisZ = 0.0f;}
	else if(key == GLFW_KEY_Y && action == GLFW_PRESS)
	{axisX = 0.0f; axisY = 1.0f; axisZ = 0.0f;}
	else if(key == GLFW_KEY_Z && action == GLFW_PRESS)
	{axisX = 0.0f; axisY = 0.0f; axisZ = 1.0f;}
	else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{degrees_ < 360.0f ? degrees_ = degrees_ + 20.0f: degrees_ = degrees_;}
	else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{degrees_ > -360.0f ? degrees_ = degrees_ - 20.0f: degrees_ = degrees_;}
	else if(key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		(I > 0) ? I--: I = 4;
		readTexture((to_string(I)+".jpg"));
	}
	else if(key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		(I < 4) ? I++: I = 0;
		readTexture((to_string(I)+".jpg"));
	}
}
