#include "material.h"



Material::Material()
{
	ambient.set(1, 1, 1); //reflected ambient light
	diffuse.set(1, 1, 1); //reflected diffuse light
	specular.set(1, 1, 1); //reflected specular light

	shininess = 50.0; //glosiness coefficient (plasticity)
}

void Material::setMaterialGold() {
	ambient.set(0.81, 0.70, 0.23);
	diffuse.set(0.81, 0.70, 0.23);
	specular.set(0.99, 0.90, 0.45);
	shininess = 4.0; //glosiness coefficient (plasticity)

}

void Material::setMaterialMetal() {
	ambient.set(0.35, 0.36, 0.35);
	diffuse.set(0.80, 0.80, 0.80);
	specular.set(0.95, 0.96, 0.95);
	shininess = 5.0; //glosiness coefficient (plasticity)

}

void Material::setMaterialPlastic() {
	ambient.set(0.54, 0.72, 0.82);
	diffuse.set(0.2, 0.40, 0.82);
	specular.set(0.70, 0.85, 0.95
	);
	shininess = 150.0; //glosiness coefficient (plasticity)

}
void Material::setMaterialSkin() {
	ambient.set(1, 0.67, 0.37); //reflected ambient light
	diffuse.set(0.6, 0.60, 0.50); //reflected diffuse light
	specular.set(0.2, 0.2, 0.2); //reflected specular light


	shininess = 1.0; //glosiness coefficient (plasticity)

}





