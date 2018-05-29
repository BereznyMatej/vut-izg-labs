/**
 * @file 
 * @brief This file contains implementation of exercise.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 * @author Dominik Harmim <harmim6@gmail.com>
 */


#include <student/student.h>
#include <student/bunny.h>
#include <student/mouseCamera.h>
#include <opengl/opengl.h>
#include <student/program.h>
#include <student/linearAlgebra.h>


/**
 * @brief This structure contains all global variables for this method.
 */
struct PhongVariables
{
	///This variable contains light poistion in world-space.
	Vec3 lightPosition;
	///This variable contains a program id.
	GLuint program; //a program id
	///This variable contains a location of projection matrix uniform.
	GLint projectionMatrixUniform; //a uniform location
	///This variable contains a location of view matrix uniform.
	GLint viewMatrixUniform; //a uniform location
	///This variable contains a location of camera position uniform.
	GLint cameraPositionUniform;
	///This variable contains a location of light position uniform.
	GLint lightPositionUniform;
	///This variable contains a vertex arrays object id.
	GLuint vao; //a vertex array id
	///This variable contains a buffer id for vertex attributes.
	GLuint vbo; //vertex buffer object id
	///This variable contains a buffer id for vertex indices.
	GLuint ebo; //vertex indices
} phong; ///<instance of all global variables for triangle example.



/**
 * @addtogroup vs Vertex Shader
 * @{
 */

/**
 * @addtogroup task2 Druhý úkol
 * @{
 *
 * @todo 2.1.) Doimplementujte vertex shader.
 * Vašim úkolem je přidat uniformní proměnné pro view a projekční matici.
 * Dále pronásobte pozici vrcholu těmito maticemi a zapište výsledek
 * do gl_Position.
 * Nezapomeňte, že píšete v jazyce GLSL, který umožňuje práci s maticovými
 * a vektorovými typy. Upravujte phongVertexShaderSource proměnnou.
 *
 * @}

 * @addtogroup task3 Třetí úkol
 * @{
 *
 * @todo 3.1.) Upravte vertex shader.
 * Vašim úkolem je přidat druhý vertex atribut - normálu vrcholu.
 * Dále přidejte dvě výstupní proměnné typu vec3 a zapište do nich pozici
 * a normálu vrcholu ve world-space.
 * Tyto proměnné budete potřebovat pro výpočet osvětlení.
 * Upravujte phongVertexShaderSource proměnnou.
 *
 * @}
 */

/// This variable contains vertex shader source for phong shading/lighting.
const char *phongVertexShaderSource =
	" #version 330"
	"\n "
	"\n layout(location=0)in vec3 position; // vertex position"
	"\n layout(location=1)in vec3 normal; // vertex normal"
	"\n "
	"\n out vec3 vPosition; // <- vertex position"
	"\n out vec3 vNormal; // <- vertex normal"
	"\n "
	"\n uniform mat4 projectionMatrix; // Projection matrix"
	"\n uniform mat4 viewMatrix; // View Matrix"
	"\n "
	"\n void main()"
	"\n {"
	"\n     // transform vertices to clip-space"
	"\n     // World space -(View matrix)-> View space"
	"\n     // View space -(Projection matrix)-> Clip space"
	"\n     gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.f);"
	"\n "
	"\n     // set output attributes"
	"\n     vPosition = position;"
	"\n     vNormal = normal;"
	"\n }";

/**
 * @}
 */


/**
 * @addtogroup fs Fragment Shader
 * @{
 */

