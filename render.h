#include "utils.h"

Vec3 lerp(Vec3 start, Vec3 end, float alpha) {
	return (start*(1.0 - alpha)) + (end*alpha);

}

Vec3 ray_color(Ray r) {
	Sphere sph(Vec3(0,0,-1), 0.5);
	float t = sph.hit(r); 
	if(t != -1.0) {
		Vec3 hit_point = r.pos(t);
		Vec3 n = sph.compute_normal(hit_point); 
		return 0.5 * (n + Vec3(1.0,1.0,1.0));
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
