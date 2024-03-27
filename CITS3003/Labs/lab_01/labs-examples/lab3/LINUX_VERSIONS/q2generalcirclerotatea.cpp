// Two-Dimensional Sierpinski Gasket       
// Generated using randomly selected vertices and bisection

#include "Angel.h"

GLuint sinAngle, cosAngle;
//GLint timeParam; //added this in

const int NumPoints = 400000;

vec2 points[NumPoints];
vec3 colors[NumPoints];

//----------------------------------------------------------------------------
//had to change vec3 to vec2 from previous lab
void
init( void )
{
    vec2 vertices[3] = { 
        vec2(-1.0, -1.0), vec2(0.0, 1.0), vec2(1.0, -1.0)
    };
    // The colours of the three vertices are cyan, magenta, and yellow.
    vec3 vertex_colors[3] = {
        vec3(0.0, 1.0, 1.0), vec3(1.0, 0.0, 1.0), vec3 (1.0, 1.0, 0.0)
    };

    // Select an arbitrary initial point inside of the triangle
    points[0] = vec2(0.25, 0.50);
    colors[0] = vec3(0.5, 0.5, 0.5);

    

    // // Specifiy the vertices of a triangle
    // vec2 vertices[3] = {
    //     vec2( -1.0, -1.0 ), vec2( 0.0, 1.0 ), vec2( 1.0, -1.0 )
    // };

    // Select an arbitrary initial point inside of the triangle
    //points[0] = vec2( 0.25, 0.50 );

    int i = 1;
    while (i < NumPoints) {
        int j = rand() % 3;   // pick a vertex at random

        points[i] = (points[i - 1] + vertices[j]) / 2.0;
        colors[i] = colors[i-1]*0.8 + vertex_colors[j]*0.2;
        if (length(points[i]) <= 1) {
            i++;
        }

        
    }

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
                  NULL, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vrotate2dtriangle.glsl", "fshader24.glsl" );
    glUseProgram( program );
    // Initialize the vertex position attribute from the vertex shader
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)));

    sinAngle = glGetUniformLocation(program, "sinAngle");
    cosAngle = glGetUniformLocation(program, "cosAngle");
    

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background

        //timeParam = glGetUniformLocation(program, "time"); //added this in

    
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    //glUniform1f( timeParam, glutGet(GLUT_ELAPSED_TIME) );
    glUniform1f(sinAngle, 2.5*sin(0.001*glutGet(GLUT_ELAPSED_TIME)) );
    glUniform1f(cosAngle, 0.5*cos(0.001*glutGet(GLUT_ELAPSED_TIME)) );

    glDrawArrays( GL_POINTS, 0, NumPoints );    // draw the points
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

void idle(void){ //added this in as well for lab 3
    glutPostRedisplay();

}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );

    // If you are using freeglut, the next two lines will check if 
    // the code is truly 3.2. Otherwise, comment them out
    
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Sierpinski Gasket" );
    glutIdleFunc(idle); // added this in as well for lab 3
    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
