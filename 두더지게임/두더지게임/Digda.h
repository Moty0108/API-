#pragma once
#ifndef __DIGDA_H__
#define __DIGDA_H__


#include<Windows.h>
class Digda
{
private:
	RECT enemy[3][3];
	int enemyLive[3][3];
	int enemyMove[3][3];
	int enemyTale[3][3];
	int enemyX, enemyY, spawnTime;
public:
	Digda();
	void DIgdaSpawn(int LiveTime);
	void DigdaLiveTime();
	void DigdaRandomMove(RECT rc);
	void DigdaDraw(HDC backDC, HDC MemDc, HBITMAP hBitmap, HINSTANCE g_hInst);
	bool DigdaClicked(LPARAM lParam);
	void DigdaInit();

}; 
#endif // !__DIGDA_H__