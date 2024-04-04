#version 150

in  vec2 vPosition;
/*in  vec3 vColor; */
out vec4 color;
uniform float time;      /* in milliseconds */


void
main()
{
    float angle = 0.001*time;
    float squaredAngle = angle * angle;
    gl_Position = vec4(vPosition.x*cos(squaredAngle) - vPosition.y*sin(squaredAngle),
    vPosition.x*sin(squaredAngle) + vPosition.y*cos(squaredAngle),
    0.0,
    1.0);
    color = vec4( 1.0, 0.0, 0.0, 1.0 );
}
