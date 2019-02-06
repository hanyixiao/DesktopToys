/*@fuction: unkown
 *@data: 2019-2-2
 *@author:YixiaoHan
  */
#pragma once
#include "stdafx.h"
class CScreenTools
{
private:
	CScreenTools()
	{

	}
	~CScreenTools()
	{

	}
private:
	//����ÿ��λͼ�ļ�ռ�õ��ֽ���
	static int GetBits()
	{
		//��ʾ��ǰ�ֱ�����ÿ��������ռ���ֽ���
		int iBits;
		HDC hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		iBits = GetDeviceCaps(hDC, BITSPIXEL)*GetDeviceCaps(hDC, PLANES);
		DeleteDC(hDC);
		return iBits;
	}
	//ȷ���Ƕ���λ��λͼ
	static int GetBitCount(int iBits)
	{
		int wBitCount;
		if (iBits <= 1)
		{
			wBitCount = 1;
		}
		else if (iBits <= 4)
		{
			wBitCount = 4;
		}
		else if (iBits <= 8)
		{
			wBitCount = 8;
		}
		else if (iBits <= 24)
		{
			wBitCount = 24;
		}
		else {
			wBitCount = 32;
		}
		return wBitCount;
	}
	static BOOL WriteBmpDataToFile(PCTSTR szFileName,
		PBITMAPINFOHEADER pBitmapInfoHeader,
		DWORD dwPaletteSize, DWORD dwBmBitsSize)
	{
		//д���ֽ���
		DWORD dwWrite;
		HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
			NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			return FALSE;
		}
		BITMAPFILEHEADER bitmapFileHeader;
		//����λͼ�ļ�ͷ
		bitmapFileHeader.bfType = 0x4D42;//0x4d42��BM
		bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
			dwPaletteSize + dwBmBitsSize;
		bitmapFileHeader.bfReserved1 = 0;
		bitmapFileHeader.bfReserved2 = 0;
		bitmapFileHeader.bfOffBits= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
			dwPaletteSize;
		//д��λͼ�ļ�ͷ
		WriteFile(hFile, (LPSTR)&bitmapFileHeader, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
			+ dwBmBitsSize + dwPaletteSize, &dwWrite, NULL);
		//�ر��ļ�
		CloseHandle(hFile);
		return true;
	}
