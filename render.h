#include "objects.h"
#include <stdlib.h>

Vec3 lerp(Vec3 start, Vec3 end, float alpha) {
	return (start*(1.0 - alpha)) + (end*alpha);

}

float rand_unit() {
	return rand() / (RAND_MAX + 1.);
}

float rand_bounds(float min, float max) {
	return min + rand_unit() * (max - min);

}

Vec3 random_unit_vec() {
	return Vec3(rand_bounds(-1., 1.), rand_bounds(-1., 1.), rand_bounds(-1., 1.)).normalise();
}

// returns offset to be added to some pixel
Vec3 sampler(Viewport viewp) {
	float offset_vertical = rand_unit() - 0.5;
	float offset_horizontal = rand_unit() - 0.5;
	return (offset_vertical * viewp.pixel_delta_v) + (offset_horizontal * viewp.pixel_delta_h);	
}

Ray random_ray(Vec3 normal, Vec3 point) {	
	Vec3 unit_vec = random_unit_vec();
	if(unit_vec * normal < 0.) {
		unit_vec = -1 * unit_vec;	
	} 
	
	// from intersection point to random direction
	return Ray(point, normal + unit_vec);
}

Ray reflected_ray(Vec3 normal, Vec3 point, Ray incident) {
	Vec3 reflect_dir = incident.dir - ((2*(normal * incident.dir) * normal));
	return Ray(point, reflect_dir);
}

Vec3 ray_color(Ray r, World world, int depth) {
	Context hit_ctx = world.hit(r); 
	float t = hit_ctx.t_val;  
	if(t != infinity && hit_ctx.object_hit != nullptr && depth > 0) {
		Vec3 hit_point = r.pos(t);
		Vec3 n = hit_ctx.object_hit->compute_normal(hit_point); 
//		return 0.8 * ray_color(reflected_ray(n, hit_point, r), world, depth-1);
		return 0.5 * ray_color(random_ray(n, hit_point), world, depth-1); 
//		return 0.5 * (n + Vec3(1.0,1.0,1.0));

	}

	Vec3 ray_normalised_dir = r.dir.normalise();

//	return lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), 0.5*(ray_normalised_dir.g + 1));
	return lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.235,0.209,0.949), 0.5*(ray_normalised_dir.g + 1));
}

// currently just mean!!
Vec3 aggregate_samples(int num_samples, World world, Viewport viewp, Camera c, int i, int j) {
	Vec3 acc(0,0,0);
	int max_depth = 5;
	for(int sample = 0; sample < num_samples; sample++) {
		Vec3 pixel_pos = viewp.compute_pixel_pos(c, i, j) + sampler(viewp);
		Ray r(c.origin, pixel_pos - c.origin);	
		acc += ray_color(r, world, max_depth);
	}

	return acc/num_samples;
}

void render_image(Camera c, Viewport viewp, int width, int height) {
	shared_ptr<Sphere> sph = make_shared<Sphere>(Vec3(0,0,-1), 0.5);
	shared_ptr<Sphere> sph2 = make_shared<Sphere>(Vec3(1,0,-1), 0.2);
   	shared_ptr<Sphere> ground = make_shared<Sphere>(Vec3(0,-100.5,-1), 100);
	
//shared_ptr<Sphere> ground = make_shared<Sphere>(Vec3(0, -5, -1), 4.5);
	World world;
	world.add_object(sph);
//	world.add_object(sph2);
	world.add_object(ground);

	int num_samples = 100;
	cout << "P3\n" << width << " " << height << "\n255\n";
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			Vec3 result_color = aggregate_samples(num_samples, world, viewp, c, i, j);
			result_color.print_pixel(true);
		}
	}
}
