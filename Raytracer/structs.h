#pragma once

typedef struct Vec3 {
	float x, y, z;
} Vec3;

typedef struct Color { unsigned char r, g, b; } Color;

typedef struct Sphere {
	Vec3 center;
	float radius;
	Color color;
	float specular;
} Sphere;

enum Light_Type {
	Light_Type_Ambient, Light_Type_Point, Light_Type_Directional
};

typedef struct Light {
	unsigned char type;
	float intensity;
	Vec3 position;
} Light;

typedef struct Scene {
	unsigned ViewportSize;
	int ProjectionPlaneZ;
	Vec3 CameraPosition;
	Color BackgroundColor;
	unsigned SphereCount;
	Sphere* spheres;
	unsigned LightCount;
	Light* lights;
} Scene;