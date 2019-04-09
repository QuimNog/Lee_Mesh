#include "application.h"
#include "utils.h"
#include "image.h"
#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "material.h"
#include "light.h"

Camera* camera = NULL;
Mesh* mesh = NULL;
Matrix44 model_matrix;


Shader* shader = NULL;
Shader* shader_gouraud = NULL;

Shader* shader_phong = NULL;
Shader* shader_normals = NULL;
Shader* tex = NULL;
Shader* shader_disco = NULL;



Texture* texture = NULL;
Texture* texture_normals = NULL;
Light* light = NULL;
Light* light_green = NULL;
Light* light_red = NULL;
Light* light_blue = NULL;
Light* light_white = NULL;

Material* material = NULL;

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;
	
	
	//here we create a global camera and set a position and projection properties
	camera = new Camera();
	camera->lookAt(Vector3(0,20,20),Vector3(0,10,0),Vector3(0,1,0));
	camera->setPerspective(60,window_width / window_height,0.1,10000);

	//then we load a mesh
	mesh = new Mesh();
	mesh->loadOBJ("data/lee.obj");

	//load the texture
	texture = new Texture();
	if(!texture->load("data/lee_color_specular.tga"))
	{
		std::cout << "Texture not found" << std::endl;
		exit(1);
	}

	texture_normals = new Texture();
	if (!texture_normals->load("data/lee_normal.tga"))
	{
		std::cout << "Texture not found" << std::endl;
		exit(1);
	}
	

	//we load a shader
	shader = new Shader();
	shader->load("data/texture.vs", "data/texture.ps");

	tex = new Shader();
	tex->load("data/texture.vs", "data/texture.ps");

	shader_gouraud = new Shader();
	shader_gouraud->load("data/simple_gouraud.vs", "data/simple_gouraud.ps");

	shader_phong = new Shader();
	shader_phong->load("data/simple_phong.vs", "data/simple_phong.ps");

	shader_normals = new Shader();
	shader_normals->load("data/simple.vs", "data/simple.ps");

	shader_disco = new Shader(); 
	shader_disco->load("data/disco.vs", "data/disco.ps"); 

	light = new Light();
	light_blue = new Light();
	light_blue->setLightBlue();
	light_green = new Light();
	light_green->setLightGreen();
	light_red = new Light();
	light_red->setLightRed();
	light_white = new Light();
	light_white->setLightWhite(); 

	material = new Material();
}


int chosing_shader = 3; 
//render one frame
void Application::render(void)
{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable( GL_DEPTH_TEST );

	//Get the viewprojection
	Matrix44 viewprojection = camera->getViewProjectionMatrix();
	Matrix44 mvp = model_matrix * viewprojection;


	//choose shader

	if (chosing_shader == 0) {

		shader = shader_normals;
	}
	else if (chosing_shader == 1) {

		shader = shader_gouraud;
	}
	else if (chosing_shader == 2) {

		shader = shader_phong;
	}
	else if (chosing_shader == 3) {

		shader = tex;
	}
	else if (chosing_shader == 4) {
		shader = shader_disco; 
	}
	
	
	if (chosing_shader == 0 || chosing_shader == 1 || chosing_shader == 2) {

		//enable the shader
		shader->enable();

		shader->setMatrix44("mvp", mvp); //upload info to the shader
		shader->setMatrix44("model", model_matrix);

		shader->setVector3("eye", camera->eye);

		//light info
		shader->setVector3("lp", light->position);
		shader->setVector3("id", light->diffuse_color);
		shader->setVector3("is", light->specular_color);
		shader->setVector3("ia", light->ambient_color);

		//material info
		shader->setVector3("kd", material->diffuse);
		shader->setVector3("ks", material->specular);
		shader->setFloat("alpha", material->shininess);
		shader->setVector3("ka", material->ambient);
	}
	else if (chosing_shader == 3) {

		//enable the shader
		shader->enable();

		shader->setMatrix44("mvp", mvp); //upload info to the shader
		shader->setMatrix44("model", model_matrix);

		shader->setVector3("eye", camera->eye);

		//light info
		shader->setVector3("lp", light->position);
		shader->setVector3("id", light->diffuse_color);
		shader->setVector3("is", light->specular_color);
		shader->setVector3("ia", light->ambient_color);

		//material info
		shader->setVector3("kd", material->diffuse);
		shader->setVector3("ks", material->specular);
		shader->setFloat("alpha", material->shininess);
		shader->setVector3("ka", material->ambient);
	
		shader->setTexture("color_texture", texture);
		shader->setTexture("normal_texture", texture_normals);

	}
	else if(chosing_shader == 4){

		//enable the shader
		shader->enable();

		shader->setMatrix44("mvp", mvp); //upload info to the shader
		shader->setMatrix44("model", model_matrix);

		shader->setVector3("eye", camera->eye);

		//light info
		shader->setVector3("lp", light->position);
		shader->setVector3("id", light->diffuse_color);
		shader->setVector3("is", light->specular_color);
		shader->setVector3("ia", light->ambient_color);

		shader->setVector3("lp_g", light_green->position);
		shader->setVector3("id_g", light_green->diffuse_color);
		shader->setVector3("is_g", light_green->specular_color);
		shader->setVector3("ia_g", light_green->ambient_color);

		shader->setVector3("lp_r", light_red->position);
		shader->setVector3("id_r", light_red->diffuse_color);
		shader->setVector3("is_r", light_red->specular_color);
		shader->setVector3("ia_r", light_red->ambient_color);

		shader->setFloat("time", sin(1 * time));
		shader->setFloat("time_r", sin(4*time));
		


		//material info
		shader->setVector3("kd", material->diffuse);
		shader->setVector3("ks", material->specular);
		shader->setFloat("alpha", material->shininess);
		shader->setVector3("ka", material->ambient);

		shader->setTexture("color_texture", texture);
		shader->setTexture("normal_texture", texture_normals);
	}
	//render the data
	mesh->render(GL_TRIANGLES);

	//disable shader
	shader->disable();

	//swap between front buffer and back buffer

	SDL_GL_SwapWindow(this->window);
}

