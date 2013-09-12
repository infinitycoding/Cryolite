uniform sampler2D Texture0;
int ActiveLights = 2;

varying vec3 position;
varying vec3 normal;

void main(void)
{
  vec3 lightDir;
  float  attenFactor;
  vec3 eyeDir 			= normalize(-position); // camera is at (0,0,0) in ModelView space
  vec4 lightAmbientDiffuse 	= vec4(0.0,0.0,0.0,0.0);
  vec4 lightSpecular 		= vec4(0.0,0.0,0.0,0.0);

  // iterate all lights
  for (int i=0; i<ActiveLights; ++i)
  {
	// attenuation and light direction
	if (gl_LightSource[i].position.w != 0.0)
	{
		// positional light source
		float dist	= distance(gl_LightSource[i].position.xyz, position);
		attenFactor	= 1.0/(	gl_LightSource[i].constantAttenuation +
					gl_LightSource[i].linearAttenuation * dist +
					gl_LightSource[i].quadraticAttenuation * dist * dist );
		lightDir	= normalize(gl_LightSource[i].position.xyz - position);
	}
	else
	{
		// directional light source
		attenFactor	= 1.0;
		lightDir	= gl_LightSource[i].position.xyz;
	}
	// ambient + diffuse
	lightAmbientDiffuse 	+= gl_FrontLightProduct[i].ambient*attenFactor;
	lightAmbientDiffuse 	+= gl_FrontLightProduct[i].diffuse * max(dot(normalize(normal), lightDir), 0.0) * attenFactor;
	// specular
	vec3 r 		= normalize(reflect(-lightDir, normal));
	lightSpecular 	+= gl_FrontLightProduct[i].specular *
			      pow(max(dot(r, eyeDir), 0.0), gl_FrontMaterial.shininess) *
			      attenFactor;
  }
  // compute final color
  vec4 texColor = gl_Color * texture2D(Texture0, gl_TexCoord[0].xy);
  gl_FragColor 	= texColor * (gl_FrontLightModelProduct.sceneColor + lightAmbientDiffuse) + lightSpecular;

  float fog	= (gl_Fog.end - gl_FogFragCoord) * gl_Fog.scale;	// Intensität berechnen
  fog		= clamp(fog, 0.0, 1.0);  				// Beschneiden
  gl_FragColor 	= mix(gl_Fog.color, gl_FragColor, fog);  		// Nebelfarbe einmischen
}
