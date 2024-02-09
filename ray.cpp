
#include <iostream>
#include <math.h>
#include "objects.h"
using namespace std;

class Object {
	public:
		virtual float hit(Ray r) = 0;
		virtual Vec3 compute_normal(Vec3 hit_point) = 0;
};

class Sphere : public Object {
	public:
		Sphere(Vec3 center, float r) {
			this->center = center;
			this->radius = r;
		}	

		float hit(Ray r) override {
			Vec3 dir_to_center = r.origin - this->center;
			float a = r.dir * r.dir;
			float b = 2 * (r.dir * dir_to_center);
			float c = (dir_to_center*dir_to_center) - pow(this->radius, 2);
			float disc = b*b - (4 * a * c); 
			if(disc < 0) return -1.0;
			float t = (-b - sqrt(disc)) / (2*a);
			return t;
		}

		Vec3 compute_normal(Vec3 hit_point) override {
			return (hit_point - this->center).normalise();
		}
		
		// variables to describe sphere
		Vec3 center;
		float radius;


};


int main() {
	
	float aspect_ratio = 16.0/9.0;
	int image_width = 400;
	int image_height = static_cast<int>(image_width / aspect_ratio);
	
	float viewport_height = 2.0;
	float viewport_width = viewport_height * (static_cast<float>(image_width)/image_height);
	
	// camera with 1.0 focal length
	Camera c(1.0);
	Viewport viewp(viewport_height, viewport_width, image_height, image_width);
	
	render_image(c, viewp, image_width, image_height);

	return 0;	

}
