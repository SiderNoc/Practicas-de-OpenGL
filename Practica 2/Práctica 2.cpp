#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void setColorBack(int r, int g, int b)
{
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

void setTriangleColor(GLuint shaderProgram, float r, float g, float b)
{
	// Obtenemos la ubicación de la variable uniform 'ourColor' en el programa de shaders
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	// Asignamos los valores de color pasados como parámetros
	glUniform3f(vertexColorLocation, r / 255.0f, g / 255.0f, b / 255.0f);
}


// Vertex Shader
const char* vertexShaderSource = "#version 440 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment Shader
const char* fragmentShaderSource = "#version 440 core\n"
"out vec4 FragColor;\n"
"uniform vec3 ourColor;\n" // Se define una variable uniform para el color
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n" // Usamos la variable ourColor para definir el color
"}\n\0";


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Práctica 2: El primer triangulo", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Error" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 1000, 1000);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	glCompileShader(vertexShader);


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(fragmentShader);

	// Creamos el objeto del programa de shaders y obtenemos su referencia
	GLuint shaderProgram = glCreateProgram();
	// Adjuntamos los shaders de vértice y fragmento al programa de shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Vinculamos/Enlazamos todos los shaders al programa de shaders
	glLinkProgram(shaderProgram);

	// Eliminamos los objetos de shaders de vértices y fragmentos que ya no son necesarios
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Coordenadas de los vértices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Esquina inferior izquierda
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Esquina inferior derecha
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Esquina superior
	};

	// Creamos contenedores de referencia para el Objeto de Matriz de Vértices (VAO) y el Objeto de Búfer de Vértices (VBO)
	GLuint VAO, VBO;

	// Generamos el VAO y VBO con solo 1 objeto cada uno
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Hacemos que el VAO sea el objeto de matriz de vértices actual vinculándolo
	glBindVertexArray(VAO);

	// Vinculamos el VBO especificando que es un GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introducimos los vértices en el VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configuramos el atributo de vértice para que OpenGL sepa cómo leer el VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Habilitamos el atributo de vértice para que OpenGL sepa usarlo
	glEnableVertexAttribArray(0);

	// Vinculamos el VBO y el VAO a 0 para no modificarlos accidentalmente
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Bucle principal
	while (!glfwWindowShouldClose(window))
	{
		// Especificamos el color de fondo
		setColorBack(118, 90, 242);
		// Limpiamos el búfer de fondo y le asignamos el nuevo color
		glClear(GL_COLOR_BUFFER_BIT);
		// Indicamos a OpenGL qué programa de shaders queremos usar
		glUseProgram(shaderProgram);

		setTriangleColor(shaderProgram, 200, 50, 200); // Color del triángulo
		// Vinculamos el VAO para que OpenGL sepa usarlo
		glBindVertexArray(VAO);
		// Dibujamos el triángulo usando la primitiva GL_TRIANGLES
		glDrawArrays(GL_TRIANGLES, 0, 12);
		// Intercambiamos el búfer de fondo con el de frente
		glfwSwapBuffers(window);
		// Procesamos todos los eventos de GLFW
		glfwPollEvents();
	}


	// Eliminamos todos los objetos que hemos creado
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// Eliminamos la ventana antes de finalizar el programa
	glfwDestroyWindow(window);
	// Terminamos GLFW antes de finalizar el programa
	glfwTerminate();
	return 0;
}
