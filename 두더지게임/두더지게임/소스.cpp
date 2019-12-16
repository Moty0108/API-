#include<windows.h>
#include"resource.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
#include"Digda.h"
#include"CreatedFunction.h"
#include"GameData.h"

#pragma comment(lib, "Msimg32.lib")


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("두더지게임");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;


	srand((unsigned)time(NULL));

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, MemDc, backDC;
	PAINTSTRUCT ps;
	static RECT b_Start, i_Title, c_Cursor;
	static RECT back, rc;
	static bool bNowGame, bNowCursor;
	static int i = 0, j = 0;
	static int spawnTime = 7, stage;
	static int cur, cur2;
	static TCHAR text[20];
	static TCHAR text2[50];
	static TCHAR text3[10];
	HFONT hfont, oldFont;
	static int mx, my;

	HBITMAP hBitmap, hOldBitmap;
	static HBITMAP backBitmap = NULL;

	static Digda d = Digda();
	static GameData gamedata = GameData();

	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &rc);
		cur = CURSOR;
		cur2 = CURSOR2;
		bNowGame = false;
		bNowCursor = false;
		wsprintf(text3, TEXT("STAGE 1"));
		d.DigdaInit();
		SetTimer(hWnd, 1, 1700, NULL);
		SetTimer(hWnd, 2, 500, NULL);
		SetTimer(hWnd, 4, 100, NULL);
		SetTimer(hWnd, 5, 1000, NULL);
		SetTimer(hWnd, 6, 100, NULL);
		SetCursor(NULL);
		ShowCursor(FALSE);

		break;

	case WM_TIMER:
		switch (wParam)
		{
			//에너미스폰 및 생존시간 설정
		case 1:
			d.DIgdaSpawn(spawnTime);
			InvalidateRect(hWnd, NULL, FALSE);
			break;

			//에너미 생존시간 줄어드는 설정
		case 2:
			d.DigdaLiveTime();
			break;

			//게임시간 설정
		case 3:
			if (gamedata.getGameTime() > 0)
				gamedata.SubGameTime(1);
			if (gamedata.getGameTime() <= 0 && bNowGame)
			{
				bNowGame = FALSE;
				ShowCursor(TRUE);
				wsprintf(text2, TEXT("SCORE : %d\n게임을 종료하시겠습니까?"), gamedata.getGameScore());
				if (MessageBox(hWnd,  text2, TEXT("TIMEOVER!"), MB_YESNO) == IDYES)
				{
					KillTimer(hWnd, 1);
					KillTimer(hWnd, 2);
					KillTimer(hWnd, 3);
					KillTimer(hWnd, 4);
					KillTimer(hWnd, 5);
					KillTimer(hWnd, 6);
					PostQuitMessage(0);
				}
				else
					ShowCursor(FALSE);
			}
			break;

			//화면 지우기
		case 4:
			InvalidateRect(hWnd, NULL, FALSE);
			break;

			//난이도 설정
		case 5:
			if (gamedata.getGameTime() <= 30)
			{
				d.DIgdaSpawn(3);
			}
			
			break;
			
			//난이도 설정 2
		case 6:
			if (gamedata.getGameStage() == 3)
			{
				d.DigdaRandomMove(rc);
			}
			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rc);
		MemDc = CreateCompatibleDC(hdc);
		backDC = CreateCompatibleDC(hdc);
		backBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		hOldBitmap = (HBITMAP)SelectObject(backDC, backBitmap);		

		
		
		if (!bNowGame)
			DrawMain(backDC, MemDc, &hBitmap, &i_Title, &b_Start, &back, g_hInst);
		else
		{
			wsprintf(text2, TEXT("%d"), gamedata.getGameTime());
			wsprintf(text, TEXT("SCORE : %d"), gamedata.getGameScore());

			DrawBit2(backDC, MemDc, &hBitmap,  0, 0, BACKGROUND, &back, g_hInst);
			d.DigdaDraw(backDC, MemDc, hBitmap, g_hInst);

			SetBkMode(backDC, TRANSPARENT);
			SetTextColor(backDC, RGB(56, 46, 44));
			hfont = CreateFont(50, 0, 0, 0, FW_HEAVY, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("빙그레체 Bold"));
			oldFont = (HFONT)SelectObject(backDC, hfont);
			TextOut(backDC, 500, 50, text, lstrlen(text));
			TextOut(backDC, 100, 50, text3, lstrlen(text3));

			SelectObject(backDC, oldFont);
			DeleteObject(hfont);
			hfont = CreateFont(100, 0, 0, 0, FW_HEAVY, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("빙그레체 Bold"));
			oldFont = (HFONT)SelectObject(backDC, hfont);
			TextOut(backDC, 350, 20, text2, lstrlen(text2));
			SelectObject(backDC, oldFont);
			DeleteObject(hfont);
		}
		
		if(!bNowCursor)
		DrawBit2(backDC, MemDc, &hBitmap, mx, my, cur, &c_Cursor, g_hInst);
		else
			DrawBit2(backDC, MemDc, &hBitmap, mx, my, cur2, &c_Cursor, g_hInst);


		SelectObject(MemDc, hOldBitmap);
		DeleteDC(MemDc);
		DeleteObject(hBitmap);

		BitBlt(hdc, 0, 0, rc.right, rc.bottom, backDC, 0, 0, SRCCOPY);

		DeleteObject(SelectObject(backDC, hOldBitmap));
		DeleteDC(backDC);
		DeleteObject(backBitmap);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_MOUSEMOVE:
		mx = LOWORD(lParam) - 20;
		my = HIWORD(lParam) - 150;

		return 0;

	case WM_LBUTTONDOWN:
		bNowCursor = true;
		InvalidateRect(hWnd, NULL, FALSE);
		if (bNowGame)
		{
			if (d.DigdaClicked(lParam))
			{
				gamedata.AddGameScore(100);
			}
		}
		if (mosTorec(b_Start, lParam) && !bNowGame)
		{
			SetTimer(hWnd, 3, 1000, NULL);
			bNowGame = true;
			bNowCursor = false;
			gamedata.InitGameData(stage);
			d.DigdaInit();
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;

	case WM_LBUTTONUP:
		bNowCursor = false;
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_CREATOR:
			ShowCursor(TRUE);
			MessageBox(hWnd, TEXT("김태헌\n조수현\n유승한"), TEXT("CREATOR"), MB_OK);
			ShowCursor(FALSE);
			break;
		case ID_MENU_HELP:
			ShowCursor(TRUE);
			MessageBox(hWnd, TEXT("제한시간내에 최대한 많은 두더지를 잡으십시오!"), TEXT("HELP"), MB_OK);
			ShowCursor(FALSE);
			break;
		case ID_MENU_NEWGAME:
			ShowCursor(TRUE);
			bNowGame = FALSE;
			ShowCursor(FALSE);
			break;
		case ID_MENU_QUITGAME:
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
			KillTimer(hWnd, 5);
			KillTimer(hWnd, 6);
			PostQuitMessage(0);
			return 0;
		case ID_WEAPON_DEFAULT:
			cur = CURSOR;
			cur2 = CURSOR2;
			break;
		case ID_WEAPON_TOUR:
			cur = CURSOR_TOUR;
			cur2 = CURSOR2_TOUR;
			break;
		case ID_STAGE_1:
			spawnTime = 7;
			stage = 1;
			wsprintf(text3, TEXT("STAGE 1"));
			break;
		case ID_STAGE_2:
			spawnTime = 4;
			stage = 2;
			gamedata.setGameStage(2);
			wsprintf(text3, TEXT("STAGE 2"));
			break;
		case ID_STAGE_3:
			spawnTime = 2;
			stage = 3;
			gamedata.setGameStage(3);
			wsprintf(text3, TEXT("STAGE 3"));
			break;
		}
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		KillTimer(hWnd, 5);
		KillTimer(hWnd, 6);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