public:
	//���浽�ļ�
	static int SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName)
	{
		/*bitmap�ļ���ʽ����
		 *BITMAPFILEHEADER
		 *BITMAPINFOHEADER
		 *RGBQUAD arry
		 *Color-index arry
		*/
		BOOL bRet = FALSE;
		//λͼ��ÿ��������ռ���ֽ���
		WORD wBitCount;
		//�����ɫ��Ĵ�С��λͼ�����صĴ�С��λͼ�ļ���С��д���ļ��ֽ���
		DWORD dwPaletteSize = 0;
		DWORD dwBmBitSize;
		BITMAP Bitmap;
		BITMAPINFOHEADER bitmapInfoHeader;    //λͼ���Խṹ
		LPBITMAPINFOHEADER pBitmapInfoHeader; //λͼ��Ϣ�ṹ
		wBitCount = GetBitCount(GetBits());   //ȷ������λ��λͼ
		if (wBitCount <= 8) {				  //�����ɫ���С
			dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);
		}
		//����λͼ��Ϣͷ�ṹ
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
		bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfoHeader.biWidth = Bitmap.bmWidth;
		bitmapInfoHeader.biHeight = Bitmap.bmHeight;
		bitmapInfoHeader.biPlanes = 1;
		bitmapInfoHeader.biBitCount = wBitCount;
		bitmapInfoHeader.biCompression = BI_RGB;
		bitmapInfoHeader.biSizeImage = 0;
		bitmapInfoHeader.biXPelsPerMeter = 0;
		bitmapInfoHeader.biYPelsPerMeter = 0;
		bitmapInfoHeader.biClrUsed = 0;
		bitmapInfoHeader.biClrImportant = 0;
		//�������ݵĴ�С
		//ÿһ�еĴ�С��������4����������
		dwBmBitSize = ((Bitmap.bmWidth*wBitCount + 31) / 32) * 4
			* Bitmap.bmHeight;
		HANDLE hDib = GlobalAlloc(GHND, dwBmBitSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
		pBitmapInfoHeader = (LPBITMAPINFOHEADER)GlobalLock(hDib);
		*pBitmapInfoHeader = bitmapInfoHeader;
		//��ȡ��ɫ�����µ�����ֵ
		{
			HDC hDC;										  //�豸������
			HPALETTE hOldPal = NULL;						  //��ȡ�ɵĵ�ɫ��
			hDC = ::GetDC(NULL);                              //��ȡ��ĻDC
			HANDLE hPal = GetStockObject(DEFAULT_PALETTE);
			if (hPal) {
				hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
				RealizePalette(hDC);
			}
			//��ȡ��ɫ�����µ�����ֵ
			GetDIBits(hDC, hBitmap, 0,
				(UINT)Bitmap.bmHeight,
				(LPSTR)pBitmapInfoHeader + sizeof(BITMAPINFOHEADER) +
				dwPaletteSize,
				(BITMAPINFO *)pBitmapInfoHeader,
				DIB_RGB_COLORS
			);
			if (hOldPal) {                                    //�ָ���ɫ��
				SelectPalette(hDC, hOldPal, TRUE);
				RealizePalette(hDC);
			}
			::ReleaseDC(NULL,hDC);
		}
		//����λͼ��д��
		{
			if (!WriteBmpDataToFile(lpFileName, pBitmapInfoHeader, dwPaletteSize, dwBmBitSize))
			{
				goto _Cleanup;
			}
		}
		bRet = TRUE;
	_Cleanup:
		GlobalUnlock(hDib);
		GlobalFree(hDib);
		return bRet;
	}
	//��ȡλͼ���
	static HBITMAP CopyScreenToBitmap(LPRECT lpRect)
	{
		HDC hScrDC, hMemDC;
		HBITMAP  hBitmap, hOldBitmap;
		int nX, nY, nX2, nY2;
		int nWidth, nHeight;
		int xScrn, yScrn;
		if (IsRectEmpty(lpRect)) {
			return NULL;
		}
		hScrDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		hMemDC = CreateCompatibleDC(hScrDC);//Ϊ��Ļ�����豸�����������ݵ��ڴ��豸������
		//��ȡ����
		nX = lpRect->left;
		nY = lpRect->top;
		nX2 = lpRect->right;
		nY2 = lpRect->bottom;
		//��ȡ��Ļ�ֱ���
		xScrn = GetDeviceCaps(hScrDC, HORZRES);
		yScrn = GetDeviceCaps(hScrDC, VERTRES);
		//ȷ��ѡ�������ǿɿ���
		if (nX < 0) {
			nX = 0;
		}
		if (nY < 0) {
			nY = 0;
		}
		if (nX2 > xScrn) {
			nX2 = xScrn;
		}
		if (nY2 > yScrn) {
			nY2 = yScrn;
		}
		nWidth = nX2 - nX;
		nHeight = nY2 - nY;
		//����һ������Ļ�豸��������ݵ�λͼ
		hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);
		//��ȡ��Ļλͼ�ľ��
		hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
		//���
		DeleteDC(hScrDC);
		DeleteDC(hMemDC);
		//����λͼ���
		return hBitmap;
	}
	//ȫ����ͼ
	static HBITMAP PrintScreen()
	{
		CRect rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = GetSystemMetrics(SM_CXSCREEN);
		rect.bottom = GetSystemMetrics(SM_CYSCREEN);
		return CopyScreenToBitmap(rect);
	}
	//��ȡָ������
	static HBITMAP PrintWindow(HWND hwnd)
	{
		RECT rrrr;
		LPRECT lpRect= &rrrr;
		::GetWindowRect(hwnd, lpRect);
		HDC hScrDC, hMemDC;
		HBITMAP hBitmap, hOldBitmap;
		hScrDC = ::GetWindowDC(hwnd);
		hMemDC = CreateCompatibleDC(hScrDC);
		int nWidth = lpRect->right - lpRect->left;
		int nHeight = lpRect->bottom - lpRect->top;
		//����һ������Ļ�豸��������ݵ�λͼ
		hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
		//���µ�����ѡ���豸��������
		hOldBitmap = (HBITMAP)SelectObject(hScrDC, hBitmap);
		//����Ļ���豸�������Ƶ��ڴ���������
		BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, 0, 0, SRCCOPY);
		hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hScrDC);
		DeleteDC(hMemDC);
		return hBitmap;
	}
	static void DrawMouse(POINT pnt)
	{
		HWND DeskHwnd = ::GetDesktopWindow();             //��ȡ������
		HDC DeskDC = ::GetWindowDC(DeskHwnd);             //��ȡ�����豸���
		int oldRop2 = SetROP2(DeskDC, R2_NOTXORPEN);      
		HPEN newPen = ::CreatePen(0, 1, RGB(255, 0, 0));  //�����»���������DeskDC
		HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);  //ѡ��������������ɵĻ���
		::MoveToEx(DeskDC, pnt.x - 10, pnt.y, NULL);      //�ڴ������ܻ�һ������
		::LineTo(DeskDC, pnt.x + 10, pnt.y);
		::MoveToEx(DeskDC, pnt.x, pnt.y + 10, NULL);
		::LineTo(DeskDC, pnt.x, pnt.y - 10);
		::SetROP2(DeskDC, oldRop2);                    
		::SelectObject(DeskDC, oldPen);                   //�ָ�Ϊ�ɻ���
		::DeleteObject(newPen);
		::ReleaseDC(DeskHwnd, DeskDC);
		DeskDC = NULL;
	}
};