//global variables from the CPU
uniform mat4 model;
uniform mat4 mvp;

//vars to pass to the pixel shader
varying vec3 v_color;

//here create uniforms for all the data we need here

uniform vec3 kd; 
uniform vec3 id;
 
uniform vec3 is; 
uniform vec3 ks;
uniform float alpha;

uniform vec3 ka;
uniform vec3 ia; 
 
uniform vec3 lp;
uniform vec3 eye; 


void main()
{	
	vec3 pos = (model * vec4( gl_Vertex.xyz, 1.0)).xyz;
	vec3 normal = (model * vec4( gl_Normal.xyz, 0.0)).xyz;
	vec3 light_pos = lp; 
	
	vec3 L = normalize((pos-light_pos));
	L = (model * vec4( L.xyz, 0.0)).xyz;
	
	float LdotN = dot(L, normal);
	
	
	vec3 R = reflect(L, normal);
	
	vec3 V = normalize((pos-eye));
	
	float RdotV = dot(R,V);
	
	if(RdotV<0.0){
	RdotV=0.0; 
	}

	RdotV = pow(RdotV, alpha);
	
	vec3 ambient = ka*ia; 
	vec3 diffuse = kd*LdotN*id;
	vec3 specular = ks*RdotV*is; 	


   	v_color = ambient + diffuse+specular;  

	//pass it to the pixel shader as color (for debug)
	//v_color = normal;
	 

	//project the vertex by the model view projection 
	gl_Position = mvp * gl_Vertex; //output of the vertex shader
}