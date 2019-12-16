#pragma once
#ifndef __CreatedFunction_H__
#define __CreatedFunction_H__
#include<Windows.h>

void DrawBit2(HDC backDC, HDC MemDc, HBITMAP *hBitmap, int x, int y, int num, RECT *pos, HINSTANCE g_hInst);
BOOL mosTorec(RECT rec, LPARAM lParam);
void DrawMain(HDC hdc, HDC MemDc, HBITMAP *hBitmap, RECT *i_Title, RECT *b_Start, RECT *back, HINSTANCE g_hInst);
void allDrawEnemy(HDC hdc, HDC MemDc, HBITMAP *Hbitmap, int name, RECT enemy[][3], int Live[][3], HINSTANCE g_hInst);

#endif 