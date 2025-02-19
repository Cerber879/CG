#pragma once

#include "resource.h"
#include "WindowsX.h"

#include <cmath>
#include <ctime>
#include <windows.h>

#define PI 3.14159265

class LetterAnimator
{
public:
    LetterAnimator() : offsetFirst(0.0), offsetSecond(0.0), offsetThird(0.0),
        amplitude(100.0), frequency(1.5)
    {
        redPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
        redBrush = CreateSolidBrush(RGB(255, 0, 0));
        greenPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
        greenBrush = CreateSolidBrush(RGB(0, 255, 0));
        bluePen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
        blueBrush = CreateSolidBrush(RGB(0, 0, 255));

        DWORD currentTime = GetTickCount64();
        startTimeFirst = currentTime;       
        startTimeSecond = currentTime + 500;
        startTimeThird = currentTime + 1000; 
    }

    ~LetterAnimator() 
    {
        DeletePen(redPen);
        DeleteBrush(redBrush);
        DeletePen(greenPen);
        DeleteBrush(greenBrush);
        DeletePen(bluePen);
        DeleteBrush(blueBrush);
    }

    void UpdateOffsets()
    {
        static double velocityFirst = 0.0;
        static double velocitySecond = 0.0;
        static double velocityThird = 0.0;

        double acceleration = 0.1;
        DWORD currentTime = GetTickCount64();

        if (currentTime >= startTimeFirst)
        {
            velocityFirst += acceleration;
            offsetFirst += velocityFirst;
            if (offsetFirst > amplitude) 
            {
                velocityFirst *= -1;
                offsetFirst =  amplitude;
            }
        }

        if (currentTime >= startTimeSecond)
        {
            velocitySecond += acceleration;
            offsetSecond += velocitySecond;
            if (offsetSecond > amplitude) 
            {
                velocitySecond *= -1;
                offsetSecond = amplitude;
            }
        }

        if (currentTime >= startTimeThird) 
        {
            velocityThird += acceleration;
            offsetThird += velocityThird;
            if (offsetThird > amplitude) 
            {
                velocityThird *= -1;
                offsetThird = amplitude;
            }
        }
    }


    void DrawLetters(HDC dc)
    {
        // Буква 'А'
        SelectPen(dc, redPen);
        SelectBrush(dc, redBrush);
        POINT aPoints[] = { 
            {70, 250 + offsetFirst}, 
            {150, 50 + offsetFirst},
            {230, 250 + offsetFirst}, 
            {200, 250 + offsetFirst}, 
            {150, 110 + offsetFirst}, 
            {100, 250 + offsetFirst}
        };
        Polygon(dc, aPoints, 6);
        Rectangle(dc, 110, 180 + offsetFirst, 190, 200 + offsetFirst);

        // Буква 'Н'
        SelectPen(dc, greenPen);
        SelectBrush(dc, greenBrush);
        Rectangle(dc, 260, 50 + offsetSecond, 290, 250 + offsetSecond);
        Rectangle(dc, 360, 50 + offsetSecond, 390, 250 + offsetSecond);
        Rectangle(dc, 260, 140 + offsetSecond, 390, 170 + offsetSecond);

        // Буква 'А'
        SelectPen(dc, bluePen);
        SelectBrush(dc, blueBrush);
        POINT a2Points[] = { 
            {420, 250 + offsetThird},
            {500, 50 + offsetThird},
            {580, 250 + offsetThird},
            {550, 250 + offsetThird},
            {500, 110 + offsetThird},
            {450, 250 + offsetThird}
        };
        Polygon(dc, a2Points, 6);
        Rectangle(dc, 470, 180 + offsetThird, 550, 200 + offsetThird);
    }

private:
    double offsetFirst, offsetSecond, offsetThird;
    double amplitude;
    double frequency;

    DWORD startTimeFirst, startTimeSecond, startTimeThird; 

    HPEN redPen, greenPen, bluePen;
    HBRUSH redBrush, greenBrush, blueBrush;
};