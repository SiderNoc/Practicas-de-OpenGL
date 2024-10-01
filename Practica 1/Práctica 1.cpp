#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Función para establecer el color usando RGB
void setColorFromRGB(int r, int g, int b)
{
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

int main()
{
	// Inicia GLFW
	glfwInit();

	// Indicar la version de OpenGL (version 4.4)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	// Indicar el perfil CORE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Crea la venta, las dimensiones y añade el nombre a la ventana
	GLFWwindow* window = glfwCreateWindow(500, 500, "Practica 1: Abriendo una ventana", NULL, NULL);
	// Marca error si la ventana falló al crearse
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Carga el glad
	gladLoadGL();
	// Especifica el tamaño que usara opengl en la ventana creada
	// En este caso la ventana cubrira de x = 0, y = 0, a x = 500, y = 500
	glViewport(0, 0, 500, 500);

	// Establece el color de fondo usando valores RGB
	setColorFromRGB(118, 90, 242);

	// Quita el fondo predeterminado
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Loop de la ventana
	while (!glfwWindowShouldClose(window))
	{
		// eventos de GLFW
		glfwPollEvents();
	}

	// Elimina la ventana al cerrarla
	glfwDestroyWindow(window);
	// Cierra glfw
	glfwTerminate();
	return 0;
}