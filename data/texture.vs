//global variables from the CPU
uniform mat4 model;
uniform mat4 mvp;

//vars to pass to the pixel shader
varying vec3 v_color;

varying vec3 position; 
//texture
varying vec2 v_coord;

//normal texture


//here create uniforms for all the data we need here

//texture

varying vec3 normals;




void main()
{	
	
	vec3 pos = (model * vec4( gl_Vertex.xyz, 1.0)).xyz;
	vec3 normal = (model * vec4( gl_Normal.xyz, 0.0)).xyz;

	//get the texture coordinates (per vertex) and pass them to the pixel shader
	v_coord = gl_MultiTexCoord0.xy;


	
	position = pos; 
	 

	//project the vertex by the model view projection 
	gl_Position = mvp * gl_Vertex; //output of the vertex shader
}