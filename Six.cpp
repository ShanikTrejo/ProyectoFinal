//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//******* Alumno (s): Trejo Luna Eva Marion Shanik************//
//*************  	Visual Studio 2017					******//
//************* Ejercicio de Casa 12					******//
//************************************************************//
#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"
//Solo para Visual Studio 2015
#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


									//NEW// Keyframes
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;

#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	float movBrazoDer;
	float movBrazoDerInc;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 5;			//introducir datos
bool play = false;
int playIndex = 0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;
//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };

CTexture text1;
CTexture text2;
CTexture text3;	//Barda
CTexture text4;	//Pavimento
CTexture text5;	//Pasto
CTexture text6;	//Casa01
CTexture text7;//Edificio
CTexture text8;//Comida Mexicana
CTexture text9;//Metal de colores
CTexture tree;
//MIS TEXTURAS
CTexture Pasto;
CTexture Barda;
CTexture Pavimento;
CTexture t_metal01;//Textura de Metal gris
CTexture t_METAL;//Metal de colores

//Transparencias
//JL
CTexture Batman;
CTexture Jocker;
CTexture Wonder;
CTexture Superman;
CTexture Supergirl;
CTexture Flash;
CTexture Green;
//LOONEY TUNES
CTexture Bugs;
CTexture Lola;
CTexture Silvestre;
CTexture Piolin;
CTexture Lucas;
CTexture Sam;
CTexture taz;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito

				//Figuras de 3D Studio
CModel kit;
CModel llanta;
CModel casita;
CModel oldhouse;
//DECLARACIONES DEL CIRCUITO DE BOOMERANG
//carritos
float angRot = 0.0;//Angulo de rotacion
float angRotAux = 0.0;//Angulo para el Vudu
float movKitX = 0.0;//Movimiento en X
float movKitY = 0.0;//Movimiento en Y
float movKitZ = 0.0;//Movimiento en Z
float rotKit = 0.0;//Rotacion de las llantas
float rotD = 0.0;
float rotI = 0.0;
float X = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;//Animacion
bool g_avanza = false;//Anaza
bool g_reversa = false;//Reversa
bool circuito = false;//Circuito Boomerang: Maquina de Estados
bool recorrido1 = true;//Estado (A):Posicion Inicial Z=0
bool recorrido2 = false;//Estado (B): Sube en reversa hasta Z=-100
bool recorrido3 = false;//Estado (C): Z=-100
bool recorrido4 = false;//Estado (D):Avanza hasta la primer vuelta de 360° <<Z=155>>
bool recorrido5 = false;//Estado (E): Vuelta de 360°
bool recorrido6 = false;//Estado (F): Inclinacion <<Sube hasta Z=100>>
bool recorrido7 = false;//Estado (G): Sube una loma de 180° <<Z=150>>
bool recorrido8 = false;//Estado (H):  al llegar a 180°  va avanzazar desde X=0 
bool recorrido9 = false;//Estado (I):avanza en curva de 180° <<hasta X=100>>
bool recorrido10 = false;//Estado (J):Sube una loma de 180°
bool recorrido11 = false;//Estado (K): Baja en Z´ hasta Z´=250
bool recorrido12 = false;//Estado (L): Va en reversa desde <<Z´=250>> hasta <<Z=0>>

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	movBrazoDer = KeyFrame[0].movBrazoDer;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;

}

