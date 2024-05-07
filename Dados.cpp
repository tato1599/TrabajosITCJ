#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define PI 3.14159265358979324

using namespace std;

static float Xangle = 30.0, Yangle = 10.0, Zangle = 0.0; // Angles to rotate objects.
static int animateMode = 0; // In animation mode?
static int animationPeriod = 50; // Speed of animation (milliseconds).
static float angle1 = 0; // Angle for first dice rotation.
static float angle2 = 0; // Angle for second dice rotation.
static int face1 = 1; // Current face of first dice.
static int face2 = 1; // Current face of second dice.
static float dicePosition1 = 2.0; // Y-position of first dice.
static float dicePosition2 = 2.0; // Y-position of second dice.
static float diceSpeed1 = 0.01; // Speed of dice movement.
static float diceSpeed2 = 0.01; // Speed of dice movement.
static GLuint tableTexture; // ID for table texture.


// Function prototype.
void drawDice(int face);
void updateDicePosition(float& position, float& speed);
void rollDice();
bool checkDiceCollision(float dicePosition, float tableTop);
void printInteraction(void);
void initTextures();
void loadTextureFromFile(const char* filename, GLuint textureID);
void drawTableWithTexture();

// Definir el tamaño de la textura (tamaño de la imagen en píxeles).
const int textureSize = 256;

// Arreglo para almacenar las texturas cargadas desde archivos .raw.
GLuint textures[6];



// Función para cargar una imagen .raw como textura.
void loadTextureFromFile(const char* filename, GLuint textureID)
{
    FILE* file;
    unsigned char* texture;

    // Abrir el archivo .raw de manera segura usando fopen_s.
    if (fopen_s(&file, filename, "rb") != 0)
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }
    // Almacenar la imagen en un arreglo de píxeles.
    texture = (unsigned char*)malloc(textureSize * textureSize * 3);
    fread(texture, textureSize * textureSize * 3, 1, file);
    fclose(file);

	// Asignar la textura al ID de textura proporcionado.
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 0, textureSize, textureSize, 0, 0,100, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Liberar la memoria utilizada por la imagen.

      
    free(texture); // Liberar la memoria utilizada por la imagen.
}

// Función para inicializar las texturas.
void initTextures()
{

    // Cargar las imágenes .raw como texturas para las caras del dado.
    for (int i = 0; i < 6; ++i)
    {
        char filename[20];
        sprintf_s(filename, "%d.png", i + 1);
       
        // Imprimir en consola el nombre del archivo (opcional).
        printf("Cargando textura: %s\n", filename);

		// Generar un ID de textura y cargar la imagen desde el archivo.


        glGenTextures(1, &textures[i]);
        
        loadTextureFromFile(filename, textures[i]);
		if (i == 0) {
			printf("Cargando textura: %s\n", filename);
		}

    }

	// Cargar la textura de la mesa desde un archivo .raw.
	glGenTextures(1, &tableTexture);
	loadTextureFromFile("1.png", tableTexture);
    


	// Habilitar el mapeo de texturas.
	glEnable(GL_TEXTURE_2D);


}


// Función para actualizar la posición del dado y simular el rebote.
void updateDicePosition(float& position, float& speed)
{
    const float tableTop = -1.1; // Altura de la mesa.
    const float gravity = 0.007; // Gravedad simulada.
    const float minSpeed = 0.001; // Velocidad mínima para detener el rebote.

    // Actualizar posición vertical.
    position += speed;

    // Verificar colisión con la mesa.
    if (position <= tableTop)
    {
        // Invertir la dirección vertical (rebote).
        speed = -speed * 0.5; // Coeficiente de restitución (0.5 para simular pérdida de energía).

        // Ajustar la posición para evitar que el dado se hunda en la mesa.
        position = tableTop;

        // Detener el rebote si la velocidad es muy baja.
        if (fabs(speed) < minSpeed)
        {
            speed = 0.0; // Detener el rebote.
        }
    }

    // Aplicar gravedad para simular una caída más rápida.
    speed -= gravity;
}