/**
 * @addtogroup task3 Třetí úkol
 * @{
 *
 * @todo 3.2.) Upravte fragment shader (proměnná phongFragmentShaderSource).
 * Vašim úkolem je implementovat phongův osvětlovací model.
 * Přidejte dvě vstupní proměnné (typ vec3) stejného názvu,
 * jako nově přidané výstupní proměnné ve vertex shaderu.
 * V jedné obdržíte pozice fragmentu ve world-space.
 * V druhé obdržíte normálu fragmentu ve world-space.
 * Dále přidejte dvě uniformní proměnné (typ vec3) pro pozici kamery
 * a pro pozici světla.
 * Difuzní barvu materiálu nastave v základu na vec3(0.f,1.f,0.f) - zelená.<br/>
 * V případě, že normála povrchu směřuje vzhůru bude difuzní
 * barva vec3(1.f,1.f,1.f) - bílá.<br/>
 * Zelenou a bílou difuzní barvu míchejte pomocí y komponenty normály
 * umocněné na druhou.<br/>
 * Samozřejmě berte v potaz záporné hodnoty a nepřidávejte sníh (bílou barvu)
 * ze spodu.<br/>
 * Spekulání barvu materiálu nastavte na vec3(1.f,1.f,1.f) - bílá.<br/>
 * Shininess faktor nastavte na 40.f.<br/>
 * Předpokládejte, že světlo má bílou barvu.<br/>
 * Barva se vypočíta podle vzorce dF*dM*dL + sF*sM*sL.<br/>
 * dM,sM jsou difuzní/spekulární barvy materiálu - vektory.<br/>
 * dL,sL jsou difuzní/spekulární barvy světla - vektory.<br/>
 * dF,sF jsou difuzní/spekulární faktory - skaláry.<br/>
 * dF lze vypočíst pomocí vztahu clamp(dot(N,L),0.f,1.f) -
 * skalární součin a ořez do rozsahu [0,1].<br/>
 * N je normála fragmentu (nezapomeňte ji normalizovat).<br/>
 * L je normalizovaný vektor z pozice fragmentu směrem ke světlu.<br/>
 * sF lze vypočíst pomocí vztahu pow((clamp(dot(R,L),0.f,1.f)),s) -
 * skalární součin, ořez do rozsahu [0,1] a umocnění.<br/>
 * s je shininess faktor.<br/>
 * R je odražený pohledový vektor V; R = reflect(V,N).<br/>
 * V je normalizovaný pohledový vektor z pozice kamery do pozice fragmentu.<br/>
 * <br/>
 * Nezapomeňte, že programujete v jazyce GLSL, který zvládá
 * vektorové operace.<br/>
 * <b>Seznam užitečných funkcí:</b>
 *  - dot(x,y) - funkce vrací skalární součit dvou vektorů x,y stejné délky
 *  - clamp(x,a,b) - funkce vrací ořezanou hodnotu x do intervalu [a,b]
 *  - normalize(x) - funkce vrací normalizovaný vektor x
 *  - reflect(I,N) - funkce vrací odražený vektor I podle normály N
 *  - pow(x,y) - funkce vrací umocnění x na y - x^y
 *
 * @}
 */

/// This variable contains fragment shader source for phong shading/linghting.
const char *phongFragmentShaderSource =
	" #version 330"
	"\n "
	"\n in vec3 vPosition; // vertex position"
	"\n in vec3 vNormal; // vertex normal"
	"\n "
	"\n layout(location=0)out vec4 fColor; // output fragment color"
	"\n "
	"\n uniform vec3 cameraPosition; // position of camera"
	"\n uniform vec3 lightPosition; // position of light"
	"\n "
	"\n uniform vec3 lightColor = vec3(1.f, 1.f, 1.f); // lightColor = white"
	"\n // specualrColor = white"
	"\n uniform vec3 specularColor = vec3(1.f, 1.f, 1.f);"
	"\n uniform float shininessFactor = 40.f; // shininess factor"
	"\n uniform float eps = .001f;"
	"\n "
	"\n void main()"
	"\n {"
	"\n     vec3 light = normalize(lightPosition - vPosition);"
	"\n     vec3 camera = normalize(cameraPosition - vPosition);"
	"\n "
	"\n     // diffuseColor calculation"
	"\n     vec3 diffuseColor;"
	"\n     float nY = vNormal.y;"
	"\n     if (abs(nY - 1.f) <= eps)"
	"\n         // nY == 1 => normal goes vertical up"
	"\n         diffuseColor = vec3(1.f, 1.f, 1.f); // diffuseColor = white"
	"\n     else if (nY < 0 || abs(nY) <= eps)"
	"\n         // nY < 0 OR nY == 0 => normal goes down or it is horizontal"
	"\n         diffuseColor = vec3(0.f, 1.f, 0.f); // diffuseColor = green"
	"\n     else"
	"\n     { // nY < 1 AND nY > 0"
	"\n         // diffuseColor = linear interpolation of white and green"
	"\n         float t = abs(nY * nY);"
	"\n         diffuseColor = vec3(t, 1.f, t);"
	"\n     }"
	"\n     vec3 diffuse = clamp("
	"\n          lightColor * diffuseColor * max(dot(vNormal, light), 0.f),"
	"\n          0.f, 1.f"
	"\n     );"
	"\n     "
	"\n     vec3 R = normalize(-1.f * reflect(light, vNormal));"
	"\n     vec3 specular = clamp("
	"\n         lightColor * specularColor"
	"\n             * pow(max(dot(R, camera), 0.f), shininessFactor),"
	"\n         0.f, 1.f"
	"\n     );"
	"\n     "
	"\n     // write output color"
	"\n     fColor = vec4(diffuse + specular, 1.f);"
	"\n }";

/**
 * @}
 */


/**
 * @addtogroup init Inicializace
 * @{
 */

