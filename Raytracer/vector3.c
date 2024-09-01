#include "vector3.h"

Vec3 Vec3Create(float x, float y, float z)
{
	return (Vec3) {x, y, z};
}

float Vec3Dot(Vec3 a, Vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3Sub(Vec3 a, Vec3 b)
{
	return (Vec3) {a.x - b.x, a.y - b.y, a.z - b.z};
}
