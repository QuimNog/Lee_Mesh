//global variables from the CPU
uniform mat4 model;
uniform mat4 mvp;

//vars to pass to the pixel shader
varying vec3 v_color;

//here create uniforms for all the data we need here

void main()
{	
	vec3 pos = (model * vec4( gl_Vertex.xyz, 1.0)).xyz;
	vec3 normal = (model * vec4( gl_Normal.xyz, 0.0)).xyz;

	//pass it to the pixel shader as color (for debug)
	v_color = normal;

	//project the vertex by the model view projection 
	gl_Position = mvp * gl_Vertex; //output of the vertex shader
}