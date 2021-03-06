#include "math/int3.h"

#include <iostream>

#include "utility/convert.h"


// Constr
kl::int3::int3() : x(0), y(0), z(0) {}
kl::int3::int3(int a) : x(a), y(a), z(a) {}
kl::int3::int3(int x, int y, int z) : x(x), y(y), z(z) {}
kl::int3::int3(const kl::int2& v, int z) : x(v.x), y(v.y), z(z) {}
kl::int3::int3(int x, const kl::int2& v) : x(x), y(v.x), z(v.y) {}

// Getters
int& kl::int3::operator[](int i) {
	return data[i];
}
const int& kl::int3::operator[](int i) const {
	return data[i];
}

// Addition
kl::int3 kl::int3::add(const kl::int3& obj) const {
	return kl::int3(x + obj.x, y + obj.y, z + obj.z);
}
kl::int3 kl::int3::operator+(const kl::int3& obj) const {
	return add(obj);
}
void kl::int3::operator+=(const kl::int3& obj) {
	x += obj.x; y += obj.y; z += obj.z;
}

// Subtraction
kl::int3 kl::int3::sub(const kl::int3& obj) const {
	return kl::int3(x - obj.x, y - obj.y, z - obj.z);
}
kl::int3 kl::int3::operator-(const kl::int3& obj) const {
	return sub(obj);
}
void kl::int3::operator-=(const kl::int3& obj) {
	x -= obj.x; y -= obj.y; z -= obj.z;
}

// Multiplication
kl::int3 kl::int3::mul(int a) const {
	return kl::int3(x * a, y * a, z * a);
}
kl::int3 kl::int3::operator*(int a) const {
	return mul(a);
}
void kl::int3::operator*=(int a) {
	x *= a; y *= a; z *= a;
}
kl::int3 kl::int3::mul(const kl::int3& obj) const {
	return kl::int3(x * obj.x, y * obj.y, z * obj.z);
}
kl::int3 kl::int3::operator*(const kl::int3& obj) const {
	return mul(obj);
}
void kl::int3::operator*=(const kl::int3& obj) {
	x *= obj.x; y *= obj.y; z *= obj.z;
}

// Division
kl::int3 kl::int3::div(int a) const {
	return kl::int3(x / a, y / a, z / a);
}
kl::int3 kl::int3::operator/(int a) const {
	return div(a);
}
void kl::int3::operator/=(int a) {
	x /= a; y /= a; z /= a;
}
kl::int3 kl::int3::div(const kl::int3& obj) const {
	return kl::int3(x / obj.x, y / obj.y, z / obj.z);
}
kl::int3 kl::int3::operator/(const kl::int3& obj) const {
	return div(obj);
}
void kl::int3::operator/=(const kl::int3& obj) {
	x /= obj.x; y /= obj.y; z /= obj.z;
}

// Comparison
bool kl::int3::equals(const kl::int3& obj) const {
	return x == obj.x && y == obj.y && z == obj.z;
}
bool kl::int3::operator==(const kl::int3& obj) const {
	return equals(obj);
}
bool kl::int3::operator!=(const kl::int3& obj) const {
	return !equals(obj);
}

// Returns a negated vec
kl::int3 kl::int3::negate() const {
	return mul(-1);
}

// Returns an absolute vec
kl::int3 kl::int3::abso() const {
	return kl::int3(abs(x), abs(y), abs(z));
}

// Overloading std::cout
std::ostream& kl::operator<<(std::ostream& os, const kl::int3& obj) {
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
	return os;
}
