//GABRIELA AGUILAR LUGO A01373890
//GRAFICAS COMPUTACIONALES
//PRIMER PARCIAL


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "InputFile.h"
#include <cmath> 
#include <cstdlib>
#include <GL/glut.h>



// Identificador del manager al que vamos a asociar todos los VBOs
GLuint vao;

// Identifcador del manager de los shaders (shaderProgram)
GLuint shaderProgram;

void Initialize()
{
	// Creando toda la memoria que el programa va a utilizar.

	// Creación del atributo de posiciones de los vértices.
	// Lista de vec2
	// Claramente en el CPU y RAM

	float i;

	std::vector<glm::vec2> positions;
	positions.push_back(glm::vec2(0, 0));
	std::vector<glm::vec3> colors;
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));

	for (i = 0; i <= 362; i++) {
		positions.push_back(glm::vec2(glm::cos(glm::radians(i)),
			glm::sin(glm::radians(i))));
		colors.push_back(glm::vec3(glm::cos(glm::radians(i)),
			glm::sin(glm::radians(i)), 0.0f));
	}

	//std::vector<glm::vec2> positions;
	//positions.push_back(glm::vec2(-1.0f, -1.0f));
	//positions.push_back(glm::vec2(1.0f, -1.0f));
	//positions.push_back(glm::vec2(0.0f, 1.0f));

	// Arreglo de colores en el cpu
	//std::vector<glm::vec3> colors;
	//colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	//colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	//colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	// Queremos generar 1 manager
	glGenVertexArrays(1, &vao);
	// Utilizar el vao. A partir de este momento, todos VBOs creados y configurados
	// se van a asociar a este manager.
	glBindVertexArray(vao);

	// Identificador del VBO de posiciones.
	GLuint positionsVBO;
	// Creación del VBO de posiciones
	glGenBuffers(1, &positionsVBO);
	// Activamos el buffer de posiciones para poder utilizarlo
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * positions.size(),
		positions.data(), GL_STATIC_DRAW);
	// Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(0);
	// Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Ya no vamos a utilizar este VBO en este momento.
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(),
		colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desactivamos el manager
	glBindVertexArray(0);

	// Creamos un objeto para leer archivos de texto
	InputFile ifile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde está
	// el código del vertex shader.
	//ifile.Read("Default.vert");
	ifile.Read("DiscardCenter.vert");
	// Obtenemos el código fuente y lo guardamos
	// en un string
	std::string vertexSource = ifile.GetContents();
	// Creamos un shader de tipo vertex
	// guardamos su identificador en una variable.
	GLuint vertexShaderHandle =
		glCreateShader(GL_VERTEX_SHADER);
	// Obtener los datos en el formato correcto
	const GLchar *vertexSource_c =
		(const GLchar*)vertexSource.c_str();
	// Le estamos dando el código fuente a OpenGL
	// para que se lo asigne al shader
	glShaderSource(vertexShaderHandle, 1,
		&vertexSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ningún error.
	glCompileShader(vertexShaderHandle);

	//ifile.Read("Default.frag");
	ifile.Read("DiscardCenter.frag");
	std::string fragmentSource = ifile.GetContents();
	GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);

	// Creamos el identificador para el manager de los shaders
	shaderProgram = glCreateProgram();
	// Adjuntamos el vertex shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, vertexShaderHandle);
	// Adjuntamos el fragment shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, fragmentShaderHandle);
	// Asociamos un buffer con indice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	// Asociamos un buffer con indice 1 (colores) a la variable VertexColor
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	// Ejecutamos el proceso de linker (asegurarnos que el vertex y fragment son
	// compatibles)
	glLinkProgram(shaderProgram);
}

void GameLoop()
{
	// Limpiamos el buffer de color y el buffer de profunidad.
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Activamos el vertex shader y el fragment shader utilizando el manager
	glUseProgram(shaderProgram);
	// Activamos el manager, en este momento se activan todos los
	// VBOs asociados automáticamente.
	glBindVertexArray(vao);
	// Función de dibujado sin indices.
	// se incrementa dos angulos mas porque con 361 queda un grado vacio, entocnes 361+1 
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);

	// Terminamos de utilizar el manager
	glBindVertexArray(0);
	// Desactivamos el manager
	glUseProgram(0);

	// Cuando terminamos de renderear, cambiamos los buffers.
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	// Inicializar freeglut
	// Freeglut se encarga de crear una ventana
	// en donde podemos dibujar
	glutInit(&argc, argv);
	// Solicitando una versión específica de OpenGL.
	//glutInitContextVersion(4, 4);
	// Iniciar el contexto de OpenGL. El contexto se refiere
	// a las capacidades que va a tener nuestra aplicación
	// gráfica.
	// En este caso estamos trabajando con el pipeline programable.
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// Freeglut nos permite configurar eventos que ocurren en la ventana.
	// Un evento que nos interesa es cuando alguien cierra la ventana.
	// En este caso, simplemente dejamos de renderear la esscena y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Configuramos el framebuffer. En este caso estamos solicitando un buffer
	// true color RGBA, un buffer de profundidad y un segundo buffer para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);
	// Creamos la ventana y le damos un título.
	glutCreateWindow("Hello World GL");
	// Asociamos una función de render. Esta función se mandará a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);

	// Inicializar GLEW. Esta librería se encarga de obtener el API de OpenGL de
	// nuestra tarjeta de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configurar OpenGL. Este es el color por default del buffer de color
	// en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Configuración inicial de nuestro programa.
	Initialize();

	// Iniciar la aplicación. El main se pausará en esta línea hasta que se cierre
	// la venta de OpenGL.
	glutMainLoop();

	return 0;
}
