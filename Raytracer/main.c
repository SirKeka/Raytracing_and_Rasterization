// Raytracer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "window.h"
#include "Raytracer.h"

int main()
{
	WinCreate(L"Raytracer", 0, 0, 616, 639);

	Scene scene;
	scene.ViewportSize = 1;
	scene.ProjectionPlaneZ = 1;
	scene.CameraPosition = (Vec3){ 0, 0, 0 };
	scene.BackgroundColor = (Color){ 255, 255, 255 };
	scene.SphereCount = 4;

	Sphere spheres[4] = {
		(Sphere) { (Vec3) { 0.F,    -1.F, 3.F },	1.F, (Color){ 255,   0,    0 }, 500 },
		(Sphere) { (Vec3) { -2.F,    0.F, 4.F },	1.F, (Color){ 0,   255,    0 }, 10 },
		(Sphere) { (Vec3) { 2.F,     0.F, 4.F },	1.F, (Color){ 0,      0, 255 }, 500 },
		(Sphere) { (Vec3) { 0.F, -5001.F, 0.F }, 5000.F, (Color){ 255, 255,   0 }, 1000 }
	};
	scene.spheres = spheres;
	scene.LightCount = 3;
	Light lights[3] = {
		(Light){ Light_Type_Ambient,     0.2F },
		(Light){ Light_Type_Point,		 0.6F, (Vec3){ 2.F, 1.F, 0.F } },
		(Light){ Light_Type_Directional, 0.2F, (Vec3){ 1.F, 4.F, 4.F } }
	};
	scene.lights = lights;

	DrawScene(&scene);

	/* Функция UpdateWindow обновляет клиентскую область указанного окна, отправляя в окно сообщение WM_PAINT,
	 * если область обновления окна не пуста. Функция отправляет сообщение WM_PAINT непосредственно в оконную
	 * процедуру указанного окна, минуя очередь приложений. Если область обновления пуста, сообщение не отправляется.
	 */
	 UpdateWindow(WinGetHWND());

	// главный цикл приложения
	while (TRUE) {
		WinMessage();
	}

	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

