#version 130
/* FAIL - attribute cannot have array type in GLSL 1.30 */
attribute vec4 i[10];

void main()
{
  gl_Position = vec4(1.0);
}
