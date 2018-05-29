/**
 * @file 
 * @brief This file contains implementation of simple quad example.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 * @author Dominik Harmim <harmim6@gmail.com>
 */


#include <examples/quadExample.h>
#include <student/mouseCamera.h>
#include <student/program.h>
#include <opengl/opengl.h>


//! [GLOBALS]
/**
 * @brief This structure contains all global variables for triangle example.
 */
struct QuadExampleVariables
{
	///This variable contains shader program.
	GLuint program; //a program id
	///This variable contains location of projection matrix
	/// uniform variable in shader program.
	GLint projectionMatrixUniform; //a uniform location
	///This variable contains location of view matrix
	/// uniform variable in shader program.
	GLint viewMatrixUniform; //a uniform location
	///This variable contains vertex puller.
	GLuint vao; //a vertex array id
	///This variable contains buffer with vertex positions.
	GLuint vbo; //vertex buffer object id
	///This variable contains buffer with indices.
	GLuint ebo; //vertex indices
} quadExample; ///< instance of all global variables for triangle example.
//! [GLOBALS]


//! [VERTEXSHADER]
const char *quadExampleVertexShaderSource =
	//! [VERSION]
	//a version of GLSL
	" #version 330"
	//! [VERSION]

	//! [UNIFORMS]
	//a uniform variable
	"\n uniform mat4 projectionMatrix;"
	//a uniform variable
	"\n uniform mat4 viewMatrix;"
	//! [UNIFORMS]

	//! [INATTRIB]
	//an input vertex attribute (it is read from buffer)
	"\n layout(location=0)in vec3 position;"
	//! [INATTRIB]

	//! [OUTATTRIB]
	//an output vertex attribute (it is interpolated in rasterization)
	"\n out vec3 vColor;"
	//! [OUTATTRIB]


	//! [MAIN]
	//a main function
	"\n void main()"
	"\n {"
	//! [MAIN]

	//! [MATMUL]
	//a projection of a position from world-space into clip-space
	"\n    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.f);"
	///! [MATMUL]

	//! [COMPUTECOLOR]
	//a computation of color
	"\n     if (gl_VertexID == 0) vColor = vec3(1.f, 0.f, 0.f);"
	"\n     else if (gl_VertexID == 1) vColor = vec3(0.f, 1.f, 0.f);"
	"\n     else if (gl_VertexID == 2) vColor = vec3(0.f, 0.f, 1.f);"
	"\n     else if (gl_VertexID == 3) vColor = vec3(0.f, 1.f, 1.f);"
	//! [COMPUTECOLOR]

	"\n }";
//! [VERTEXSHADER]

//! [FRAGMENTSHADER]
const char *quadExampleFragmentShaderSource =
	//a version of GLSL
	" #version 330"

	//an input fragment attribute (it was interpolated using vertex attributes)
	//! [INATTRIBFS]
	"\n in vec3 vColor;"
	//! [INATTRIBFS]

	//an output fragment attribute (it is sent to framebuffer)
	//! [OUTATTRIBFS]
	"\n layout(location=0)out vec4 fColor;"
	//! [OUTATTRIBFS]

	"\n void main()"
	"\n {"

	//! [COLOROUTPUT]
	"\n     fColor = vec4(vColor, 1.f);"
	//! [COLOROUTPUT]

	"\n }";
//! [FRAGMENTSHADER]


