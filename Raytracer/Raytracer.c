#include "Raytracer.h"
#include "window.h"
#include <math.h>

// 1 пиксель экрана равен 0,26 мм
// 4 пикселя ~ равно 1 мм

typedef struct Scene {
	int ViewportSize;
	int ProjectionPlaneZ;
	Vec3 CameraPosition;
	COLORREF BackgroundColor;
	Sphere spheres[4];
} Scene;

static Scene state;

int SceneCreate(int ViewportSize, int ProjectionPlaneZ, Vec3 CameraPosition, COLORREF BackgroundColor, Sphere spheres[])
{
	state.ViewportSize = ViewportSize;
	state.ProjectionPlaneZ = ProjectionPlaneZ;
	state.CameraPosition = CameraPosition;
	state.BackgroundColor = BackgroundColor;
	state.spheres[0] = spheres[0];
	state.spheres[1] = spheres[1];
	state.spheres[2] = spheres[2];
	state.spheres[3] = spheres[3];

	return 1;
}

Vec3 CanvasToViewport(float x, float y)
{
	RECT rect;
	GetClientRect(WinGetHWND(), &rect);

	Vec3 vec;
	vec.x = x * state.ViewportSize / rect.right;
	vec.y = y * state.ViewportSize / rect.bottom;
	vec.z = state.ProjectionPlaneZ;

	return vec;
}

void IntersectRaySphere(Vec3 origin, Vec3 direction, Sphere sphere, float OutTs[])
{
	Vec3 oc = Vec3Sub(origin, sphere.center);

	float k1 = Vec3Dot(direction, direction);
	float k2 = 2 * Vec3Dot(oc, direction);
	float k3 = Vec3Dot(oc, oc) - sphere.radius * sphere.radius;

	float discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0) {
		OutTs[0] = FLOAT_MAX;
		OutTs[1] = FLOAT_MAX;
		return;
	}

	OutTs[0] = (-k2 + sqrt(discriminant)) / 2 * k1;
	OutTs[1] = (-k2 - sqrt(discriminant)) / 2 * k1;
}

COLORREF TraceRay(Vec3 origin, Vec3 direction, float min_t, float max_t)
{
	float ClosestT = FLOAT_MAX;
	Sphere* ClosestSphere = NULL;

	for (int i = 0; i < 4; i++) {
		float ts[2];
		IntersectRaySphere(origin, direction, state.spheres[i], ts);
		if (ts[0] < ClosestT && min_t < ts[0] && ts[0] < max_t) {
			ClosestT = ts[0];
			ClosestSphere = &state.spheres[i];
		}
		if (ts[1] < ClosestT && min_t < ts[1] && ts[1] < max_t) {
			ClosestT = ts[1];
			ClosestSphere = &state.spheres[i];
		}
	}

	if (ClosestSphere == NULL) {
		return RGB(255, 255, 255);
	}

	return ClosestSphere->color;
}
