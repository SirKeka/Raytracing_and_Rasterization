#pragma once
#include "vector3.h"
#include "window.h"

typedef struct Sphere {
	Vec3 center;
	int radius;
	Color color;
} Sphere;

int SceneCreate(int ViewportSize, int ProjectionPlaneZ, Vec3 CameraPosition, Color BackgroundColor, Sphere spheres[]);

// Преобразует 2D-координаты холста в 3D-координаты области просмотра.
Vec3 CanvasToViewport(float x, float y);

// Вычисляет пересечение луча и сферы.Возвращает значения t для пересечений.
void IntersectRaySphere(Vec3 origin, Vec3 direction, Sphere sphere, float OutTs[]);

// Проводит луч по набору сфер в сцене.
Color TraceRay(Vec3 origin, Vec3 direction, float min_t, float max_t);