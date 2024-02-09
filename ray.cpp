
#include <iostream>
#include <math.h>
#include "render.h"
using namespace std;

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
