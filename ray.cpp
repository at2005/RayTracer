
#include <iostream>
#include <math.h>
#include "render.h"
using namespace std;

#define WHITE Vec3(1.0, 1.0, 1.0)
#define GRAY Vec3(0.3, 0.3, 0.3)

int main() {
	
	float aspect_ratio = 16.0/9.0;
	int image_width = 400;
	int image_height = static_cast<int>(image_width / aspect_ratio);
	
	float viewport_height = 2.0;
	float viewport_width = viewport_height * (static_cast<float>(image_width)/image_height);
	
	// camera with 1.0 focal length
	Camera c(1.0);
	Viewport viewp(viewport_height, viewport_width, image_height, image_width);
	
	Vec3 col(0.4, 1.0, 0.5);

	shared_ptr<Lambert> ground_shader = make_shared<Lambert>(GRAY);
	shared_ptr<Lambert> diffuse_shader = make_shared<Lambert>(WHITE); 
	shared_ptr<Metal> metal_shader = make_shared<Metal>(col);
	shared_ptr<Metal> metal_shader2 = make_shared<Metal>(Vec3(1,0.2, 0.2));

	shared_ptr<Sphere> sph = make_shared<Sphere>(Vec3(0,0,-1), 0.5, metal_shader);
	shared_ptr<Sphere> sph2 = make_shared<Sphere>(Vec3(1,0,-1), 0.2, metal_shader2);
   	shared_ptr<Sphere> ground = make_shared<Sphere>(Vec3(0,-100.5,-1), 100, ground_shader);
		
	World world;
	world.add_object(sph);
	world.add_object(sph2);
	world.add_object(ground);

	render_image(world, c, viewp, image_width, image_height);

	return 0;	

}
