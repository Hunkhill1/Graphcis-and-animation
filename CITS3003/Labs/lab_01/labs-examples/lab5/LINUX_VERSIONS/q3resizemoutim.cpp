/* sierpinski gasket with vertex arrays */

#include "Angel.h"
GLuint transformID;
GLint windowHeight=512, windowWidth=512;
using namespace std;

int numDisplayCalls = 0;
char lab[] = "Lab5";
char programName[] = "q3callbacks";

// Perspective projection
mat4 projection = Frustum(-0.2, 0.2, -0.2, 0.2, 0.2, 2.0);

// Move the scene backwards relative to the camera
mat4 view = Translate(0.0, 0.0, -1.5);

const int NumTriangles = 12;
const int NumVertices  = 8;
const int NumElements  = 3 * NumTriangles;

// Each vertex now appears only once, so we have only 8 rather than 36
vec3 points[NumVertices] = {
   vec3( -0.5, -0.5, -0.5 ), vec3( -0.5, -0.5,  0.5 ),
   vec3( -0.5,  0.5, -0.5 ), vec3( -0.5,  0.5,  0.5 ),

   vec3(  0.5, -0.5, -0.5 ), vec3(  0.5, -0.5,  0.5 ),
   vec3(  0.5,  0.5, -0.5 ), vec3(  0.5,  0.5,  0.5 )
};

// The following builds triangles from the 8 vertices above,
// using numbers 0-7 to refer to the element positions in the array
GLuint elements[NumElements] = {
    1, 5, 3,
    7, 3, 5,

    0, 4, 2,
    6, 2, 4,

    4, 6, 5,
    7, 5, 6,

    0, 2, 1,
    3, 1, 2,

    2, 3, 6,
    7, 6, 3,

    0, 1, 4,
    5, 4, 1
};


// We only need to give 8 colors, one for each vertex.
vec3 colors[NumVertices] = {
  vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0),
  vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 1.0),

  vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 1.0),
  vec3(1.0, 1.0, 0.0), vec3(1.0, 1.0, 1.0),
};







//----------------------------------------------------------------------------

void
init( void )
{
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // First, we create an empty buffer of the size we need by passing
    //   a NULL pointer for the data values
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
		  NULL, GL_STATIC_DRAW );

    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

        // ADDED: load the element index data
    GLuint elementBufferId;
    glGenBuffers(1, &elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);



    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader24sq3d.glsl", "fshader24.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader    
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    //glEnable( GL_DEPTH_TEST );

    transformID = glGetUniformLocation(program, "multipliers");
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------
void drawCube(mat4 model) {
    glUniformMatrix4fv( transformID, 1, GL_TRUE, model );
    glDrawElements(GL_TRIANGLES, NumElements, GL_UNSIGNED_INT, NULL);}



void
display( void )
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  ); 
    float angle = (0.001 * glutGet(GLUT_ELAPSED_TIME))*60;
    //ROt z axis
    mat3 mTransform3z = mat3( vec3(cos(angle), -sin(angle), 0.0),  // Rotation around x-axis
                             vec3(sin(angle), cos(angle), 0.0),   // Rotation around y-axis
                             vec3(0.0, 0.0, 1.0) );    

    // glUniformMatrix3fv(transformID, 1, GL_TRUE, mTransform3z);
    // glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    // ROT X axis
    mat3 mTransform1x = mat3( vec3(1.0, 0.0, 0.0),       // No rotation around x-axis
                             vec3(0.0, cos(angle), -sin(angle)),  // Rotation around y-axis
                             vec3(0.0, sin(angle), cos(angle)) );

    // glUniformMatrix3fv(transformID, 1, GL_TRUE, mTransform1x);
    // glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    mat3 mTransformy = mat3( vec3(cos(angle),  0.0, sin(angle)),
                                     vec3(0.0,         1.0,        0.0),
                                     vec3(-sin(angle), 0.0, cos(angle)) );

    // glUniformMatrix3fv(transformID, 1, GL_TRUE, mTransformy; 
    //     glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    mat3 shrinkX =
        mat3( vec3(0.25, 0.0, 0.0),
              vec3(0.0,  1.0, 0.0),
              vec3(0.0,  0.0, 1.0)  );


    
    
    
    // Original cubes
    drawCube(projection * view *Translate(-0.5, -0.5, 0) * Scale(0.3) * RotateX(angle) * RotateY(angle));
    drawCube(projection * view *Translate(-0.5, 0.5, 0) * Scale(0.3) * RotateX(angle) * RotateY(angle));
    drawCube(projection * view *Translate(0.5, -0.5, 0) * Scale(0.3) * RotateX(angle) * RotateY(angle));
    drawCube(projection * view *Translate(0.5, 0.5, 0) * Scale(0.3) * RotateX(angle) * RotateY(angle));

    // Cubes with Translate(0.6, 0.6, 0.6) inserted at different locations in the transformation
    drawCube(projection * view *Translate(0.5, 0.5, 0) * Scale(0.3) * RotateX(angle) * RotateY(angle) * Translate(0.6, 0.6, 0.6));
    drawCube(projection * view *Translate(-0.5, 0.5, 0) * Scale(0.3) * RotateX(angle) * Translate(0.6, 0.6, 0.6) * RotateY(angle));
    drawCube(projection * view *Translate(0.5, -0.5, 0) * Scale(0.3) * Translate(0.6, 0.6, 0.6) * RotateX(angle) * RotateY(angle));
    
    
    
        
        
    numDisplayCalls++;
    glutSwapBuffers();
}

//----------------------------------------------------------------------------
void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, windowWidth, windowHeight);

    projection = Frustum(-0.2*(float)width/(float)height, 0.2*(float)width/(float)height, -0.2, 0.2, 0.2, 2.0);
}

void mouse(int xPixel, int yPixel )
{
    GLfloat x = (GLfloat)xPixel/(GLfloat)windowWidth - 0.5;
    GLfloat y = 0.5 - (GLfloat)yPixel/(GLfloat)windowHeight;

    view = Translate(x, y, -1.5);
}

void timer(int unused) {

    char title[256];
    sprintf(title, "%s %s: %d Frames Per Second @ %d x %d",
            lab, programName, numDisplayCalls, windowWidth, windowHeight );
 
    glutSetWindowTitle(title);
    
    numDisplayCalls = 0;
    glutTimerFunc(1000, timer, 1);
}


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
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Simple GLSL example" );
    glutIdleFunc( idle );

    glewInit();

    init();

    glEnable( GL_DEPTH_TEST ); 

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutMotionFunc(mouse);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, timer, 1);

    glutMainLoop();
    return 0;
}
