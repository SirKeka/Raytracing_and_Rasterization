#pragma once

typedef struct Vec3
{
	float x, y, z;
} Vec3;

Vec3 Vec3Create(float x, float y, float z);

float Vec3Dot(Vec3 a, Vec3 b);
Vec3 Vec3Sub(Vec3 a, Vec3 b);