void quadExample_onInit(int32_t width, int32_t height)
{
	//! [INITIALIZATION]
	cpu_initMatrices(width, height);
	//! [INITIALIZATION]

	//! [CREATESHADER]
	const GLuint vertexId = compileShader(
		GL_VERTEX_SHADER, //a type of shader
		quadExampleVertexShaderSource //a glsl source
	);
	const GLuint fragmentId = compileShader(
		GL_FRAGMENT_SHADER, //a type of shader
		quadExampleFragmentShaderSource //a glsl source
	);
	quadExample.program = linkProgram(vertexId, fragmentId);
	//! [CREATESHADER]

	//! [UNIFORMLOCATION]
	quadExample.projectionMatrixUniform = glGetUniformLocation(
		quadExample.program, //a program id
		"projectionMatrix" //a uniform variable name
	);
	quadExample.viewMatrixUniform = glGetUniformLocation(
		quadExample.program, //a program id
		"viewMatrix" //a uniform variable name
	);
	//! [UNIFORMLOCATION]

	//! [VERTEXDATA]
	const float positions[12] = { //vertex positions
		-1.f, -1.f, +0.f, //a quad vertex A
		+1.f, -1.f, +0.f, //a quad vertex B
		-1.f, +1.f, +0.f, //a quad vertex C
		+1.f, +1.f, +0.f, //a quad vertex D
	};
	//! [VERTEXDATA]

	//! [GENBUFFERS]
	glGenBuffers(
		1, //a number of buffer ids that will be reserved
		&quadExample.vbo //a pointer to buffer id variable
	);
	//! [GENBUFFERS]

	//! [BINDBUFFER]
	glBindBuffer(
		GL_ARRAY_BUFFER, //a binding point
		quadExample.vbo //a buffer id
	);
	//! [BINDBUFFER]

	//! [BUFFERDATA]
	glBufferData(
		GL_ARRAY_BUFFER, //a binding point
		sizeof(float) * 12, //a size of buffer
		positions, //a pointer to data
		GL_STATIC_DRAW //a hint
	);
	//! [BUFFERDATA]

	//! [EBO]
	const uint32_t indices[6] = {
		0, 1, 2,
		2, 1, 3,
	};
	glGenBuffers(1, &quadExample.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadExample.ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices, GL_STATIC_DRAW
	);
	//! [EBO]

	//! [ATTRIBLOCATION]
	const GLint positionAttribute = glGetAttribLocation(
		quadExample.program, //a program id
		"position" //a name of vertex attribute
	);
	//! [ATTRIBLOCATION]

	//! [GENARRAYS]
	glGenVertexArrays(
		1, //a number of vertex arrays
		&quadExample.vao //a pointer to first
	);
	//! [GENARRAYS]

	//! [BINDARRAYS]
	glBindVertexArray(quadExample.vao);
	//! [BINDARRAYS]

	//! [BINDEBO]
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadExample.ebo);
	//! [BINDEBO]

	//! [BINDVBO]
	glBindBuffer(
		GL_ARRAY_BUFFER,
		quadExample.vbo
	);
	//! [BINDVBO]

	//! [ATTRIBPOINTER]
	glVertexAttribPointer(
		(GLuint) positionAttribute, //an attribute index
		3, //a number of components
		GL_FLOAT, //a type of attribute
		GL_FALSE, //a normalization
		sizeof(float) * 3, //a stride in bytes
		(const GLvoid*) 0 //an offset in bytes
	);
	//! [ATTRIBPOINTER]

	//! [ENABLEATTRIB]
	glEnableVertexAttribArray((GLuint) positionAttribute);
	//! [ENABLEATTRIB]

	//! [UNBINDARRAYS]
	glBindVertexArray(0);
	//! [UNBINDARRAYS]

	glClearColor(.1f, .1f, .1f, 1.f);
}


void quadExample_onExit()
{
	//! [FREE]
	glDeleteProgram(quadExample.program);
	glDeleteBuffers(1, &quadExample.vbo);
	glDeleteBuffers(1, &quadExample.ebo);
	glDeleteVertexArrays(1, &quadExample.vao);
	//! [FREE]
}


void quadExample_onDraw()
{
	//! [CLEAR]
	glClear(
		GL_COLOR_BUFFER_BIT //clear color buffer
		| GL_DEPTH_BUFFER_BIT //clear depth buffer
	);
	//! [CLEAR]

	//! [USEPROGRAM]
	glUseProgram(quadExample.program);
	//! [USEPROGRAM]

	//! [BINDVAO]
	glBindVertexArray(quadExample.vao);
	//! [BINDVAO]

	//! [UPLOADMATRICES]
	glUniformMatrix4fv(
		quadExample.projectionMatrixUniform, //location of uniform variable
		1, //number of matrices
		GL_FALSE, //transpose
		(float *) &projectionMatrix //pointer to data
	);
	glUniformMatrix4fv(
		quadExample.viewMatrixUniform, //location of uniform variable
		1, //number of matrices
		GL_FALSE, //transpose
		(float *) &viewMatrix //pointer to data
	);
	//! [UPLOADMATRICES]

	//! [DRAW]
	glDrawElements(
		GL_TRIANGLES, //primitive type
		6, //number of indices
		GL_UNSIGNED_INT, //type of indices
		(const GLvoid *) 0 //offset
	);
	//! [DRAW]

	//! [UNBINDVAO]
	glBindVertexArray(0);
	//! [UNBINDVAO]
}


