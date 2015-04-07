#ifndef VECTOR3_H
#define VECTOR3_H

#pragma once

class Vector3 {
	public:
		
		union {
			struct {
				double x;
				double y;
				double z;
			};

			struct {
				double r;
				double g;
				double b;
			};

			double c[3];
		};

		// Konstruktoren
		Vector3() : x(0.0), y(0.0), z(0.0) 																			{}
		Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z)															{}
		Vector3(const double f) : x(f), y(f), z(f)																		{}
		Vector3(const double _x, const double _y, const double _z) : x(_x), y(_y), z(_z)						{}
		Vector3(const double* pfComponent) : x(pfComponent[0]), y(pfComponent[1]), z(pfComponent[2])	{}

		// Zuweisungsoperatoren
		Vector3& operator = (const Vector3& v) {x = v.x; y = v.y; z = v.z; return *this;}
		Vector3& operator += (const Vector3& v) {x += v.x; y += v.y; z += v.z; return *this;}
		Vector3& operator -= (const Vector3& v) {x -= v.x; y -= v.y; z -= v.z; return *this;}
		Vector3& operator *= (const Vector3& v) {x *= v.x; y *= v.y; z *= v.z; return *this;}
		Vector3& operator *= (const float f) {x *= f; y *= f; z *= f; return *this;}
		Vector3& operator /= (const Vector3& v) {x /= v.x; y /= v.y; z /= v.z; return *this;}
		Vector3& operator /= (const float f) {x /= f; y /= f; z /= f; return *this;}

};

// Arithmetische Operatoren
inline Vector3 operator + (const Vector3& a, const Vector3& b) {return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);}
inline Vector3 operator - (const Vector3& a, const Vector3& b) {return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);}
inline Vector3 operator - (const Vector3& v) {return Vector3(-v.x, -v.y, -v.z);}
inline Vector3 operator * (const Vector3& a, const Vector3& b) {return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);}
inline Vector3 operator * (const Vector3& v, const double f) {return Vector3(v.x * f, v.y * f, v.z * f);}
inline Vector3 operator * (const double f, const Vector3& v) {return Vector3(v.x * f, v.y * f, v.z * f);}
inline Vector3 operator / (const Vector3& a, const Vector3& b) {return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);}
inline Vector3 operator / (const Vector3& v, const double f) {return Vector3(v.x / f, v.y / f, v.z / f);}

// Vergleichsoperatoren
inline bool operator == (const Vector3& a, const Vector3& b) {if(a.x != b.x) return false; if(a.y != b.y) return false; return a.z == b.z;}
inline bool operator != (const Vector3& a, const Vector3& b) {if(a.x != b.x) return true; if(a.y != b.y) return true; return a.z != b.z;}

// Funktionen deklarieren
inline double	Vector3Length(const Vector3& v) {return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);}
inline double	Vector3LengthSq(const Vector3& v) {return v.x * v.x + v.y * v.y + v.z * v.z;}
inline Vector3 Vector3Normalize(const Vector3& v) {return v / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);}
inline Vector3 Vector3NormalizeEx(const Vector3& v) {return v / (sqrt(v.x * v.x + v.y * v.y + v.z * v.z) + 0.0001);}
inline Vector3 Vector3Cross(const Vector3& v1, const Vector3& v2) {return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);}
inline double	Vector3Dot(const Vector3& v1, const Vector3& v2) {return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
inline double	Vector3Angle(const Vector3& v1, const Vector3& v2) {return acos((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / sqrt((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z) * (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z)));}
inline Vector3 Vector3InterpolateCoords(const Vector3& v1, const Vector3& v2, const double p) {return v1 + p * (v2 - v1);}
inline Vector3 Vector3InterpolateNormal(const Vector3& v1, const Vector3& v2, const double p) {return Vector3NormalizeEx(v1 + p * (v2 - v1));}
inline Vector3 Vector3Min(const Vector3& v1, const Vector3& v2) {return Vector3(FM_MIN(v1.x, v2.x), FM_MIN(v1.y, v2.y), FM_MIN(v1.z, v2.z));}
inline Vector3 Vector3Max(const Vector3& v1, const Vector3& v2) {return Vector3(FM_MAX(v1.x, v2.x), FM_MAX(v1.y, v2.y), FM_MAX(v1.z, v2.z));}

inline int Vector3BiggestDimension(const Vector3& v) {
	if(v.x >= v.y && v.x >= v.z)
		return 0;
	else if(v.y >= v.x && v.y >= v.z)
		return 1;
	else
		return 2;
}

#endif