//called after render
void Application::update(double seconds_elapsed)
{
	//rotation
	if (keystate[SDL_SCANCODE_SPACE])
	{
		model_matrix.rotateLocal(seconds_elapsed,Vector3(0,1,0));
	}

	if (keystate[SDL_SCANCODE_D])
	{
		camera->eye.x += seconds_elapsed * 15;
	}
	if (keystate[SDL_SCANCODE_A])
	{
		camera->eye.x -= seconds_elapsed * 15;
	}
	if (keystate[SDL_SCANCODE_W])
	{
		camera->eye.y += seconds_elapsed * 15;
	}
	if (keystate[SDL_SCANCODE_S])
	{
		camera->eye.y -= seconds_elapsed * 15;
	}
	//shaders
	if (keystate[SDL_SCANCODE_0])
	{
		chosing_shader = 0;
	}
	if (keystate[SDL_SCANCODE_1])
	{
		chosing_shader = 1;
		light->setLightOriginal();
	}
	if (keystate[SDL_SCANCODE_2])
	{
		chosing_shader = 2;
		light->setLightOriginal();
	}
	if (keystate[SDL_SCANCODE_3])
	{
		chosing_shader = 3;
		light->setLightWhite();

	}if (keystate[SDL_SCANCODE_4])
	{
		chosing_shader = 4;
		light->setLightWhite();
	}
	//fov
	if (keystate[SDL_SCANCODE_M]) {
		camera->fov -= seconds_elapsed * 10; 
	}
	if (keystate[SDL_SCANCODE_N]) {
		camera->fov += seconds_elapsed * 10;
	}
	//light rotations
	if (keystate[SDL_SCANCODE_UP])
	{
		light->position.z += seconds_elapsed * 5;
	}
	if (keystate[SDL_SCANCODE_DOWN])
	{
		light->position.z -= seconds_elapsed * 5;
	}
	if (keystate[SDL_SCANCODE_LEFT])
	{
		light->position.x -= seconds_elapsed * 5;
	}
	if (keystate[SDL_SCANCODE_RIGHT])
	{
		light->position.x += seconds_elapsed * 5;
	}

	//light colors
	if (keystate[SDL_SCANCODE_Z])
	{
		light->setLightRed();
	}
	if (keystate[SDL_SCANCODE_X])

	{
		light->setLightGreen();
	}
	if (keystate[SDL_SCANCODE_C])
	{
		light->setLightWhite();
	}
	if (keystate[SDL_SCANCODE_V])
	{
		light->setLightOriginal();
	}

	//materials
	if (keystate[SDL_SCANCODE_P])
	{
		material->setMaterialGold();
	}
	if (keystate[SDL_SCANCODE_O])
	{
		material->setMaterialMetal();
	}
	if (keystate[SDL_SCANCODE_I])
	{
		material->setMaterialPlastic();
	}
	if (keystate[SDL_SCANCODE_U])
	{
		material->setMaterialSkin();
	}
}

//keyboard press event 
void Application::onKeyPressed( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: exit(0); break; //ESC key, kill the app
	}
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{

	}
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{

	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
