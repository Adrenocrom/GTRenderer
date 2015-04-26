#ifndef SI_H
#define SI_H

#pragma once

#define SI_WIDTH	640
#define SI_HEIGHT 480

typedef float real;
typedef unsigned int uint;

struct rgb;

typedef real real3x3[9];
typedef rgb rgbWxH[SI_WIDTH][SI_HEIGHT];

struct real3 {
	real x;
	real y;
	real z;

	real3() : x(0.0), y(0.0), z(0.0) 														{}
	real3(const real _x, const real _y, const real _z) : x(_x), y(_y), z(_z)	{}

	real3& operator = (const real3& v) {x = v.x; y = v.y; z = v.z; return *this;}
	real3& operator += (const real3& v) {x += v.x; y += v.y; z += v.z; return *this;}
	real3& operator -= (const real3& v) {x -= v.x; y -= v.y; z -= v.z; return *this;}
	real3& operator *= (const real3& v) {x *= v.x; y *= v.y; z *= v.z; return *this;}
	real3& operator *= (const real f) {x *= f; y *= f; z *= f; return *this;}
	real3& operator /= (const real3& v) {x /= v.x; y /= v.y; z /= v.z; return *this;}
	real3& operator /= (const real f) {x /= f; y /= f; z /= f; return *this;}

	real3& rotate(real3x3 m) {
		const real3 t = *this;
		x = t.x*m[0] + t.y*m[1] + t.z*m[2];
		y = t.x*m[3] + t.y*m[4] + t.z*m[5];
		z = t.x*m[6] + t.y*m[7] + t.z*m[8];
		return *this;
	}
};

inline real3 operator + (const real3& a, const real3& b) {return real3(a.x + b.x, a.y + b.y, a.z + b.z);}
inline real3 operator - (const real3& a, const real3& b) {return real3(a.x - b.x, a.y - b.y, a.z - b.z);}
inline real3 operator - (const real3& v) {return real3(-v.x, -v.y, -v.z);}
inline real3 operator * (const real3& a, const real3& b) {return real3(a.x * b.x, a.y * b.y, a.z * b.z);}
inline real3 operator * (const real3& v, const real f) {return real3(v.x * f, v.y * f, v.z * f);}
inline real3 operator * (const real f, const real3& v) {return real3(v.x * f, v.y * f, v.z * f);}
inline real3 operator / (const real3& a, const real3& b) {return real3(a.x / b.x, a.y / b.y, a.z / b.z);}
inline real3 operator / (const real3& v, const real f) {return real3(v.x / f, v.y / f, v.z / f);}

// Vergleichsoperatoren
inline bool operator == (const real3& a, const real3& b) {if(a.x != b.x) return false; if(a.y != b.y) return false; return a.z == b.z;}
inline bool operator != (const real3& a, const real3& b) {if(a.x != b.x) return true; if(a.y != b.y) return true; return a.z != b.z;}

inline real  dot(const real3& a, const real3& b) {return a.x*b.x + a.y*b.y + a.z*b.z;}
inline real3 normalize(const real3& v) {return v / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);}
inline real	 clamp(const real& f) {return MAX(MIN(255.0, f), 0.0);}

struct rgb {
	uint r;
	uint g;
	uint b;

	rgb() : r(0), g(0), b(0) {}
	rgb(const uint _r, const uint _g, const uint _b) : r(_r), g(_g), b(_b) {}

	rgb& operator = (const real3& v) {
		r = (uint)clamp(v.x);
		g = (uint)clamp(v.y);
		b = (uint)clamp(v.z);
		return *this;
	}
};

struct ray {
	real3 o;
	real3 d;
	
	ray() : o(real3()), d(real3(0.0, 0.0, 1.0))			{}
	ray(const real3 _o, const real3 _d) : o(_o), d(_d) {}
};

struct sphere {
	real3 p;		// position
	real 	r;		// radius
	real3	c;		// color
	real 	k;		// kappa
};

struct hitInfo {
	int  id;
	real tn;
	real tf;
};

uint intersect(const ray& r, const sphere& s, hitInfo& info);
void saveRgbWxHToPbm(const rgbWxH& image, const char* pcFilename);

#endif