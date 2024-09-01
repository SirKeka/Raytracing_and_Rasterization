﻿// Raytracer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "window.h"
#include "Raytracer.h"

int main()
{
	WinCreate("Raytracer", 0, 0, 616, 639);
	HWND hwnd = WinGetHWND();
	RECT rect;
	GetClientRect(hwnd, &rect);

	Sphere spheres[4] = {
		(Sphere) { (Vec3) { 0, -1, 3 }, 1, RGB(255, 0, 0) },
		(Sphere) { (Vec3) { -2, 0, 4 }, 1, RGB(0, 255, 0) },
		(Sphere) { (Vec3) { 2, 0, 4 }, 1, RGB(0, 0, 255) },
		(Sphere) { (Vec3) { 0, -5001, 0 }, 5000, RGB(255, 255, 0) }
	};

	SceneCreate(1, 1, (Vec3) { 0, 0, 0 }, RGB(255, 255, 255), spheres);

	/* Функция UpdateWindow обновляет клиентскую область указанного окна, отправляя в окно сообщение WM_PAINT,
	 * если область обновления окна не пуста. Функция отправляет сообщение WM_PAINT непосредственно в оконную
	 * процедуру указанного окна, минуя очередь приложений. Если область обновления пуста, сообщение не отправляется.
	 */
	 UpdateWindow(WinGetHWND());

	// главный цикл приложения
	while (1) {
		WinMessage();

	}

	

	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