void ciudad()
{

	glPushMatrix(); //Pavimento
	  glTranslatef(0.0, 0.0, 0.0);
	  glScalef(125, 0.1, 125);
	  glDisable(GL_LIGHTING);
	  fig3.prisma2(text4.GLindex, 0);
	  glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	 glTranslatef(0.0, 0.0, 0.0);
	 glScalef(100, 0.1, 100);
	 glDisable(GL_LIGHTING);
	fig3.prisma2(text5.GLindex, 0);
	
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, 7.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Restaurante1
	glTranslatef(0.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	//glRotatef(180,0,0,1);
	glScalef(7, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//Restaurante2
	glPushMatrix();
	glTranslatef(7.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(8, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text7.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//Restaurante3
	glPushMatrix();
	glTranslatef(15.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(8, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text8.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//BardaTrasera(X+)
	glPushMatrix();
	glTranslatef(29.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(20, 5, 5);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//BardaTrasera(X-)
	glPushMatrix();
	glTranslatef(-21.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(-35, 5, 5);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//BardaLateral(-)
	glPushMatrix();
	glTranslatef(-51, 3.0, 0.0);
	glRotatef(-90, 0, 0, 1);
	glScalef(-5, 5, 90);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//BardaLateral(+)
	glPushMatrix();
	glTranslatef(51, 3.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(-5, 5, 90);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//Baño Niñas
	glPushMatrix();
	glTranslatef(45.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(4, 5.0, 4);
	glDisable(GL_LIGHTING);
	fig5.prisma2(Lola.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//Baño niños
	glPushMatrix();
	glTranslatef(41.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(4, 5.0, 4);
	glDisable(GL_LIGHTING);
	fig5.prisma2(Bugs.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//Baño Niñas
	glPushMatrix();
	glTranslatef(-45.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(4, 5.0, 4);
	glDisable(GL_LIGHTING);
	fig5.prisma2(Wonder.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//Baño niños
	glPushMatrix();
	glTranslatef(-41.0, 3.0, -45.0);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5.0, 4);
	glDisable(GL_LIGHTING);
	fig5.prisma2(Batman.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	/*//Boomerang
	glPushMatrix();
	glTranslatef(-10.0, 10.0, -10.0);
	glRotatef(0, 0, 1, 0);
	glScalef(0.25, 5.0,0.25 );
	glDisable(GL_LIGHTING);
	fig5.cilindro(t_metal01.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();*/

}

void arbol_alpha()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, tree.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void arbol_blend()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);     // Turn Blending On
							//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, tree.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);//Turn Blending Off
	glEnable(GL_LIGHTING);
}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	fig7.prisma(2.0, 2.0, 1, text2.GLindex);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	fig7.cilindro(0.25, 0.25, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	fig7.esfera(0.75, 15, 15, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho-->
	glTranslatef(1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
	glRotatef(-45, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <--
	glTranslatef(-1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(25, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glTranslatef(-0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(0, -1.5, 0);
	fig7.prisma(1, 2, 1, 0);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + rotRodIzq, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	ciudad();
	//monito();
	// endList
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	//ESTRUCTURA DEL BOOMERANG
	t_metal01.LoadBMP("metal2.bmp");//Textura de Metal sin esta no se puede visualizar la imagen
	t_metal01.BuildGLTexture();
	t_metal01.ReleaseImage();
	////////MIS TEXTURAS////////////
	t_METAL.LoadBMP("METAL.tga");//Textura de Metal sin esta no se puede visualizar la imagen
	t_METAL.BuildGLTexture();
	t_METAL.ReleaseImage();
	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/barda.tga");/////////////
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/grass.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();
	text7.LoadTGA("city/restaurante.tga");
	text7.BuildGLTexture();
	text7.ReleaseImage();
	text8.LoadTGA("city/taquitos.tga");
	text8.BuildGLTexture();
	text8.ReleaseImage();
	text8.LoadTGA("city/metalc.tga");
	text8.BuildGLTexture();
	text8.ReleaseImage();
	tree.LoadTGA("Tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();
	////////////////////////////////////////////

	//JL:Batman,Jocker,Wonder,Superman,Supergirl, Flash, Green
	Batman.LoadTGA("batmancontransparencias.tga");
	Batman.BuildGLTexture();
	Batman.ReleaseImage();
	Jocker.LoadTGA("jockerConTransparencias.tga");
	Jocker.BuildGLTexture();
	Jocker.ReleaseImage();
	Wonder.LoadTGA("Wonderwomancontransparencias.tga");
	Wonder.BuildGLTexture();
	Wonder.ReleaseImage();
	Superman.LoadTGA("Supermancontransparencias.tga");
	Superman.BuildGLTexture();
	Superman.ReleaseImage();
	Supergirl.LoadTGA("Supergirlcontransparencias.tga");
	Supergirl.BuildGLTexture();
	Supergirl.ReleaseImage();
	Flash.LoadTGA("Flash1ConTransparencias.tga");
	Flash.BuildGLTexture();
	Flash.ReleaseImage();
	Green.LoadTGA("greenlanternConTransparencias.tga");
	Green.BuildGLTexture();
	Green.ReleaseImage();
	//Looney Tunes: Bugs y Lola, Silvestre, Piolin, Lucas,Sam, taz
	Bugs.LoadTGA("BugsBunnyConTransparencias.tga");
	Bugs.BuildGLTexture();
	Bugs.ReleaseImage();
	Lola.LoadTGA("LolaBunnyConTransparencias.tga");
	Lola.BuildGLTexture();
	Lola.ReleaseImage();
	Silvestre.LoadTGA("Silvestrecontransparencias.tga");
	Silvestre.BuildGLTexture();
	Silvestre.ReleaseImage();
	Piolin.LoadTGA("Piolin1.contransparencias.tga");
	Piolin.BuildGLTexture();
	Piolin.ReleaseImage();
	Lucas.LoadTGA("LucasconTransparencias.tga");
	Lucas.BuildGLTexture();
	Lucas.ReleaseImage();
	Sam.LoadTGA("Sam_Bigotescontransparencias.tga");
	Sam.BuildGLTexture();
	Sam.ReleaseImage();
	taz.LoadTGA("tazcontransparencias.tga");
	taz.BuildGLTexture();
	taz.ReleaseImage();

	kit._3dsLoad("kitt.3ds");
	//kit.VertexNormals();

	llanta._3dsLoad("k_rueda.3ds");

	casita._3dsLoad("Dollshouse.3ds");

	oldhouse._3dsLoad("oldhouse/oldhouse.3ds");
	oldhouse.LoadTextureImages();
	oldhouse.GLIniTextures();
	oldhouse.ReleaseTextureImages();

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();
	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].giroMonito = 0;
	KeyFrame[0].movBrazoDer = 0;

	KeyFrame[1].posX = 20;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -3.5;
	KeyFrame[1].rotRodIzq = 60;
	KeyFrame[1].giroMonito = -90.0;
	KeyFrame[1].movBrazoDer = 40;

	KeyFrame[2].posX = 20;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = 4.0;
	KeyFrame[2].rotRodIzq = -20.0;
	KeyFrame[2].giroMonito = 0;
	KeyFrame[2].movBrazoDer = 0;

	KeyFrame[3].posX = 20;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = 4.0;
	KeyFrame[3].rotRodIzq = 40.0;
	KeyFrame[3].giroMonito = 45;
	KeyFrame[3].movBrazoDer = 90;

	KeyFrame[4].posX = 20;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = 4.0;
	KeyFrame[4].rotRodIzq = -40.0;
	KeyFrame[4].giroMonito = -45;
	KeyFrame[4].movBrazoDer = -90;
	//NEW//////////////////NEW//////////////////NEW//////////////////

}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
							//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

/*void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	PlaySound("MusicaDeFondo.wav", NULL, SND_LOOP | SND_ASYNC);

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//glScalef(0.5, 0.5, 0.5);
	//monito();
	glCallList(ciudad_display_list);
	glTranslatef(posX, posY, posZ);
	glRotatef(giroMonito, 0, 1, 0);
	monito();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();


	glPushMatrix(); //Casa M0delo 3ds
	glTranslatef(-12.0, 0.0, -9.0);
	glScalef(0.3, 0.3, 0.3);
	casita.GLrender(NULL, _SHADED, 1);
	glPopMatrix();

	glPushMatrix(); //Casa M0delo 3ds
	glTranslatef(-32.0, 0.0, -9.0);
	glScalef(0.7, 0.7, 0.7);
	oldhouse.GLrender(NULL, _SHADED, 1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	//Para lograr la inclinacion
	glTranslatef(movKitX, 4 + movKitY, movKitZ); //Agrego variable para que suba la inclinacion
	glRotatef(rotKit, 0, 1, 0);
	glRotatef(X, 1, 0, 0);
	kit.GLrender(NULL, _SHADED, 1.0); //Dibujamos la carroceria
									  //llanta.GLrender(NULL,_SHADED,1.0);

									  //Colocar aquí las llantas
	glPushMatrix(); //llanta frontal der
	glTranslatef(-6, -1, 7.5);
	glRotatef(rotD, 0, 0, -1); //rotacion de las llantas cuando vuela
	glRotatef(-rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //llanta frontal izq
	glTranslatef(6, -1, 7.5);
	glRotatef(rotI, 0, 0, 1); //rotacion de las llantas cuando vuela
	glRotatef(180, 0, 1, 0);
	glRotatef(rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //llanta trasera der
	glTranslatef(-6, -1, -9.5);
	glRotatef(rotD, 0, 0, -1); //rotacion de las llantas cuando vuela
	glRotatef(-rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //llanta trasera izq
	glTranslatef(6, -1, -9.5);
	glRotatef(rotI, 0, 0, 1); //rotacion de llanta cuando vuela
	glRotatef(180, 0, 1, 0);
	glRotatef(rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPopMatrix();


	glPushMatrix(); //Flecha
	glScalef(7, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma_anun(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-30, 0, 10);
	arbol_alpha();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	//Transparencias de los personajes
	//JL:Batman,Jocker,Wonder,Superman,Supergirl, Flash, Green
	//Batman
	glTranslatef(-20, 0, -10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Batman.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Wonder_woman
	glTranslatef(-10, 0, -10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Wonder.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Superman
	glTranslatef(-15, 0, -15);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Superman.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Green Lantern
	glTranslatef(-11, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Green.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Flash
	glTranslatef(-15, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Flash.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Supergirl
	glTranslatef(-10, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Supergirl.GLindex);
	glDisable(GL_ALPHA_TEST);

	//Looney Tunes: Bugs y Lola, Silvestre, Piolin, Lucas,Sam, taz
	//Bugs
	glTranslatef(25, 0, 25);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Bugs.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Lola
	glTranslatef(13, 0, 13);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Lola.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Silvestre
	glTranslatef(8, 0, -8);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Silvestre.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Piolin
	glTranslatef(15, 0, 15);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Piolin.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Lucas
	glTranslatef(20, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Lucas.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Sam
	glTranslatef(15, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Sam.GLindex);
	glDisable(GL_ALPHA_TEST);
	//TAZ
	glTranslatef(10, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, taz.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	//////////////////////////////////

	glColor3f(0.0, 0.40, 0.40);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "Proyecto Final");
	glColor3f(0.0, 0.40, 0.40);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glutSwapBuffers();

}*/
void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	PlaySound("MusicaDeFondo.wav", NULL, SND_LOOP | SND_ASYNC);
	glPushMatrix();
	glRotatef(g_lookupdown, 1.0f, 0, 0);
	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//glScalef(0.5, 0.5, 0.5);
	//monito();
	glCallList(ciudad_display_list);
	glTranslatef(posX, posY, posZ);
	glRotatef(giroMonito, 0, 1, 0);
	monito();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();//(Cierre1)
	glRotatef(90, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	glTranslatef(movKitX, 4, movKitZ);
	glRotatef(rotKit, 0, 1, 0);
	kit.GLrender(NULL, _SHADED, 1.0); //Dibujamos la carroceria
									  //llanta.GLrender(NULL,_SHADED,1.0);

									  //Colocar aquí las llantas
	glPushMatrix(); //llanta frontal der
	glTranslatef(-6, -1, 7.5);
	glRotatef(-rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //llanta frontal izq
	glTranslatef(6, -1, 7.5);
	glRotatef(180, 0, 1, 0);
	glRotatef(rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //llanta trasera der
	glTranslatef(-6, -1, -9.5);
	glRotatef(-rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //llanta trasera izq
	glTranslatef(6, -1, -9.5);
	glRotatef(180, 0, 1, 0);
	glRotatef(rotTires, 1, 0, 0);
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPopMatrix();//(Cierre1)

	glPushMatrix();
	glTranslatef(-30, 0, 10);
	arbol_alpha();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();

	glTranslatef(0.0, 0.0, -4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, 4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//Transparencias de los personajes
	//JL:Batman,Jocker,Wonder,Superman,Supergirl, Flash, Green
	//Batman
	glTranslatef(-20, 0, -10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Batman.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Jocker
	//glTranslatef(-15, 0, -10);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.1);
	//fig7.prisma(3, 3, 0.5, Jocker.GLindex);
	//glDisable(GL_ALPHA_TEST);
	//Wonder_woman
	glTranslatef(-10, 0, -10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Wonder.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Superman
	glTranslatef(-15, 0, -15);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Superman.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Green Lantern
	glTranslatef(-11, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Green.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Flash
	glTranslatef(-15, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Flash.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Supergirl
	glTranslatef(-10, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Supergirl.GLindex);
	glDisable(GL_ALPHA_TEST);

	//Looney Tunes: Bugs y Lola, Silvestre, Piolin, Lucas,Sam, taz
	//Bugs
	glTranslatef(25, 0, 25);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Bugs.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Lola
	glTranslatef(13, 0, 13);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Lola.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Silvestre
	glTranslatef(8, 0, -8);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Silvestre.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Piolin
	glTranslatef(15, 0, 15);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Piolin.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Lucas
	glTranslatef(20, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Lucas.GLindex);
	glDisable(GL_ALPHA_TEST);
	//Sam
	glTranslatef(15, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, Sam.GLindex);
	glDisable(GL_ALPHA_TEST);
	//TAZ
	glTranslatef(10, 0, 10);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig7.prisma(3, 3, 0.5, taz.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	//////////////////////////////////

	glColor3f(0.0, 0.40, 0.40);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "Proyecto Final");
	glColor3f(0.0, 0.40, 0.40);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glutSwapBuffers();

}

void animacion()
{
	fig3.text_izq -= 0.01;
	fig3.text_der -= 0.01;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;
	if (g_fanimacion)
	{
		if (g_avanza)
		{
			movKitZ += 1.0;
			rotTires -= 10;
			if (movKitZ > 130)
				g_avanza = false;
		}
		else
		{
			movKitZ -= 1.0;
			rotTires += 10;
			if (movKitZ < 0)
				g_avanza = true;
		}
	}

	if (circuito)//Maquina de Estados 
	{
		if (recorrido1)//Estado(A):Desde Z=0 comienza a volar hasta Z= 155 
		{
			movKitZ++;//Se incrementa el movimiento en el eje Z
			if (movKitZ > 155)//Se limita el recorrido a 155 en el eje Z
			{
				recorrido1 = false;//Si el recorrido 1 es falso  se desactiva
				recorrido2 = true;//Si el recorrido 2 es verdadero  se activa
			}
		}
		if (recorrido2)////Estado(B):Desde X=0 comienza a volar hasta X= 125 las llantas comienzan a rotar
		{
			rotKit = 90;//Va a dar una vuelta de 90°
			X = 0;//Se inicializa el angulo en 0°
			movKitX++;//Se incrementa el movimiento en el eje X
			if (movKitX > 125)//Se limita el recorrido a 125 en el eje X
			{
				recorrido2 = false;//Si el recorrido 2 es falso  se desactiva
				recorrido3 = true;//Si el recorrido 3 es verdadero  se activa

			}
		}
		if (recorrido3)//Estado(C):Desde Z=155 comienza a volar hasta Z=0
		{
			rotKit = 180;//Va a dar una vuelta de 180°
			movKitZ--;//Se decrementa el movimiento en el eje Z
			if (movKitZ < -155)//Regresa de Z=155 a Z=0
			{
				recorrido3 = false;//Si el recorrido 3 es falso  se desactiva
				recorrido4 = true;//Si el recorrido 3 es verdadero  se activa
			}

		}

		if (recorrido4)//Estado(D):Desde X=125 comienza a volar hasta X= 0
		{
			rotKit = 280;//Va a dar una vuelta de 280°
			movKitX--;//Se decrementa el movimiento en el eje X
			if (movKitX < 0)//Regresa de X=125 a X=0
			{
				recorrido4 = false;//Si el recorrido 4 es falso  se desactiva
				recorrido5 = true;//Si el recorrido 5 es verdadero  se activa
			}


		}


		if (recorrido5)//Estado(E)
		{
			rotKit = 90;//Va a dar una vuelta de 90°
			movKitX--;//Se decrementa el movimiento en el eje X
			if (movKitX < 0)
			{
				recorrido5 = false;//Si el recorrido 5 es falso  se desactiva
				recorrido6 = true;//Si el recorrido 6 es verdadero  se activa
			}

		}
		if (recorrido6) //Estado(F)
		{
			rotKit = 0.0;//Rota a 0°
			X = -45.0;//Se decrementa el angulo a 45°
			movKitZ += 0.1;//Incrementa el mov en el eje Z
			movKitY += 0.33;//Incrementa el mov en el eje X
			rotI -= 0.35;//Rota las llantas izquierdas
			rotD = rotI - 0.35;//Rota las llantas derechas
			if (movKitZ >= -120.0)//Se valida la distancia recorrida en el eje Z
			{
				recorrido6 = false;//Si el recorrido 6 es falso  se desactiva
				recorrido7 = true;//Si el recorrido 7 es verdadero  se activa
			}


		}

		if (recorrido7) //Estado(G)
		{
			rotKit = 0;
			X = 0;
			movKitZ++;

			if (movKitZ >= 120)
			{
				recorrido7 = false;//Si el recorrido 7 es falso  se desactiva
				recorrido8 = true;//Si el recorrido 8 es verdadero  se activa
			}
		}

		if (recorrido8)//Estado(H)
		{
			rotKit = 0.0;
			X = 47.0;
			movKitZ += 0.10;
			movKitY -= 0.35;
			rotI += 0.35;
			rotD = rotI + 0.35;
			if (movKitZ >= 150) {

				movKitY = 0.0; //Estado (H) al estado (B)
				recorrido8 = false;//Si el recorrido 8 es falso  se desactiva
				recorrido2 = true; //Si el recorrido 2 es verdadero  se activa
			}
		}

	}

	//Movimiento del monito
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			giroMonito += KeyFrame[playIndex].giroMonitoInc;
			movBrazoDer += KeyFrame[playIndex].movBrazoDerInc;

			i_curr_steps++;
		}

	}

	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'O':		//  
	case 'o':
		g_fanimacion ^= true; //Activamos/desactivamos la animacíon
		circuito = false;
		break;

	case 'i':		//  
	case 'I':
		circuito ^= true; //Activamos/desactivamos la animacíon
		g_fanimacion = false;
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex>1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;

	case 'y':
	case 'Y':
		posZ++;
		break;

	case 'g':
	case 'G':
		posX--;
		break;

	case 'h':
	case 'H':
		posZ--;
		break;

	case 'j':
	case 'J':
		posX++;
		break;

	case 'b':
		rotRodIzq++;
		break;

	case 'B':
		rotRodIzq--;
		break;

	case 'p':
		giroMonito++;
		break;

	case 'P':
		giroMonito--;
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex >1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}


void menu(int id)
{

}

int main(int argc, char** argv)   // Main Function
{
	int submenu;

	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto Final: SIX FLAGS MEXICO"); // Nombre de la Ventana

														 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();          // 

	return 0;
}