// Initialization routine.
void setup(void)
{
   
    glClearColor(0.0, 0.1, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Habilitar prueba de profundidad.
    glEnable(GL_LIGHTING); // Habilitar iluminación.
    glEnable(GL_LIGHT0); // Habilitar la primera luz.
    glShadeModel(GL_SMOOTH); // Usar sombreado suave.
    glPointSize(0.008); // Aumentar el tamaño de los puntos.

    // Configurar la posición y color de la luz.
    GLfloat light_position[] = { 0.0, 1.0, 2.0, 0.0 }; // Posición de la luz (en el espacio de la escena).
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; // Color ambiental de la luz.
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // Color difuso de la luz.
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Color especular de la luz.

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Habilitar la luz.
    glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL); // Habilitar el seguimiento del color del material.
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // Configurar el color del material.
	glMateriali(GL_FRONT, GL_SHININESS, 128); // Configurar el brillo del material.




}

// Drawing routine for the table with texture.
void drawTableWithTexture()
{
	
    // Bind the texture for the table.
    glBindTexture(GL_TEXTURE_2D, tableTexture); // Assuming you've loaded a table texture.

    // Define vertices and texture coordinates for a cube (scaled to represent the table).
    glBegin(GL_QUADS);
    // Front face
    glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -0.1, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(2.0, -0.1, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 0.1, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 0.1, 1.0);


    // Add similar code for other faces of the cube (sides, back, etc.)
    glEnd();
}


// Drawing routine.
void drawScene(void)
{
	glEnable(GL_TEXTURE_2D);
    //glDisable(GL_LIGHTING); // Desactivar la iluminación para ver colores sin afectar por la luz.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Camera position and orientation.

    // Draw rectangular prism as table.

    glPushMatrix();
    
    glColor3f(0.54, 0.27, 0.07); // Brown color for table.
    glTranslatef(0.0, -1.5, 0.0);
    glScalef(4.0, 0.1, 2.0); // Scale to form a larger rectangular prism.
    glutSolidCube(1.0);
    glColor3f(0.0, 0.0, 0.0); // Black color for table edges.
    glutWireCube(1.0); // Draw wireframe of the table.
    glPopMatrix();

    // Draw first dice.
    glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for dice.
    glTranslatef(-1.5, dicePosition1, 0.0); // Position first dice.
    glRotatef(angle1, 1.0, 1.0, 1.0); // Rotate dice.
    drawDice(face1); // Draw current face of first dice.
    glColor3f(0.0, 0.0, 0.0); // Black color for dice edges.
    glutWireCube(1.0); // Draw wireframe of the dice.
    glPopMatrix();

    // Draw second dice.
    glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for dice.
    glTranslatef(1.5, dicePosition2, 0.0); // Position second dice.
    glRotatef(angle2, -1.0, -1.0, -1.0); // Rotate dice.
    drawDice(face2); // Draw current face of second dice.
    glColor3f(0.0, 0.0, 0.0); // Black color for dice edges.
    glutWireCube(1.0); // Draw wireframe of the dice.
    glPopMatrix();

    glutSwapBuffers();
}

// Timer function to animate dice rotation and movement.
void animate(int value)
{
    if (animateMode)
    {
        // Actualizar ángulos de rotación.
        angle1 += 1.0; // Rotación lenta del dado 1.
        angle2 -= 1.0; // Rotación lenta del dado 2.
        if (angle1 > 360.0) angle1 -= 360.0;
        if (angle2 < 0.0) angle2 += 360.0;

        // Cambiar caras aleatoriamente cada ciertas iteraciones.
        if (value % 50 == 0)
        {
            face1 = rand() % 6 + 1;
            face2 = rand() % 6 + 1;
        }

        // Actualizar la posición vertical de los dados.
        updateDicePosition(dicePosition1, diceSpeed1); // Actualizar posición del dado 1.
        updateDicePosition(dicePosition2, diceSpeed2); // Actualizar posición del dado 2.

        // Detener la animación si ambos dados están sobre la mesa.
        if (dicePosition1 <= -1.4 && dicePosition2 <= -1.4)
            animateMode = 0;
    }

    glutTimerFunc(animationPeriod, animate, value + 1);
    glutPostRedisplay(); // Volver a renderizar la escena.
}