/**
 * \example quadExample quadExample.c
 *
 *
 * \image html images/quad.png "The figure shows the output of the quad example." width=10cm
 * Tento příklad vykreslí jeden barevný čtverec s použitím indexování.
 *
 *
 * \section Globals Globální proměnné
 * Globální proměnné jsou uloženy ve struktuře:
 * \snippet quadExample.c GLOBALS
 * Projekční a view matice jsou uloženy v externích proměnných:
 * Pokud se hýbe s myší, jsou tyto matice přepočítávány.<br/>
 * Zdrojáky vertex a fragment shaderu jsou uloženy v proměnných:
 * \snippet quadExample.c VERTEXSHADER
 * \snippet quadExample.c FRAGMENTSHADER
 *
 *
 * \section Initialization Inicializace
 * Když je příklad spuštěn, je zavolána funkce quadExample_onInit().
 * Tato funkce vytvoří opengl objekty (buffer, vertex arrays, shader programy).
 * První funkční volání inicializuje matice:
 * \snippet quadExample.c INITIALIZATION
 *
 * \subsection ShaderProgram Inicializace shader programu
 * Dále následuje kopilace shaderů a linkování shader programu:
 * \snippet quadExample.c CREATESHADER
 * Shader program je program, který běží na GPU a je psán v jazyce GLSL.<br/>
 * Následuje získaní lokací (id) uniformních proměnných v shader programu
 * pro matice:
 * \snippet quadExample.c UNIFORMLOCATION
 * Lokace uniformní proměnné je celé číslo, které je dostupné na straně
 * CPU a slouží jako handle pro náhrání dat do dané proměnné.
 * Lokaci uniformní proměnné lze získat pomocí jejího jména.
 *
 * \subsection Buffers Inicializace bufferů (lineární pole na GPU)
 * Následuje inicializace bufferu pro vrcholy.
 * Vrcholy jsou uloženy ve statickém poli:
 * \snippet quadExample.c VERTEXDATA
 * Nejprve je nutné zarezervovat jmeno(id) bufferu:
 * \snippet quadExample.c GENBUFFERS
 * Poté je nutné id bufferu navázat na vhodný binding point opengl:
 * \snippet quadExample.c BINDBUFFER
 * GL_ARRAY_BUFFER binding point slouží pro vertex attributy.
 * Následuje nahrání dat na GPU:
 * \snippet quadExample.c BUFFERDATA
 * Následuje vytvoření bufferu pro indexy.
 * Postup je obdobný jako pro vertex atributy, jen binding point je jiný:
 * \snippet quadExample.c EBO
 * Tím je inicializace bufferů hotová.
 *
 * \subsection VAO Inicializace vertex arrays object (nastavení vertex pulleru)
 * Následuje vytvoření a nastavení objektu Vertex Arrays.
 * Tento objekt obsahuje nastavení vertex puller - ten sestavuje vertexy,
 * které přícházení do vertex shaderu.
 * Vertex je složen z několik vertex attributů,
 * (v tomto příkladě pouze z jednoho)
 * Nejprve je nutné získát lokaci vstupní proměnné ve vertex shaderu,
 * pro kterou sa nastavuje čtecí hlava:
 * \snippet quadExample.c ATTRIBLOCATION
 * První krok spočívá v rezervování jména (id) vertex arrays objektu (vao):
 * \snippet quadExample.c GENARRAYS
 * Nastavení vao se provádí mezi příkazy pro aktivaci a dekativaci,
 * další krok je proto aktivace:
 * \snippet quadExample.c BINDVAO
 * Pro nastavení indexování je nutné navázat element buffer:
 * \snippet quadExample.c BINDEBO
 * Pro nastavení vertex attributů je pořeba specifikovat,
 * ze kterého bufferu bude daný atribut čten:
 * \snippet quadExample.c BINDVBO
 * Dále je nutné specifikovat, kde se vertex attribut
 * v bufferu nachází (konfigurace čtecí hlavy):
 * \snippet quadExample.c ATTRIBPOINTER
 * Vertex attribut (pozice) je složen ze 3 komponent, typu float,
 * je uložen těsně za sebou a začíná na začátku bufferu (nulový offset).<br/>
 * Poté je nutné vertex attribut povolit:
 * \snippet quadExample.c ENABLEATTRIB
 * Nakonec je nutné deaktivovat vao:
 * \snippet quadExample.c UNBINDARRAYS
 * Tím je inicializace hotová.
 *
 *
 * \section Deinit Deinicializace
 * Deinicializace/uvolnění zdrojů probíhá ve funkci quadExample_onExit().
 * V této funkci je nutné uvolnit program, buffery a vertex arrays object:
 * \snippet quadExample.c FREE
 *
 *
 * \section Shaders Shadery
 * Shadery jsou uloženy ve statických řetězcích.
 * Shadery jsou psány v jazyce GLSL.<br/>
 * Každý shader musí mít na prvním řádku uvedenou verzi.
 * \snippet quadExample.c VERSION
 *
 * \subsection VertexShader Vertex Shader
 * Vertex shader v tomto příkladě promítá vrcholy pomocí matic do clip-space
 * a počítá barvu vrcholu z jeho pořadového čísla.
 * Vertex shader začíná deklarací interface.<br/>
 * Interface je složen z uniformních proměnných:
 * \snippet quadExample.c UNIFORMS
 * Interface dále obsahuje vertex atribut pro pozici vrcholu:
 * \snippet quadExample.c INATTRIB
 * Poslední položka interface je výstupní vertex atribut pro barvu vrcholu:
 * \snippet quadExample.c OUTATTRIB
 * Pokud před deklarací proměnné leží klíčoví slovo in, out nebo uniform
 * je proměnná součástí interface.
 * Z proměnných "in" a "uniform" lze pouze číst.
 * Do proměnných "out" lze pouze zapisovat.
 * Proměnné "in" a "out" mohou obsahovat pro každý vrchol jinou hodnotu.
 * Proměnné "uniform" slouží pro uložení konstant, které zůstávají stejné
 * po dobu jednoho vykreslujícího příkazu.
 * "layout(location=n)" explicitně specifikuje lokaci dané proměnné."<br/>
 * Tělo shaderu tvoří funkce main:
 * \snippet quadExample.c MAIN
 * Ve funkci main se nejprve spočítá pozice v clip-space:
 * \snippet quadExample.c MATMUL
 * Jazyk GLSL umožňuje násobení vektorů a matic a rozšíření
 * trojsložkového vektoru na čtyřsložkový.<br/>
 * Následně se spočíta brava z čísla vrcholu:
 * \snippet quadExample.c COMPUTECOLOR
 *
 * \subsection FragmentShader Fragment Shader
 * Stejně jako vertex shader, fragment shader také začíná deklarací
 * interface.<br/>
 * Interface je složen ze vstupního fragment atributu barvy:
 * \snippet quadExample.c INATTRIBFS
 * Název proměnné musí odpovídat názvu příslušné proměnné ve vertex shaderu,
 * liší se pouze v kvalifikátoru "in/out".
 * Proměnná bude obsahovat interpolovanou barvu.<br/>
 * Následuje specifikace výstupního fragment atributu:
 * \snippet quadExample.c OUTATTRIBFS
 * Výstupní atribut na pozici 0 je automaticky zapsán přes per-fragment
 * operace do framebufferu.<br/>
 * Ve funkci main je barva pouze přeposlána ze vstupní proměnné do
 * výstupní proměnné:
 * \snippet quadExample.c COLOROUTPUT
 *
 *
 * \section Draw Kreslení
 * Kreslení je zajištěno funkci quadExample_onDraw().
 * Funkce nejprve vyčistí framebuffer:
 * \snippet quadExample.c CLEAR
 * Následně aktivuje shader program:
 * \snippet quadExample.c USEPROGRAM
 * Aktivuje vertex arrays object (vao):
 * \snippet quadExample.c BINDVAO
 * Nahraje aktuální matice na GPU:
 * \snippet quadExample.c UPLOADMATRICES
 * Spustí kreslení:
 * \snippet quadExample.c DRAW
 * A nakonec deaktivuje vao:
 * \snippet quadExample.c UNBINDVAO
 */
