varying vec3 position;
varying vec3 normal;

void main(void)
{
  gl_Position		= gl_ModelViewProjectionMatrix * gl_Vertex;
  gl_FrontColor		= gl_Color;
  gl_TexCoord[0]	= gl_MultiTexCoord0;
  normal		= normalize(gl_NormalMatrix * gl_Normal);
  position		= vec3(gl_ModelViewMatrix * gl_Vertex);
}
