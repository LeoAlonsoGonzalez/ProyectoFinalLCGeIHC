/*---------------------------------------------------------*/
/* ----------------   Práctica 3 --------------------------*/
/*-----------------    2021-2   ---------------------------*/
/*-------Alumno:Leonardo Alonso González Pacheco --------------*/
/*-------Cuenta: 313221136 ------------------*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO[2], VAO[2], EBO[2];

void myData(void);
void getResolution(void);

//For Keyboard

float movX = 0.0f,
	  movY = 0.0f,
      movZ = -40.0f;

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	

	GLfloat verticesCubo[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	GLfloat verticesLuis[] = {
		// positions			//Color
		-0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 0.0f,	//V0
		0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 1.0f,	//V1
		0.5f, 0.3f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		-0.2f, 0.3f, -0.5f,		1.0f, 1.0f, 0.0f,	//V3
		-0.2f, -0.3f, -0.5f,	0.0f, 1.0f, 0.0f,	//V4
		0.5f, -0.3f, -0.5f,		0.0f, 1.0f, 1.0f,	//V5
		0.5f, -0.7f, -0.5f,		0.0f, 0.0f, 1.0f,	//V6
		-0.5f, -0.7f, -0.5f,	1.0f, 1.0f, 1.0f,	//V7

		//-0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 0.0f,	//V0
		//0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 1.0f,	//V1
		//-0.2f, 0.3f, -0.5f,		1.0f, 1.0f, 0.0f,	//V3

		//0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 1.0f,	//V1
		//0.5f, 0.3f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		//-0.2f, 0.3f, -0.5f,		1.0f, 1.0f, 0.0f,	//V3

		//-0.2f, -0.3f, -0.5f,	0.0f, 1.0f, 0.0f,	//V4
		//0.5f, -0.3f, -0.5f,		0.0f, 1.0f, 1.0f,	//V5
		//-0.5f, -0.7f, -0.5f,	1.0f, 1.0f, 1.0f,	//V7

		//-0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 0.0f,	//V0
		//-0.5f, -0.7f, -0.5f,	1.0f, 1.0f, 1.0f,	//V7
		//-0.2f, -0.3f, -0.5f,	0.0f, 1.0f, 0.0f,	//V4

		//0.5f, -0.3f, -0.5f,		0.0f, 1.0f, 1.0f,	//V5
		//0.5f, -0.7f, -0.5f,		0.0f, 0.0f, 1.0f,	//V6
		//-0.5f, -0.7f, -0.5f,	1.0f, 1.0f, 1.0f,	//V7

		//-0.2f, 0.3f, -0.5f,		1.0f, 1.0f, 0.0f,	//V3
		//-0.2f, -0.3f, -0.5f,	0.0f, 1.0f, 0.0f,	//V4
		//-0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 0.0f,	//V0

	};

	unsigned int indicesLuis[] =
	{
		/*0, 1, 2, 3, 4, 5, 6, 7*/
		//Indices que ayudan a dibujar los triangulos//
		5,7,6,
		1,2,3,
		1,3,0,
		4,3,0,
		0,4,7,
		4,5,7 
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);	//Only if we are going to work with index


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLuis), verticesLuis, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesLuis), indicesLuis, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

	//Prepare to draw the scene with Projections
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	myShader.use();
	// create transformations and Projection
	glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	/*projectionOp = glm::ortho(-5.0f, 5.0f, -3.0f, 3.0f, 0.1f, 10.0f);*/

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		/*******************************************/
		//Use "view" in order to affect all models
		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY, movZ));
		// pass them to the shaders
		myShader.setMat4("model", modelOp);
		myShader.setMat4("view", viewOp);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		myShader.setMat4("projection", projectionOp);
		

		//glBindVertexArray(VAO[1]);	//Enable data array [1]
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]); //Only if we are going to work with index

		//modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
		//myShader.setMat4("model", modelOp);
		////glDrawArrays(GL_LINE_LOOP, 0, 8); //My C
		//glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));	//to Draw using index
		////el 3 indica los elementos que se van a dibujar
		////glDrawArrays(GL_TRIANGLES, 0, 18); //My C


		/*-------------------Second figure-------------------*/
		glBindVertexArray(VAO[0]);	//Enable data array [0]

		//Línea1
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 1

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 2

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, 0.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 3

		//Línea2
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -1.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 4

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -1.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 5

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -1.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 6

		//Línea3
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -2.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 7

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -2.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 8

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -2.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 9


		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -2.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 10

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -2.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 11

		//Línea 4
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -3.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 12

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -3.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 13

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -3.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 14

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -3.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 15

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -3.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 16

		//Línea 5
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -4.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 17

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -4.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 18

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -4.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 19

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -4.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 20

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -4.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 21

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -4.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 22

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -4.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 23

		//Linea6

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 24

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 25

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 26

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 27

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 28

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 29

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 30

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 31

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 32

		//Linea 7

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 33

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 34

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 35

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 36

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 37

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 38

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 39

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 40

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 41


		//Línea 8
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 42

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 43

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 44

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 45

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 46

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 47

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 48

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 49

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 50


		//Línea 9
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 51

		
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 52

		//Parte de abajo ojos
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 53

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 54

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 55

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 56
		
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 57

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 58

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 59

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 60

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, -8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 61

		//Linea 10
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 62

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 63

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 64


		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 65

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 66

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 67

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 68

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 69

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 70

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 71

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, -9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 72

		//Linea 11

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 73


		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 74


		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 75

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 76

		//Boca Primera Parte
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 77

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 78

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 79

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 80

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 81

		//Cara parte de la boca

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 82

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 83

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 84

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(9.5f, -10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 85


		//Linea siguiente despues de la boca

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 86

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 87

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 88

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 89

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 90

		//Boca segunda parte
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 91

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 92

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(2.55f, 2.55f, 2.55f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 93

	    //Cara parte de boca segunda parte

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 94

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 95

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 96

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 97

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(9.5f, -11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 98


		//Parte de abajo//

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 99

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 100

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 101

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 102


		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 103

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 104

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 105

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 106

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 107

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 108

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, -12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.50f, 0.251f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 109

		



		///*modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -6.2f, 0.0f));*/
		//modelOp = glm::translate(modelOp, glm::vec3(0.0f, -6.2f, 0.0f)); //lo hago dependiente de mi cubo anterior
		//myShader.setMat4("model", modelOp);
		//glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube

		glBindVertexArray(0);
		/*****************************************************************/
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
		movZ += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS)
		movZ -= 0.01f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}