void phong_onInit(int32_t width, int32_t height)
{
	//init matrices
	cpu_initMatrices(width, height);

	//init lightPosition
	init_Vec3(&phong.lightPosition, 100.f, 100.f, 100.f);

	const GLuint vertexId = compileShader(
		GL_VERTEX_SHADER, //a type of shader
		phongVertexShaderSource //a shader source
	);
	const GLuint fragmentId = compileShader(
		GL_FRAGMENT_SHADER, //a type of shader
		phongFragmentShaderSource //a shader source
	);
	phong.program = linkProgram(vertexId, fragmentId);


	/**
	 * @addtogroup task1 První úkol
	 * @{
	 *
	 * @todo 1.1.) Doprogramujte inicializační funkci phong_onInit().
	 * Zde byste měli vytvořit buffery na GPU, nahrát data do bufferů,
	 * vytvořit vertex arrays object a správně jej nakonfigurovat.
	 * Do bufferů nahrajte vrcholy králička (pozice, normály) a indexy na
	 * vrcholy ze souboru bunny.h.
	 * V konfiguraci vertex arrays objektu zatím nastavte pouze jeden
	 * vertex atribut - pro pozici.
	 * Využijte proměnné ve struktuře PhongVariables (vbo, ebo, vao).
	 * Do proměnné phong.vbo zapište id bufferu obsahující vertex atributy.
	 * Do proměnné phong.ebo zapište id bufferu obsahující indexy na vrcholy.
	 * Do proměnné phong.vao zapište id vertex arrays objektu.
	 * Data vertexů naleznete v proměnné bunny.h/bunnyVertices -
	 * ty překopírujte do bufferu phong.vbo.
	 * Data indexů naleznete v proměnné bunny.h/bunnyIndices -
	 * ty překopírujte do bufferu phong.ebo.
	 * Dejte si pozor, abyste správně nastavili stride a offset ve
	 * funkci glVertexAttribPointer.
	 * Vrchol králička je složen ze dvou vertex atributů: pozice a normála.<br/>
	 * Buffer indexů nabindujte při nahrávání nastavení do VAO na
	 * GL_ELEMENT_ARRAY_BUFFER binding point.<br/>
	 * <b>Seznam funkcí, které jistě využijete:</b>
	 *  - glGenBuffers
	 *  - glBindBuffer
	 *  - glBufferData
	 *  - glGenVertexArrays
	 *  - glGetAttribLocation
	 *  - glBindVertexArray
	 *  - glVertexAttribPointer
	 *  - glEnableVertexAttribArray
	 *
	 *  @}
	 */

	// create buffer for vertex attributes
	glGenBuffers(1, &phong.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, phong.vbo);
	glBufferData(
		GL_ARRAY_BUFFER, sizeof(bunnyVertices), bunnyVertices, GL_STATIC_DRAW
	);

	// create buffer for vertex indices
	glGenBuffers(1, &phong.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, phong.ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(bunnyIndices), bunnyIndices,
		GL_STATIC_DRAW
	);

	// create vertex puller
	glGenVertexArrays(1, &phong.vao);

	// bind vertex puller
	glBindVertexArray(phong.vao);

	// bind buffer for indexing
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, phong.ebo);

	// bind buffer for attributes alocation
	glBindBuffer(GL_ARRAY_BUFFER, phong.vbo);

	// get position attribute id from program
	const GLint possitionAttribute = glGetAttribLocation(
		phong.program, "position"
	);

	// set vertex puller head for position
	glVertexAttribPointer(
		(GLuint) possitionAttribute, 3, GL_FLOAT, GL_FALSE,
		sizeof(GLfloat) * 6, (const GLvoid *) 0
	);

	// enable vertex puller head for position
	glEnableVertexAttribArray((GLuint) possitionAttribute);


	/**
	 * @addtogroup task2 Druhý úkol
	 * @{
	 *
	 * @todo 2.2.) Ve funkci phong_onInit() získejte lokace přidaných
	 * uniformních proměnných pro projekční a view matice.
	 * Zapište lokace do příslušných položek ve struktuře PhongVariables.
	 * Nezapomeňte, že lokace získáte pomocí jména proměnné v jazyce GLSL,
	 * které jste udělali v předcházejícím kroku.
	 *
	 * @}
	 */

	// get projection matrix and view matrix unfiroms location
	phong.projectionMatrixUniform = glGetUniformLocation(
		phong.program, "projectionMatrix"
	);
	phong.viewMatrixUniform = glGetUniformLocation(
		phong.program, "viewMatrix"
	);


	/**
	 * @addtogroup task3 Třetí úkol
	 * @{
	 *
	 * @todo 3.3.) Ve funkci phong_onInit() získejte lokace přidaných
	 * uniformních proměnných pro pozici světla a pro pozice kamery.
	 * Zapište lokace do příslušných položek ve struktuře PhongVariables.
	 * Nezapomeňte, že lokace získáte pomocí jména proměnné v jazyce GLSL,
	 * které jste udělali v předcházejícím kroku.<br/>
	 * <b>Seznam funkcí, které jistě využijete:</b>
	 *  - glGetUniformLocation
	 *
	 * @}
	 */

	// get camera position and light position uniform location
	phong.cameraPositionUniform = glGetUniformLocation(
		phong.program, "cameraPosition"
	);
	phong.lightPositionUniform = glGetUniformLocation(
		phong.program, "lightPosition"
	);


	/**
	 * @addtogroup task3 Třetí úkol
	 * @{
	 *
	 * @todo 3.4.) Ve funkci phong_onInit() nastavte druhý vertex atribut
	 * pro normálu.
	 * Musíte získat lokaci vstupní proměnné ve vertex shaderu, kterou
	 * jste přidali v předcházejícím kroku.
	 * Musíte správně nastavit stride a offset - normála nemá nulový
	 * offset.<br/>
	 * <b>Seznam funkcí, které jistě využijete:</b>
	 *  - glGetAttribLocation
	 *  - glVertexAttribPointer
	 *  - glEnableVertexAttribArray
	 *
	 * @}
	 */

	// get normal attribute id from program
	const GLint normalAttribute = glGetAttribLocation(phong.program, "normal");

	// set vertex puller head for normal
	glVertexAttribPointer(
		(GLuint) normalAttribute, 3, GL_FLOAT, GL_TRUE,
		sizeof(GLfloat) * 6, (const void *) (sizeof(GLfloat) * 3)
	);

	// enable vertex puller head for normal
	glEnableVertexAttribArray((GLuint) normalAttribute);


	// unbind vertex puller
	glBindVertexArray(0);

	glClearColor(.1f, .1f, .1f, 1.f);
	glEnable(GL_DEPTH_TEST);

}

