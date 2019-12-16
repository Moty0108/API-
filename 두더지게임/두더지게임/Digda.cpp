#pragma once
#include"Digda.h"
#include"resource.h"
#include"CreatedFunction.h"

	Digda::Digda()
	{
		spawnTime = 7;
		enemyX = 75, enemyY = 105;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				enemyLive[i][j] = 0;
				enemyMove[i][j] = 0;
				enemyTale[i][j] = 1;
				enemy[j][i] = { enemyX + (260 * i), enemyY + (150 * j), enemyX + (260 * i) + WIDTH, enemyY + (150 * j) + HEIGHT };
			}
		}
	}

	void Digda::DIgdaSpawn(int LiveTime)
	{
		int i = rand() % 3;
		int j = rand() % 3;
		enemyLive[i][j] = rand() % LiveTime + 1;
	}

	void Digda::DigdaLiveTime()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (enemyLive[i][j] > 0)
				{
					enemyLive[i][j] -= 1;
				}
				if (enemyLive[i][j] < 0)
				{
					enemyLive[i][j] += 1;
				}

			}
		}
	}

	void Digda::DigdaRandomMove(RECT rc)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (enemyMove[i][j] == 0)
				{
					enemy[i][j].left -= SPEED;
					enemy[i][j].top -= SPEED;
					if (enemy[i][j].left <= rc.left || enemy[i][j].top <= rc.top + 130)
					{
						enemy[i][j].left += SPEED;
						enemy[i][j].top += SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
				else if (enemyMove[i][j] == 1)
				{
					enemy[i][j].top -= SPEED;
					if (enemy[i][j].top <= rc.top + 130)
					{
						enemy[i][j].top += SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
				else if (enemyMove[i][j] == 2)
				{
					enemy[i][j].left += SPEED;
					enemy[i][j].top -= SPEED;
					if (enemy[i][j].right >= rc.right || enemy[i][j].top <= rc.top + 130)
					{
						enemy[i][j].left -= SPEED;
						enemy[i][j].top += SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
				else if (enemyMove[i][j] == 3)
				{
					enemy[i][j].left -= SPEED;
					if (enemy[i][j].left <= rc.left)
					{
						enemy[i][j].left += SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
				else if (enemyMove[i][j] == 4)
				{
					enemyMove[i][j] = rand() % 9;
				}

				else if (enemyMove[i][j] == 5)
				{
					enemy[i][j].left += SPEED;
					if (enemy[i][j].right >= rc.right)
					{
						enemy[i][j].left -= SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
				else if (enemyMove[i][j] == 6)
				{
					enemy[i][j].left -= SPEED;
					enemy[i][j].top += SPEED;
					if (enemy[i][j].left <= rc.left || enemy[i][j].bottom >= rc.bottom)
					{
						enemy[i][j].left += SPEED;
						enemy[i][j].top -= SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
				else if (enemyMove[i][j] == 7)
				{
					enemy[i][j].top += SPEED;
					if (enemy[i][j].bottom >= rc.bottom)
					{
						enemy[i][j].top -= SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
				else if (enemyMove[i][j] == 8)
				{
					enemy[i][j].left += SPEED;
					enemy[i][j].top += SPEED;
					if (enemy[i][j].right >= rc.right || enemy[i][j].bottom >= rc.bottom)
					{
						enemy[i][j].left -= SPEED;
						enemy[i][j].top -= SPEED;
						enemyMove[i][j] = rand() % 9;
					}
				}
			}
		}
	}

	void Digda::DigdaDraw(HDC backDC, HDC MemDc, HBITMAP hBitmap, HINSTANCE g_hInst)
	{
		allDrawEnemy(backDC, MemDc, &hBitmap, ENEMY_TAIL, enemy, enemyTale, g_hInst);
		allDrawEnemy(backDC, MemDc, &hBitmap, ENEMY, enemy, enemyLive, g_hInst);
	}

	bool Digda::DigdaClicked(LPARAM lParam)
	{
		int a, b;
		for (a = 0; a < 3; a++)
		{
			for (b = 0; b < 3; b++)
			{
				if (mosTorec(enemy[a][b], lParam) && enemyLive[a][b] > 0)
				{
					enemyLive[a][b] = -2;
					return true;
				}
			}
		}
		return false;
	}

	void Digda::DigdaInit()
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				enemy[j][i] = { enemyX + (260 * i), enemyY + (150 * j), enemyX + (260 * i) + WIDTH, enemyY + (150 * j) + HEIGHT };
			}
		}
	}