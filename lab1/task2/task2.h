#pragma once

#include "resource.h"
#include "WindowsX.h"

#include <windows.h>

class Truck
{
public:
    Truck() : posX(0), posY(0), lastX(0), lastY(0), isDragging(false)
    {
        bodyBrush = CreateSolidBrush(RGB(0, 0, 200));
        headBrush = CreateSolidBrush(RGB(200, 0, 0));
        windowBrush = CreateSolidBrush(RGB(135, 206, 250));
        doorknobBrush = CreateSolidBrush(RGB(200, 200, 200));
        wheelBrush = CreateSolidBrush(RGB(80, 80, 80));
        diskWheelBrush = CreateSolidBrush(RGB(120, 120, 120));
    }

    ~Truck()
    {
        DeleteBrush(bodyBrush);
        DeleteBrush(headBrush);
        DeleteBrush(windowBrush);
        DeleteBrush(doorknobBrush);
        DeleteBrush(wheelBrush);
    }

    void Draw(HDC hdc)
    {
        if (isDragging)
        {
            Rectangle(hdc, posX + 108, posY + 100, posX + 677, posY + 415);
        }

        // кузов
        SelectBrush(hdc, bodyBrush);
        Rectangle(hdc, posX + 325, posY + 100, posX + 660, posY + 380);

        // кабина
        SelectBrush(hdc, headBrush);
        POINT headPoints[] = {
            {posX + 120, posY + 380},
            {posX + 120, posY + 300},
            {posX + 220, posY + 270},
            {posX + 245, posY + 197},
            {posX + 325, posY + 190},
            {posX + 325, posY + 380},
        };
        Polygon(hdc, headPoints, 6);

        // дверь
        POINT doorPoints[] = {
            {posX + 234, posY + 368},
            {posX + 230, posY + 265},
            {posX + 250, posY + 207},
            {posX + 320, posY + 204},
            {posX + 319, posY + 368},
        };
        Polygon(hdc, doorPoints, 5);

        // окно
        SelectBrush(hdc, windowBrush);
        POINT windowPoints[] = {
            {posX + 240, posY + 265},
            {posX + 255, posY + 215},
            {posX + 313, posY + 213},
            {posX + 313, posY + 265},
        };
        Polygon(hdc, windowPoints, 4);

        // ручка
        SelectBrush(hdc, doorknobBrush);
        Rectangle(hdc, posX + 292, posY + 279, posX + 310, posY + 287);

        // передний бампер
        POINT frontBumperPoints[] = {
            {posX + 108, posY + 378},
            {posX + 108, posY + 358},
            {posX + 120, posY + 353},
            {posX + 120, posY + 378},
        };
        Polygon(hdc, frontBumperPoints, 4);

        // задний бампер
        POINT backBumperPoints[] = {
            {posX + 660, posY + 378},
            {posX + 660, posY + 340},
            {posX + 675, posY + 351},
            {posX + 677, posY + 378},
        };
        Polygon(hdc, backBumperPoints, 4);

        // переднее колесо
        SelectBrush(hdc, wheelBrush);
        Ellipse(hdc, posX + 135, posY + 325, posX + 228, posY + 415);

        // заднее колесо
        Ellipse(hdc, posX + 530, posY + 325, posX + 620, posY + 415);

        // передний диск колеса
        SelectBrush(hdc, diskWheelBrush);
        Ellipse(hdc, posX + 155, posY + 345, posX + 208, posY + 395);

        // задний диск колеса
        Ellipse(hdc, posX + 550, posY + 345, posX + 600, posY + 395);
    }

    void OnMouseDown(int x, int y)
    {
        if (x >= posX + 108 && x <= posX + 677 && y >= posY + 100 && y <= posY + 415)
        {
            isDragging = true;
            lastX = x;
            lastY = y;
        }
    }

    void OnMouseMove(int x, int y)
    {
        if (isDragging)
        {
            posX += x - lastX;
            posY += y - lastY;
            lastX = x;
            lastY = y;

        }
    }

    void OnMouseUp()
    {
        isDragging = false;
    }

private:
    int posX, posY;
    int lastX, lastY;
    bool isDragging;

    HBRUSH bodyBrush, headBrush, windowBrush, doorknobBrush, wheelBrush, diskWheelBrush;
};
