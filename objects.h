#include <vector>
#include "utils.h"
#include <memory>
using std::shared_ptr;
using std::make_shared;

class Object {
	public:
		virtual float hit(Ray r, Interval t_range) = 0;
		virtual Vec3 compute_normal(Vec3 hit_point) = 0;
};

class Sphere : public Object {
	public:
		Sphere(Vec3 center, float r) {
			this->center = center;
			this->radius = r;
		}	

		float hit(Ray r, Interval t_range) override {
			Vec3 dir_to_center = r.origin - this->center;
			float a = r.dir * r.dir;
			float b = 2 * (r.dir * dir_to_center);
			float c = (dir_to_center*dir_to_center) - pow(this->radius, 2);
			float disc = b*b - (4 * a * c); 
			if(disc < 0) return -1.0;
			float t = (-b - sqrt(disc)) / (2*a);
			if(!t_range.surrounds(t)) {
				t = (-b + sqrt(disc)) / (2*a);
				if(!t_range.surrounds(t)) return -1.0;
			}

			return t;
		}

		Vec3 compute_normal(Vec3 hit_point) override {
			return (hit_point - this->center).normalise();
		}
		
		// variables to describe sphere
		Vec3 center;
		float radius;
};

/*
class Context {
	public:
		Context();
		float min_t;

};
*/

class World {
	public:
		World() {
		}
		
		float hit(Ray r) {
			// t_max here represents how "far" our ray can go...
			// obviously this value will decrease as more objects are hit
			float t_max = infinity;
			for(int i = 0; i < world_list.size(); i++) {
				auto obj = world_list[i];								
				float test_t = obj->hit(r, Interval(0, t_max)); 
				if(test_t != -1.0) {
					t_max  = test_t;
				}
			}			

			return t_max == infinity ? -1.0 : t_max;
		}
		
		void add_object(shared_ptr<Object> obj) {
			world_list.push_back(obj);
		}
		
		shared_ptr<Object> operator[](unsigned int index) {
			return world_list[index];
		} 

		private:
			vector<shared_ptr<Object>> world_list;


};

