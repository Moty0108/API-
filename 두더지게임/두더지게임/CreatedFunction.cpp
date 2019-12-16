#pragma once
#include"CreatedFunction.h"
#include"resource.h"

void allDrawEnemy(HDC hdc, HDC MemDc, HBITMAP *Hbitmap, int name, RECT enemy[][3], int Live[][3], HINSTANCE g_hInst)
{
	int i, j;
	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 3; i++)
		{
			if (Live[j][i] > 0)
				DrawBit2(hdc, MemDc, Hbitmap, enemy[j][i].left, enemy[j][i].top, name, &enemy[j][i], g_hInst);
			if (Live[j][i] < 0)
				DrawBit2(hdc, MemDc, Hbitmap, enemy[j][i].left, enemy[j][i].top, ENEMY_ATTACK, &enemy[j][i], g_hInst);
		}
	}
}

void DrawMain(HDC hdc, HDC MemDc, HBITMAP *hBitmap, RECT *i_Title, RECT *b_Start, RECT *back, HINSTANCE g_hInst)
{
	DrawBit2(hdc, MemDc, hBitmap, 0, 0, BACKGROUND, back, g_hInst);
	DrawBit2(hdc, MemDc, hBitmap, 0, 0, TITLE, i_Title, g_hInst);
	DrawBit2(hdc, MemDc, hBitmap, 280, 400, B_START, b_Start, g_hInst);
}

BOOL mosTorec(RECT rec, LPARAM lParam)
{
	int x, y;

	x = LOWORD(lParam);
	y = HIWORD(lParam);

	if (rec.left < x && rec.top < y && rec.right > x && rec.bottom > y)
		return true;
	else
		return false;
}



void DrawBit2(HDC backDC, HDC MemDc, HBITMAP *hBitmap, int x, int y, int num, RECT *pos, HINSTANCE g_hInst)
{
	int nWidth, nHeight;
	BITMAP Bitmap;
	HBITMAP zBitmap, hOldBitmap;


	zBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(num));
	hOldBitmap = (HBITMAP)SelectObject(MemDc, zBitmap);

	GetObject(zBitmap, sizeof(BITMAP), &Bitmap);

	nWidth = Bitmap.bmWidth;
	nHeight = Bitmap.bmHeight;

	pos->left = x;
	pos->top = y;
	pos->bottom = y + nHeight;
	pos->right = x + nWidth;

	TransparentBlt(backDC, x, y, nWidth, nHeight, MemDc, 0, 0, nWidth, nHeight, RGB(255, 0, 255));

	DeleteObject(zBitmap);
}
