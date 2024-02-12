
Vec3 random_unit_vec() {
	return Vec3(rand_bounds(-1., 1.), rand_bounds(-1., 1.), rand_bounds(-1., 1.)).normalise();
}

void random_ray(Vec3 normal, Vec3 point) {	
	Vec3 unit_vec = random_unit_vec();
	if(unit_vec * normal < 0.) {
		unit_vec = -1 * unit_vec;	
	} 
	
	// from intersection point to random direction
	return Ray(point, unit_vec);
}