// Draw a single face of a 3D dice with textures.
void drawDice(int face)
{
    // Configurar propiedades del material para los dados (por ejemplo, color difuso y especular).
    GLfloat dice_material_ambient[] = { 0.0, 0.0, 0.0, 1.0 }; // Color ambiental (poco o nada de luz ambiental).
    GLfloat dice_material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // Color difuso (color base del dado).
    GLfloat dice_material_specular[] = { 0.5, 0.5, 0.5, 1.0 }; // Color especular (reflejos de luz).
    GLfloat dice_material_shininess[] = { 32.0 }; // Brillo del material.

    glMaterialfv(GL_FRONT, GL_AMBIENT, dice_material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dice_material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, dice_material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, dice_material_shininess);

    // Definir los colores para cada cara del dado.
    float colors[6][3] = {
        {1.0, 0.0, 0.0},  // Red for Face 1
        {0.0, 1.0, 0.0},  // Green for Face 2
        {0.0, 0.0, 1.0},  // Blue for Face 3
        {1.0, 1.0, 0.0},  // Yellow for Face 4
        {1.0, 0.0, 1.0},  // Magenta for Face 5
        {0.0, 1.0, 1.0}   // Cyan for Face 6
    };

    // Definir las coordenadas de textura para cada cara del dado.
    float texCoords[6][4][2] = {
        { { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } }, // Face 1
        { { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } }, // Face 2
        { { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } }, // Face 3
        { { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } }, // Face 4
        { { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } }, // Face 5
        { { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } }  // Face 6
    };

    // Definir los vértices para cada cara del dado.
    float vertices[6][4][3] = {
        { { -0.5, -0.5, 0.5 }, { 0.5, -0.5, 0.5 }, { 0.5, 0.5, 0.5 }, { -0.5, 0.5, 0.5 } }, // Face 1
        { { -0.5, -0.5, -0.5 }, { 0.5, -0.5, -0.5 }, { 0.5, 0.5, -0.5 }, { -0.5, 0.5, -0.5 } }, // Face 2
        { { -0.5, 0.5, -0.5 }, { -0.5, 0.5, 0.5 }, { 0.5, 0.5, 0.5 }, { 0.5, 0.5, -0.5 } }, // Face 3
        { { -0.5, -0.5, -0.5 }, { -0.5, -0.5, 0.5 }, { 0.5, -0.5, 0.5 }, { 0.5, -0.5, -0.5 } }, // Face 4
        { { 0.5, -0.5, -0.5 }, { 0.5, -0.5, 0.5 }, { 0.5, 0.5, 0.5 }, { 0.5, 0.5, -0.5 } }, // Face 5
        { { -0.5, -0.5, -0.5 }, { -0.5, -0.5, 0.5 }, { -0.5, 0.5, 0.5 }, { -0.5, 0.5, -0.5 } }  // Face 6
    };
    

	float normals[6][3] = {
		{ 0.0, 0.0, 1.0 }, // Face 1
		{ 0.0, 0.0, -1.0 }, // Face 2
		{ 0.0, 1.0, 0.0 }, // Face 3
		{ 0.0, -1.0, 0.0 }, // Face 4
		{ 1.0, 0.0, 0.0 }, // Face 5
		{ -1.0, 0.0, 0.0 }  // Face 6
	};

	

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
        glColor3fv(colors[i]); // Aplicar el color correspondiente a la cara del dado.

	
		glNormal3fv(normals[i]);
	
		for (int j = 0; j < 4; j++)
	
		{
		
			glTexCoord2fv(texCoords[i][j]);
			glVertex3fv(vertices[i][j]);
		}
	}



    glEnd();
}



// Función para detectar colisión y ajustar el rebote.
bool checkDiceCollision(float dicePosition, float tableTop)
{
    return dicePosition <= tableTop;
}


// Function to roll the dice.
void rollDice()
{
    if (!animateMode)
    {
        animateMode = 1; // Start animation.
        angle1 = 0; // Reset angles.
        angle2 = 0;
        dicePosition1 = 2.0; // Move dice above the table.
        dicePosition2 = 2.0;
        face1 = 1; // Reset dice faces.
        face2 = 1;
        diceSpeed1 = 0.01; // Reset dice speed.
        diceSpeed2 = 0.01;
    }
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        rollDice(); // Spacebar to roll the dice.
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press spacebar to roll the dice." << endl;
    cout << "Press Esc to exit." << endl;
}

// Main routine.
int main(int argc, char** argv)
{
	

	initTextures();

    srand(time(NULL)); // Seed random number generator.
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dice Animation");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(5, animate, 1);
    glutMainLoop();

    return 0;
}
