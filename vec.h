
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
