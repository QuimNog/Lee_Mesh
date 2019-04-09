
#include "light.h"



Light::Light()
{
	position.set(0, 20, 0);
	diffuse_color.set(0.6,0.6,0.6);
	specular_color.set(0.6, 0.6, 0.6);
	ambient_color.set(0.1, 0.1, 0.1);
	
}





void Light::uploadToShader(const char* shader) {
	

}
void Light::setLightRed() {
	position.set(-50, 100, +20);
	diffuse_color.set(0.6, 0, 0);
	specular_color.set(0.6, 0, 0);
	ambient_color.set(0.1, 0, 0);
}
void Light::setLightGreen() {
	position.set(50, 20, -20);
	diffuse_color.set(0, 0.6, 0);
	specular_color.set(0, 0.6, 0);
	ambient_color.set(0, 0.1, 0);
}
void Light::setLightWhite() {
	diffuse_color.set(0.6, 0.6, 0.6);
	specular_color.set(0.3, 0.3, 0.3);
	ambient_color.set(0.1, 0.1, 0.1);
}

void Light::setLightOriginal()
{	
	diffuse_color.set(0.6, 0.6, 0.6);
	specular_color.set(0.6, 0.6, 0.6);
	ambient_color.set(0.1, 0.1, 0.1);
}
void Light::setLightBlue()
{
	diffuse_color.set(0, 0, 0.6);
	specular_color.set(0, 0, 0.6);
	ambient_color.set(0, 0, 0.1);
}