#ifndef RENDER_H
#define RENDER_H

#include "objects.h"
#include <stdlib.h>

Vec3 lerp(Vec3 start, Vec3 end, float alpha) {
	return (start*(1.0 - alpha)) + (end*alpha);

}

// returns offset to be added to some pixel
Vec3 sampler(Viewport viewp) {
	float offset_vertical = rand_unit() - 0.5;
	float offset_horizontal = rand_unit() - 0.5;
	return (offset_vertical * viewp.pixel_delta_v) + (offset_horizontal * viewp.pixel_delta_h);	
}


Vec3 ray_color(Ray r, World world, int depth) {
	Context hit_ctx = world.hit(r); 
	float t = hit_ctx.t_val;  
	if(t != infinity && hit_ctx.object_hit != nullptr && depth > 0) {
		Vec3 hit_point = r.pos(t);
		Vec3 n = hit_ctx.object_hit->compute_normal(hit_point); 
		shared_ptr<Material> shader = hit_ctx.object_hit->material;
		return 0.5 * ray_color(shader->reflect(hit_point, n, r), world, depth-1);
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

void render_image(World world, Camera c, Viewport viewp, int width, int height) {
	int num_samples = 100;
	cout << "P3\n" << width << " " << height << "\n255\n";
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			Vec3 result_color = aggregate_samples(num_samples, world, viewp, c, i, j);
			result_color.print_pixel(true);
		}
	}
}

#endif
