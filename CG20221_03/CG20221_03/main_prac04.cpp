/*---------------------------------------------------------*/
/* ----------------   Práctica 4 --------------------------*/
/*-----------------    2022-1   ---------------------------*/
/*------------- Alumno:Leonardo Alonso González Pacheco  ---------------*/
/*------------- No. de cuenta: 313221136              ---------------*/
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
GLuint VBO, VAO, EBO;

void myData(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -25.0f;

float rotY = 0.0f,
       rotX = 0.0f,
       rotZ = 0.0f;

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
		-0.5f, -0.5f, 0.5f,		//V0 - Frontal
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, 0.5f, 0.5f,		//V5
		-0.5f, -0.5f, 0.5f,		//V0
		-0.5f, 0.5f, 0.5f,		//V4
		0.5f, 0.5f, 0.5f,		//V5

		0.5f, -0.5f, -0.5f,		//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, -0.5f,		//V7

		-0.5f, 0.5f, 0.5f,		//V4 - Izq
		-0.5f, 0.5f, -0.5f,		//V7
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, -0.5f, 0.5f,		//V0

		0.5f, 0.5f, 0.5f,		//V5 - Der
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		0.5f, -0.5f, -0.5f,		//V2

		-0.5f, 0.5f, 0.5f,		//V4 - Sup
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, 0.5f, -0.5f,		//V6

		-0.5f, -0.5f, 0.5f,		//V0 - Inf
		-0.5f, -0.5f, -0.5f,	//V3
		0.5f, -0.5f, -0.5f,		//V2
		-0.5f, -0.5f, 0.5f,		//V0
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, -0.5f, 0.5f,		//V1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 4", NULL, NULL);
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

	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	myShader.use();

	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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

		//Mi bloque de dibujo
		/*******************************************/
		glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
		//Use "view" in order to affect all models

		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY, movZ));
		/*viewOp = glm::rotate(glm::mat4(1.0f), glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));*/
		viewOp = glm::rotate(viewOp, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f)); //rotación de 45° en el eje y
		viewOp = glm::rotate(viewOp, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		viewOp = glm::rotate(viewOp, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		/*viewOp = glm::translate(viewOp, glm::vec3(movX, movY, movZ));*/

		// pass them to the shaders
		myShader.setMat4("model", modelOp);
		myShader.setMat4("view", viewOp);
		myShader.setMat4("projection", projectionOp);

		//Model
		glBindVertexArray(VAO);

		glm::mat4 temp = glm::mat4(1.0f); //matriz temporal unitaria donde se guarda el estado antes de aplicar escala de cuello
		glm::mat4 temp2 = glm::mat4(1.0f);
		glm::mat4 temp3 = glm::mat4(1.0f);
		//modelOp = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 0.3f, 1.0f)); //Aplico escala y ayuda a cambiar dimensiones de objeto
		//myShader.setMat4("model", modelOp);
		//myShader.setVec3("aColor", glm::vec3(31.0f/255.0f,63.0f / 255.0f, 193.0f/255.0f));
		//glDrawArrays(GL_TRIANGLES, 0, 36);//Draw cube 1

		temp = modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.75f, 0.0f)); //Aplico escala y ayuda a cambiar dimensiones de objeto
		modelOp = glm::scale(modelOp, glm::vec3(0.5f, 0.5f, 1.0f));//escala en z valor de 1 porque sino se elimina
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(31.0f/255.0f,63.0f / 255.0f, 193.0f/255.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Cuello

		///*modelOp = glm::translate(modelOp, glm::vec3(3.0f, 4.0f, 0.0f));*/ //conservo lo que tiene la matriz modelOp
		//modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.25f, 0.0f)); //parto desde el origen
		//modelOp = glm::scale(modelOp, glm::vec3(1.5f, 2.5f, 1.0f));
		//myShader.setMat4("model", modelOp);
		//myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
		//glDrawArrays(GL_TRIANGLES, 0, 36);//Cabeza desde el origen de referencia que es el pecho

		modelOp = glm::translate(temp, glm::vec3(0.0f, 1.5f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 2.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Cabeza donde el origen  esta en cuello

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(4.0f, 5.0f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Pecho

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(4.0f, 1.0f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Cadera

		temp2=modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, -5.25f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.65f, 0.30f, 0.90f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Pierna1

		modelOp = glm::translate(temp2, glm::vec3(-0.50f, -2.125f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 0.75f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.96f, 0.68f, 0.039f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Zapato1

		temp3=modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, -5.25f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.65f, 0.30f, 0.90f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Pierna2

		modelOp = glm::translate(temp3, glm::vec3(0.50f, -2.125f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 0.75f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.96f, 0.68f, 0.039f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Zapato2

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.75f, 2.25f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 0.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.039f, 0.960f, 0.650f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Brazo1

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.25f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.039f, 0.611f, 0.960f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Brazo1

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.75f, 2.25f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 0.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.039f, 0.960f, 0.650f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Brazo2

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.25f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.039f, 0.611f, 0.960f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Brazo2

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, -1.65f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 0.3f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.294f, 0.227f, 0.086f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Mango Espada

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.6f, -1.65f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.3f, 0.6f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.984f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Mango Espada

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, -1.65f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(3.5f, 0.3f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.713f, 0.713f, 0.713f));
		glDrawArrays(GL_TRIANGLES, 0, 36);// Espada

		//PATO
		
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, -4.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(3.5f, 5.0f, 3.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.984f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // cuerpo

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, -3.0f, 2.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.0f, 1.5f, 2.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //boca

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(12.7f, -2.5f, 0.5f));
		modelOp = glm::scale(modelOp, glm::vec3(1.1f, 1.3f, 1.3f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // ojo izquierdo

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(15.3f, -2.5f, 0.5f));
		modelOp = glm::scale(modelOp, glm::vec3(1.1f, 1.3f, 1.3f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // ojo derecho

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, -6.5f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.4f, 1.0f, 0.4f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // pierna derecha

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, -6.5f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.4f, 1.0f, 0.4f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // pierna izquieda

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(15.5f, -5.0f, -0.5f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 2.0f, 2.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.984f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //ala derecha

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(12.5f, -5.0f, -0.5f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 2.0f, 2.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.984f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //ala izquierda

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, -5.25f, -1.75f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 2.5f, 2.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.984f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // cola parte 1

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, -4.25f, -2.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 1.5f, 1.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.984f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //cola parte 2

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, -7.1f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 0.2f, 2.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // zapato izquierdo

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, -7.1f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 0.2f, 2.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); // zapato derecho


		//temp3=modelOp = glm::translate(temp2, glm::vec3(-1.25f, -2.25f, 0.0f));
		//modelOp = glm::scale(modelOp, glm::vec3(1.5f, 3.5f, 1.0f));
		//myShader.setMat4("model", modelOp);
		//myShader.setVec3("aColor", glm::vec3(0.65f, 0.30f, 0.90f));
		//glDrawArrays(GL_TRIANGLES, 0, 36);//Pierna1

		//
		//modelOp = glm::translate(temp3, glm::vec3(-0.5f, -2.15f, 0.0f));
		//modelOp = glm::scale(modelOp, glm::vec3(2.5f, 0.75f, 1.0f));
		//myShader.setMat4("model", modelOp);
		//myShader.setVec3("aColor", glm::vec3(0.96f, 0.68f, 0.039f));
		//glDrawArrays(GL_TRIANGLES, 0, 36);//Zapato1

		///*modelOp = glm::translate(modelOp, glm::vec3(3.0f, 4.0f, 0.0f));*/ //conservo lo que tiene la matriz modelOp
		//modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 4.0f, 0.0f)); //parto desde el origen
		//myShader.setMat4("model", modelOp);
		//myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
		//glDrawArrays(GL_TRIANGLES, 0, 36);//Draw cube 2

		glBindVertexArray(0);
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
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.01f; //Movimento mas lento
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 1.01f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 1.01f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 1.01f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 1.01f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		rotZ -= 1.01f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		rotZ += 1.01f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}