/**
 * @}
 */


void phong_onExit()
{
	glDeleteBuffers(1, &phong.vbo);
	glDeleteBuffers(1, &phong.ebo);
	glDeleteVertexArrays(1, &phong.vao);
	glDeleteProgram(phong.program);
}


/**
 * @addtogroup draw Kreslení
 * @{
 */

void phong_onDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(phong.program);


	/**
	 * @addtogroup task1 První úkol
	 * @{
	 *
	 * @todo 1.2.) Doprogramujte kreslící funkci phong_onDraw().
	 * Zde byste měli aktivovat vao a spustit kreslení.
	 * Funcke glDrawElements kreslí indexovaně, vyžaduje 4 parametry:
	 * mode - typ primitia, počet indexů,
	 * typ indexů (velikost indexu), a offset.
	 * Kreslíte trojúhelníky, počet vrcholů odpovídá počtu indexů viz
	 * proměnná bunny.h/bunnyIndices.<br/>
	 * <b>Seznam funkcí, které jistě využijete:</b>
	 *  - glBindVertexArray
	 *  - glDrawElements
	 *
	 * @}
	 */

	// bind vertex puller
	glBindVertexArray(phong.vao);

	// let's draw
	glDrawElements(
		GL_TRIANGLES, sizeof(bunnyIndices) / sizeof(VertexIndex),
		GL_UNSIGNED_INT, 0
	);


	/**
	 * @addtogroup task2 Druhý úkol
	 * @{
	 *
	 * @todo 2.3.) Upravte funkci phong_onDraw().
	 * Nahrajte data matic na grafickou kartu do uniformních proměnných.
	 * Aktuální data matic naleznete v externích proměnných viewMatrix
	 * a projectionMatrix.
	 * <b>Seznam funkcí, které jistě využijete:</b>
	 *  - glUniformMatrix4fv
	 *
	 * @}
	 */

	// set projection matrix and view matrix unform data
	glUniformMatrix4fv(
		phong.projectionMatrixUniform, 1, GL_FALSE, (GLfloat *) &projectionMatrix
	);
	glUniformMatrix4fv(
		phong.viewMatrixUniform, 1, GL_FALSE, (GLfloat *) &viewMatrix
	);


	/**
	 * @addtogroup task3 Třetí úkol
	 * @{
	 *
	 * @todo 3.5.) Ve funkci phong_onDraw() nahrajte pozici světla a pozici
	 * kamery na GPU.
	 * Pozice světla a pozice kamery je v proměnných phong.lightPosition
	 * a cameraPosition.<br/>
	 * <b>Seznam funkcí, které jistě využijete:</b>
	 *  - glUniform3f nebo glUniform3fv
	 *
	 * @}
	 */

	// set camera position and light positon uniform data
	glUniform3fv(phong.cameraPositionUniform, 1, (GLfloat *) &cameraPosition);
	glUniform3fv(
		phong.lightPositionUniform, 1, (GLfloat *) &phong.lightPosition
	);


	// unbind vertex puller
	glBindVertexArray(0);
}

/**
 * @}
 */
