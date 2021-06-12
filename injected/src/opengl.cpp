#include "../include/epycheat.h"

void SetupOrtho(void)
{
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glPushMatrix( );
	GLint viewport [ 4 ];
	glGetIntegerv( GL_VIEWPORT, viewport );
	glViewport( 0, 0, viewport [ 2 ], viewport [ 3 ] );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( 0, viewport [ 2 ], viewport [ 3 ], 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glDisable( GL_DEPTH_TEST );
}

void RestoreGL(void)
{
	glPopMatrix( );
	glPopAttrib( );
}

GLint* Get_Viewport(void)
{
	GLint *viewport = (GLint*)malloc(sizeof(GLint) * 16);

	jclass cactiverenderinfo = data.env->FindClass("net/minecraft/client/renderer/ActiveRenderInfo");

	jfieldID jfi = data.env->GetStaticFieldID(cactiverenderinfo, "viewport", "Ljava/nio/IntBuffer;");
	jobject oviewport = data.env->GetStaticObjectField(cactiverenderinfo, jfi);
	jclass cintbuffer = data.env->FindClass("java/nio/IntBuffer");
	jmethodID MIDGet = data.env->GetMethodID(cintbuffer, "get", "(I)I");
	for (int i = 0; i < 16; i++) {
		viewport[i] = data.env->CallIntMethod(oviewport, MIDGet, i);
	}
	return viewport;
}

GLfloat* Get_ModelView(void)
{
	GLfloat *modelview = (GLfloat*)malloc(sizeof(GLfloat) * 16);

	jclass CActiveRenderInfo = data.env->FindClass("net/minecraft/client/renderer/ActiveRenderInfo");
	std::cout << CActiveRenderInfo << std::endl;
	jfieldID FIDMODELVIEW = data.env->GetStaticFieldID(CActiveRenderInfo, "modelview", "Ljava/nio/FloatBuffer;");
	std::cout << FIDMODELVIEW << std::endl;
	jobject OMODELVIEW = data.env->GetStaticObjectField(CActiveRenderInfo, FIDMODELVIEW);
	std::cout << OMODELVIEW << std::endl;
	jclass CFloatBuffer = data.env->FindClass("java/nio/FloatBuffer");
	std::cout << CFloatBuffer << std::endl;
	jmethodID MIDget = data.env->GetMethodID(CFloatBuffer, "get", "(I)F");
	std::cout << MIDget << std::endl;
	std::cout << "pre prout" << std::endl;
	for (int i = 0; i < 16; i++) {
		modelview[i] = (float)data.env->CallFloatMethod(OMODELVIEW, MIDget, i);
		std::cout << (float)data.env->CallFloatMethod(OMODELVIEW, MIDget, i) << std::endl;
	}
	std::cout << std::endl;
	//std::cout << "prout" << std::endl;
	return modelview;
}

GLfloat* Get_Projection(void)
{
	GLfloat *projection = (GLfloat*)malloc(sizeof(GLfloat) * 16);

	jclass CActiveRenderInfo = data.env->FindClass("net/minecraft/client/renderer/ActiveRenderInfo");
	std::cout << CActiveRenderInfo << std::endl;
	jfieldID FIDPROJECTION = data.env->GetStaticFieldID(CActiveRenderInfo, "projection", "Ljava/nio/FloatBuffer;");
	std::cout << FIDPROJECTION << std::endl;
	jobject OPROJECTION = data.env->GetStaticObjectField(CActiveRenderInfo, FIDPROJECTION);
	std::cout << OPROJECTION << std::endl;
	jclass CFloatBuffer = data.env->FindClass("java/nio/FloatBuffer");
	std::cout << CFloatBuffer << std::endl;
	jmethodID MIDget = data.env->GetMethodID(CFloatBuffer, "get", "(I)F");
	std::cout << MIDget << std::endl;
	for (int i = 0; i < 16; i++) {
		projection[i] = data.env->CallFloatMethod(OPROJECTION, MIDget, i);
		std::cout << projection[i] << std::endl;
	}
	std::cout << std::endl;
	return projection;
}

void DrawSquare( GLfloat x, GLfloat y, GLfloat sidelength, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha )
{
	glEnable( GL_BLEND );
	glColor4ub( r, g, b, alpha );

	GLfloat halfside = sidelength;

	glBegin( GL_QUADS );
	glVertex2d( x + halfside, y + halfside );
	glVertex2d( x + halfside, y);
	glVertex2d( x, y);
	glVertex2d( x, y + halfside );
	glEnd( );
}

void DrawRect( GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha )
{
	glEnable( GL_BLEND );
	glColor4ub( r, g, b, alpha );

	glBegin( GL_QUADS );
	glVertex2d( x + width, y + height );
	glVertex2d( x + width, y );
	glVertex2d( x, y);
	glVertex2d( x, y + height );
	glEnd( );
}

void DrawLine(GLint x0, GLint y0, GLint z0, GLint x1, GLint y1, GLint z1)
{
	glColor4ub( 0, 0, 0, 255 );
	glLineWidth(20.0F);
	glBegin(GL_LINES);

  	glVertex3i(x0, y0, z0);
  	glVertex3i(x1, y1, z1);
	glEnd();
}