// Raytracer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "window.h"
#include "Raytracer.h"

int main()
{
	WinCreate("Raytracer", 0, 0, 616, 639);

	Sphere spheres[4] = {
		(Sphere) { (Vec3) { 0,    -1, 3 },	  1, (Color){ 255,   0,   0, 255 } },
		(Sphere) { (Vec3) { -2,    0, 4 },	  1, (Color){ 0,   255,   0, 255 } },
		(Sphere) { (Vec3) { 2,     0, 4 },	  1, (Color){ 0,     0, 255, 255 } },
		(Sphere) { (Vec3) { 0, -5001, 0 }, 5000, (Color){ 255, 255,   0, 255 } }
	};

	SceneCreate(1, 1, (Vec3) { 0, 0, 0 }, (Color) { 255, 255, 255, 255 }, spheres);

	for (int x = -600 / 2; x < 600 / 2; x++) {
		for (int y = -600 / 2; y < 600 / 2; y++) {
			Vec3 direction = CanvasToViewport(x, y);
			Color color = TraceRay((Vec3) { 0, 0, 0 }, direction, 1, FLOAT_MAX);
			PutPixel(x, y, color);
		}
	}

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

