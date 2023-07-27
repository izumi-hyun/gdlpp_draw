#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <gdiplus.h>
#include "resource.h"
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

HDC hdc;
ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

int main()
{
	//hdc = GetDC(FindWindow(NULL, L"notepad"));
	//hdc = GetDC(FindWindow(NULL, L"제목 없음 - Windows 메모장"));
	//hdc = GetDC(FindWindow(NULL, L"제목 없음 - 그림판"));
	HDC hMemDC= NULL;
	HBITMAP hImage, hOldBitmap = NULL, hBackBitmap;
	BITMAP bit, hImage2;
	//hImage = (HBITMAP)LoadImage(NULL, L"bitmap_location", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	hImage = (HBITMAP)LoadImage(NULL, L"./Dimage.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	hMemDC = CreateCompatibleDC(hdc);

	// bitmap_size
	int bx=0, by=0;
	HWND hDesktop = FindWindowExW(::FindWindowExW(::FindWindow(L"Progman", nullptr), nullptr, L"SHELLDLL_DefView", nullptr), nullptr, L"SysListView32", nullptr);
	SetWindowPos(hDesktop, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE || SWP_NOMOVE);
	hdc = GetDC(hDesktop);
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);	
	//Image* image = Image::FromFile(L"./Dimage.bmp");
	Bitmap* bitmap = Bitmap::FromFile(L"./Dimage.bmp");
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bitmap->GetWidth(); //bx = bit.bmWidth;
	by = bitmap->GetHeight(); //by = bit.bmHeight;
	::Graphics g(hdc);
	while (true)
	{
		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);
		//g.DrawImage(bitmap, 600, 0, bx, by);
	}
	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hImage);
	DeleteDC(hMemDC);
	//delete image;
}
