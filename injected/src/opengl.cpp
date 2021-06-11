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