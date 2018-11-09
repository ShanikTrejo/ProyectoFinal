//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


int w = 500, h = 500;
int frame=0,time,timebase=0;
int deltaTime = 0;
char s[30];
float angBrazo = 0.0;

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01

CTexture tree;
CTexture edificio;
CTexture esfera;
CTexture madera;               //declaras
CTexture clorofila;
CTexture fuego;
CTexture tacos;

CFiguras cubo;
CFiguras sky;
CFiguras holo;

//END NEW//////////////////////////////////////////


CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito

CFiguras miobj;


float movKit = 0;//MUEVE POLEO
//float volKit = 0.0;
bool g_fanimacion = false;
bool g_fanimacion2 = false;
bool g_fanimacion3 = false;
bool g_fanimacion4 = false;

float rot = -7.0; //rotaR BASE

float rot2 = 0.0;





void ciudad ()
{
	glRotatef(90, 1, 0, 0);
		glPushMatrix(); //Camino1
			glTranslatef(23.5,0.0,0.0);
			glScalef(10,0.1,7);
			
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino2
			glTranslatef(-23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,-4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		



		//glPushMatrix(); //Casa01
		//	glTranslatef(0.0,3.0,7.0);
		//	glRotatef(90,1,0,0);
		//	glRotatef(180,0,0,1);
		//	glScalef(6,5.0,6);
		//	glDisable(GL_LIGHTING);
		//	fig5.prisma2(text6.GLindex, 0);
		//	glEnable(GL_LIGHTING);
		//glPopMatrix();

		//glPushMatrix(); //Casa01
		//	glTranslatef(0.0,3.0,-7.0);
		//	glRotatef(90,1,0,0);
		//	//glRotatef(180,0,0,1);
		//	glScalef(6,5.0,6);
		//	glDisable(GL_LIGHTING);
		//	fig5.prisma2(text6.GLindex, 0);
		//	glEnable(GL_LIGHTING);
		//glPopMatrix();
}

void arbol()
{
	glPushMatrix();
					glDisable(GL_LIGHTING);
					glEnable( GL_ALPHA_TEST );
					//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
					glAlphaFunc( GL_GREATER, 0.1 );
					//glEnable(GL_BLEND);     // Turn Blending On
					//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture(GL_TEXTURE_2D, tree.GLindex);
					glBegin(GL_QUADS); //plano
						glColor3f(1.0, 1.0, 1.0);
						glNormal3f( 0.0f, 0.0f, 1.0f);
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
						glNormal3f( 0.0f, 0.0f, 1.0f);
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
						glNormal3f( 0.0f, 0.0f, 1.0f);
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
						glNormal3f( 0.0f, 0.0f, 1.0f);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
					glEnd();
					glDisable( GL_ALPHA_TEST );
					//glDisable(GL_BLEND);        // Turn Blending Off
					//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
					glEnable(GL_LIGHTING);
				
			glPopMatrix();
}

GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();


	tree.LoadTGA("tree01.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	edificio.LoadTGA("edificio.tga");
	edificio.BuildGLTexture();
	edificio.ReleaseImage();


	esfera.LoadTGA("tapiz1.tga");
	esfera.BuildGLTexture();           //carga
	esfera.ReleaseImage();

	madera.LoadTGA("dia.tga");
	madera.BuildGLTexture();           //carga
	madera.ReleaseImage();

	clorofila.LoadTGA("ama.tga");
	clorofila.BuildGLTexture();           //carga
	clorofila.ReleaseImage();

	tacos.LoadTGA("pizza.tga");
	tacos.BuildGLTexture();           //carga
	tacos.ReleaseImage();
	
	fuego.LoadTGA("llama.tga");
	fuego.BuildGLTexture();           //carga
	fuego.ReleaseImage();
	//END NEW////

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
		
	glPushMatrix();
		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

	glPushMatrix();		

			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
				glColor3f(1, 1, 1);
				glCallList(ciudad_display_list);
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();
			
			glPushMatrix(); //Flecha
				glScalef(7,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma_anun(text3.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glEnable ( GL_COLOR_MATERIAL );
		

			//glPushMatrix();
			//	glTranslatef(17, 0, -10);
			//	glColor3f(1.0, 1.0, 1.0);     //POSICION
			//	fig1.esfera(4, 20, 20, text2.GLindex);
			//glPopMatrix();

			//glPushMatrix(); 
			//	glScaled(0.5,0.5,0.5);
			//	miobj.cilindro(3, 12, 20, madera.GLindex);
			//	
			//glPushMatrix();
			//			glTranslatef(0, 12,0);
			//			miobj.cono(20, 8, 20, clorofila.GLindex);

			//		glPushMatrix();
			//					glEnable(GL_ALPHA_TEST);
			//					glAlphaFunc(GL_GREATER, 0.1);
			//					glTranslated(8,3,0);
			//					miobj.esfera(1.5, 20, 20, esfera.GLindex);
			//					glTranslated(-2, 4, 1);
			//					miobj.esfera(1.5, 20, 20, tacos.GLindex);
			//					glTranslated(-1.6, 4, 2);
			//					miobj.esfera(2, 20, 20, fuego.GLindex);
			//					glDisable(GL_ALPHA_TEST); 
			//		glPopMatrix();

			//	glPopMatrix();



				glPushMatrix(); //base arriba
				glTranslatef(-4.0, 42, -23.0);//izq, alto,atras
				glRotatef(0, 1, 0, 0);
				glScalef(10, 7.0, 12);// (largo,alto,ancho)
				glRotatef(90, 1, 0, 0); //textura

				glDisable(GL_LIGHTING);
				glRotatef(rot,1,0,0);
				fig5.prisma2(clorofila.GLindex, clorofila.GLindex);
				glEnable(GL_LIGHTING);

				glPushMatrix(); //poleo
				glTranslatef(0, 0, 3);//izq, prof,alto
				glScalef(0.25, 0.25, 5);// (largo,alto,ancho)

				//glRotatef(3,0,1,0);


				glDisable(GL_LIGHTING);
				//glRotatef(15,1,0,0);
				fig5.prisma2(madera.GLindex, madera.GLindex);
				glEnable(GL_LIGHTING);
				glPushMatrix();

						glDisable(GL_LIGHTING);
						glTranslatef(0,0,0.4);//derecha,prof,-pariba
						glScaled(0.5, 0.5, 0.5);
						glRotatef(90, 1, 0, 0);
						glRotatef(rot2, 0, 1, 0);
						miobj.cilindro(7.5, 0.2, 20, clorofila.GLindex);

						glEnable(GL_LIGHTING);

				glPopMatrix();

				glPopMatrix();

				glPopMatrix();


				////////////////////////////////////
				glPushMatrix(); //PATOTA1
				glTranslatef(0.0, 20.0, -7.0);
				glRotatef(60, 1, 0, 0);
				glScalef(1.5, 2.0, 45);//ancho,profundo,alto
				//glRotatef(30, 1, 0, 0);
				glDisable(GL_LIGHTING);
				fig5.prisma2(madera.GLindex, madera.GLindex);
				//fig5.prisma_anunprisma(
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //PATOTA4
				glTranslatef(-8.0, 20.0, -7.0);
				glRotatef(60, 1, 0, 0);
				glScalef(1.5, 2.0, 45);//ancho,profundo,alto
				//glRotatef(30, 1, 0, 0);
				glDisable(GL_LIGHTING);
				fig5.prisma2(madera.GLindex, madera.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix();//PATOTA2
				glTranslatef(0, 18.0, -40.0);//,ALTO,PROFUNDO
				glRotatef(-60, 1, 0, 0);
				glScalef(1.5, 2.0, 48);//ancho,profundo,alto
				//glRotatef(30, 1, 0, 0);
				glDisable(GL_LIGHTING);
				fig5.prisma2(madera.GLindex, madera.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix();//PATOTA3
				glTranslatef(-8, 18.0, -40.0);//,ALTO,PROFUNDO
				glRotatef(-60, 1, 0, 0);
				glScalef(1.5, 2.0, 48);//ancho,profundo,alto
				//glRotatef(30, 1, 0, 0);
				glDisable(GL_LIGHTING);
				fig5.prisma2(madera.GLindex, madera.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();


				glPopMatrix();
				glPopMatrix();
			
				if (rot >= 7)
				{
					g_fanimacion = false;
					g_fanimacion2 = true;
				}



				if (rot<=-7)

				{
					g_fanimacion2 = false;

					g_fanimacion = true;
				}



//glTranslatef(0, volKit, 0);//(frente , altura, traslado en 

				//glRotatef(movKit, 1, 0, 0);//(frente , altura, traslado en x )
				glRotatef(rot, 1, 0, 0);//(frente , altura, traslado en x )
				glRotatef(rot2, 1, 0, 0);

				



						

			

			

			glColor3f(1.0,1.0,1.0);

		glPopMatrix(); 

	glPopMatrix();

	glutSwapBuffers ( );

}

void animacion()
{
	
		fig3.text_izq-= 0.001;
		fig3.text_der-= 0.001;
		if(fig3.text_izq<-1)
			fig3.text_izq=0;
		if(fig3.text_der<0)
			fig3.text_der=1;


		if (g_fanimacion)
		{
			

			if (rot < 7)
				rot2 -= 0.01;
				rot += 0.01;

			

		}

	

		if (g_fanimacion2)
		{

			//movKit -= 0.2;
			if (rot > -7)
            rot2 -= 0.01;
			rot -= 0.01;

		}
	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;
		case 'r':
			if (-90>= rot2);
			angBrazo += 0.5f;
			printf("%f", angBrazo);
			break;
		case 'R':
			if (90<= rot2);
			angBrazo -= 0.5f;
			printf("%f",angBrazo);
            break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
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
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{

  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );


  glutMainLoop        ( );          // 

  return 0;
}
