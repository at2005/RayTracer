
#include "render.h"

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
