
#include <iostream>
#include <math.h>
using namespace std;



class Vec3 {
	public:
		float r;
		float g;
		float b;
	
	Vec3(float red, float green, float blue) {
		r = red;
		g = green;
		b = blue;
	}

	Vec3() {
		r = 0;
		g = 0;
		b = 0;
	}
	
	Vec3 operator+(const Vec3 other_vec) {
		return Vec3(this->r + other_vec.r, this->g + other_vec.g, this->b + other_vec.b);
	}

	Vec3 operator-(const Vec3 other_vec) {
		return Vec3(this->r - other_vec.r, this->g - other_vec.g, this->b - other_vec.b);
	}

	Vec3 operator*(const float scalar) {
		return Vec3(this->r * scalar, this->g * scalar, this->b * scalar);
	}
	
	friend Vec3 operator*(const float scalar, const Vec3 other_vec) {
		return Vec3(other_vec.r * scalar, other_vec.g * scalar, other_vec.b * scalar);
	}

	float operator*(const Vec3 other_vec) {
		return this->r * other_vec.r + this->g * other_vec.g + this->b * other_vec.b; 
	}

	Vec3 operator/(const float scalar) {
		return Vec3(this->r / scalar, this->g / scalar, this->b / scalar);
	}
	
	friend Vec3 operator/(const float scalar, const Vec3 other_vec) {
		return Vec3(other_vec.r / scalar, other_vec.g / scalar, other_vec.b / scalar);
	}
	
	float magnitude() {
		return sqrt(r*r + b*b + g*g);
	}

	Vec3 normalise() {
		float mag = this->magnitude(); 
		return *(this) / mag;
	}

	void print_pixel() {
		cout << static_cast<int>(r*255.999) << " " << static_cast<int>(g*255.999) << " " << static_cast<int>(b*255.999) << "\n";		
	}

	void print_raw() {
		cout << r << " " << g << " " << b << "\n";
	}

};

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

Vec3 lerp(Vec3 start, Vec3 end, float alpha) {
	return (start*(1.0 - alpha)) + (end*alpha);

}

struct Sphere {
	Vec3 center;
	float radius;
};



Vec3 compute_sphere_normal(Sphere sph, Vec3 hit_point) {
	return (hit_point - sph.center).normalise();
}

float hit_sphere(Ray r, Sphere sphere) {
	Vec3 dir_to_center = r.origin - sphere.center;
	float a = r.dir * r.dir;
	float b = 2 * (r.dir * dir_to_center);
	float c = (dir_to_center*dir_to_center) - pow(sphere.radius, 2);
	float disc = b*b - (4 * a * c); 
	if(disc < 0) return -1.0;
	disc = sqrt(disc);
	//a *= 2;
	//b *= -1;
	float t = (-b + disc) / (2*a);
	return t;

//	return t > 0 ? t : (b - disc) / a;
}


Vec3 ray_color(Ray r) {
	Sphere sph;
	sph.radius = 0.5;
	sph.center = Vec3(0,0,-1);
	float t = hit_sphere(r, sph);
	if(t != -1.0) {
		Vec3 hit_point = r.pos(t);
		Vec3 n = compute_sphere_normal(sph, hit_point);
		return 0.5 * (n + Vec3(1.0,1.0,1.0));
//		return Vec3(0,1,0);
	}

	Vec3 ray_normalised_dir = r.dir.normalise();

	return lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), 0.5*(ray_normalised_dir.g + 1));
}

void render_image(Camera c, Viewport viewp, int width, int height) {
	cout << "P3\n" << width << " " << height << "\n255\n";
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			Ray r(c.origin, viewp.compute_pixel_pos(c,i, j) - c.origin);	
			Vec3 result_color = ray_color(r);
			result_color.print_pixel();
		}
	}
}

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
