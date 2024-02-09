#include "vec.h"

class Camera {

	public:
		Vec3 origin;
		float focal_length;
	
		Camera(Vec3 og, float flength) {
			origin = og;
			focal_length = flength;
		}
			
		// default camera
		Camera(float flength) {
			origin = Vec3(0,0,0);
			focal_length = flength;
		}

};

class Ray {
	
	public:
		Vec3 origin;
		Vec3 dir;
		Ray(Vec3 og, Vec3 direction) {
			origin = og;
			dir = direction;
		}
		

		Vec3 pos(float t) {
			return origin + dir * t;
		}
};

class Viewport {
	public:
		float height;
		float  width;
		Vec3 horizontal;
		Vec3 vertical;
		
		Viewport(float h, float w, int image_h, int image_w) {
			height = h;
			width = w;
			horizontal = Vec3(width, 0, 0);
			vertical = Vec3(0, -height, 0);
			pixel_delta_h = horizontal / image_w;
			pixel_delta_v = vertical / image_h;
		}
		
		Vec3 fetch_origin(Camera c) {
			Vec3 viewport_upper_left = c.origin - Vec3(0,0,c.focal_length) - (horizontal/2) - (vertical/2);
			return viewport_upper_left + 0.5*(pixel_delta_h + pixel_delta_v);
		}
		
		Vec3 compute_pixel_pos(Camera c, int i, int j) {
			return fetch_origin(c) + (pixel_delta_v * j) + (pixel_delta_h * i);
		}

		private:
			Vec3 pixel_delta_h;
			Vec3 pixel_delta_v;
	
};

