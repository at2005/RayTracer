
#ifndef MATERIALS_H
#define MATERIALS_H

#include "vec.h"
#include "utils.h"


float rand_unit() {
	return rand() / (RAND_MAX + 1.);
}

float rand_bounds(float min, float max) {
	return min + rand_unit() * (max - min);

}

Vec3 random_unit_vec() {
	return Vec3(rand_bounds(-1., 1.), rand_bounds(-1., 1.), rand_bounds(-1., 1.)).normalise();
}


class Material {
	public:
		virtual Ray reflect(Vec3 hit_point, Vec3 normal, Ray incident) = 0;
		Vec3 attenuate_color;
};

class Lambert : public Material {
	public:
		Lambert(Vec3 color) {
			this->attenuate_color = color;
		} 
		Ray reflect(Vec3 hit_point, Vec3 normal, Ray incident) override {
			Vec3 unit_vec = random_unit_vec();
			if(unit_vec * normal < 0.) {
				unit_vec = -1 * unit_vec;	
			} 
			
			// from intersection point to random direction
			return Ray(hit_point, normal + unit_vec);
			
		}

};

class Metal: public Material {
	public:
		Metal(Vec3 color) {
			this->attenuate_color = color;
		}
		Ray reflect(Vec3 hit_point, Vec3 normal, Ray incident) override {
			Vec3 reflect_dir = incident.dir - ((2*(normal * incident.dir) * normal));
			return Ray(hit_point, reflect_dir);
		}
};

#endif
