#include "Raytracer.h"
#include "window.h"
#include "math.h"

// 1 пиксель экрана равен 0,26 мм
// 4 пикселя ~ равно 1 мм

// Преобразует 2D-координаты холста в 3D-координаты области просмотра.
static Vec3 CanvasToViewport(float x, float y, unsigned ViewportSize, float ProjectionPlaneZ)
{
	RECT rect;
	GetClientRect(WinGetHWND(), &rect);

	Vec3 vec;
	vec.x = x * ViewportSize / rect.right;
	vec.y = y * ViewportSize / rect.bottom;
	vec.z = ProjectionPlaneZ;

	return vec;
}

// Вычисляет пересечение луча и сферы.Возвращает значения t для пересечений.
static void IntersectRaySphere(Vec3 origin, Vec3 direction, Sphere sphere, float OutTs[])
{
	Vec3 oc = Vec3_Sub(origin, sphere.center);

	float k1 = Vec3_Dot(direction, direction);
	float k2 = 2.F * Vec3_Dot(oc, direction);
	float k3 = Vec3_Dot(oc, oc) - sphere.radius * sphere.radius;

	float discriminant = k2 * k2 - 4.F * k1 * k3;
	if (discriminant < 0.F) {
		OutTs[0] = FLOAT_MAX;
		OutTs[1] = FLOAT_MAX;
		return;
	}

	OutTs[0] = (-k2 + sqrtf(discriminant)) / (2.F * k1);
	OutTs[1] = (-k2 - sqrtf(discriminant)) / (2.F * k1);
}

typedef struct {
	Sphere* ClosestSphere;
	float ClosestT;
} Intersections;

static Intersections ClosestIntersection(Vec3 origin, Vec3 direction, float min_t, float max_t, Scene* scene)
{
	float ClosestT = FLOAT_MAX;
	Sphere* ClosestSphere = NULL;

	for (size_t i = 0; i < scene->SphereCount; i++) {
		float ts[2];
		IntersectRaySphere(origin, direction, scene->spheres[i], ts);
		if (ts[0] < ClosestT && min_t < ts[0] && ts[0] < max_t) {
			ClosestT = ts[0];
			ClosestSphere = &scene->spheres[i];
		}
		if (ts[1] < ClosestT && min_t < ts[1] && ts[1] < max_t) {
			ClosestT = ts[1];
			ClosestSphere = &scene->spheres[i];
		}
	}
	return (Intersections) { ClosestSphere, ClosestT };
}

static float ComputeLighting(Vec3 point, Vec3 normal, Vec3 view, float specular, Scene* scene)
{
	float intensity = 0.F; // Интенсивность белого цвета
	float t_max = 0.F;

	for (size_t i = 0; i < scene->LightCount; i++) {
		Light light = scene->lights[i];
		if (light.type == Light_Type_Ambient) {
			intensity += light.intensity;
			continue;
		} 

		Vec3 L;
		if (light.type == Light_Type_Point) {
			L = Vec3_Sub(light.position, point);
			t_max = 1.F;
		} else {
			L = light.position;
			t_max = FLOAT_MAX;
		}

		// Тени
		Intersections intersections = ClosestIntersection(point, L, 0.001F, t_max, scene);
		if (intersections.ClosestSphere != NULL) {
			continue;
		}

		// Diffuse
		float diff = Vec3_Dot(normal, L);
		float distance = Vec3_Length(L);
		if (diff > 0.F) {
			intensity += light.intensity * diff / (Vec3_Length(normal) * distance);
		}

		// Specular
		if (specular != -1) {
			Vec3 R = Vec3_Sub(Vec3_Mul_Scalar(normal, 2.F * diff), L);
			float spec = Vec3_Dot(R, view);
			if (spec > 0) {
				intensity += light.intensity * powf(spec / (Vec3_Length(R) * Vec3_Length(view)), specular);
			}
		}
	}
	return intensity; // powf(intensity, 1.F/2.2F); // Коррекция гаммы
}

// Проводит луч по набору сфер в сцене.
static Color TraceRay(Vec3 origin, Vec3 direction, float min_t, float max_t, Scene* scene)
{
	Intersections intersections = ClosestIntersection(origin, direction, min_t, max_t, scene);

	if (intersections.ClosestSphere == NULL) {
		return (Color) { 255, 255, 255 };
	}

	Vec3 point = Vec3_Add(origin, Vec3_Mul_Scalar(direction, intersections.ClosestT));
	Vec3 normal = Vec3_Sub(point, intersections.ClosestSphere->center);
	normal = Vec3_Mul_Scalar(normal, 1.F / Vec3_Length(normal));

	Vec3 view = Vec3_Mul_Scalar(direction, -1.F);
	float lighting = ComputeLighting(point, normal, view, intersections.ClosestSphere->specular, scene);

	return Color_Mul_Scalar(intersections.ClosestSphere->color, lighting);
}

void DrawScene(Scene* scene)
{
	RECT rect;
	GetClientRect(WinGetHWND(), &rect);
	for (int x = -600 / 2; x < 600 / 2; x++) {
		for (int y = -600 / 2; y < 600 / 2; y++) {
			// Преобразует 2D-координаты холста в 3D-координаты области просмотра.
			Vec3 direction;
			direction.x = (float)x * scene->ViewportSize / rect.right;
			direction.y = (float)y * scene->ViewportSize / rect.bottom;
			direction.z = (float)scene->ProjectionPlaneZ;

			Color color = TraceRay((Vec3) { 0.F, 0.F, 0.F }, direction, 1.F, FLOAT_MAX, scene);

			PutPixel(x, y, color);
		}
	}
}




