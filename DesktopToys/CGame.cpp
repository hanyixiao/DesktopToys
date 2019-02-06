#include "stdafx.h"
#include "CGame.h"
#include "SCreenTools.h"

CGame::CGame(HWND hWnd,float x,float y,float w,float h)
	: m_hWnd(hWnd)
	,m_x(x)
	,m_y(y)
	,m_width(w)
	,m_height(h)
{
	//保存全局指针
	g_game = this;
	{
		//截图整个屏幕画在自己的窗口上
		RECT r{ (long)x,(long)y,(long)(x + w),(long)(y + h) };
		HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
		m_imgBK = Bitmap::FromHBITMAP(hBmp, NULL);  //调用GDI图库对背景图进行保存
	}
	//获取窗口大小
	GetClientRect(m_hWnd, &m_rcClient);
}


CGame::~CGame()
{
}

//游戏的一帧
bool CGame::EnterFrame(DWORD dwTime)
{
	Draw();
	return false;
}
 
//鼠标左键按下
void CGame::OnLButtonDown(UINT Flags, CPoint point)
{
	switch(m_eStatus)    //声明并初始化
	{
		case CGame::EGameStatusSelect: {
			//菜单处理阶段
			break;
		}
		case CGame::EGamestatusNormal: {
			//游戏阶段
			break;
		}
		default: {
			break;
		}

	}
}
//鼠标左键抬起
void CGame::OnLButtonUp(UINT Flags, CPoint point)
{
	switch (m_eStatus) {
		case CGame::EGameStatusSelect: {
			//菜单阶段
			break;
		}
		case CGame::EGamestatusNormal: {
			//游戏阶段
			break;
		}
		default: {
			break;
		}
	}
}
//鼠标左键双击
void CGame::OnLButtonDblClk(UINT Flags, CPoint point)
{
   
}
//鼠标右键按下
void CGame::OnRButtonDown(UINT Flags, CPoint point)
{
	switch (m_eStatus)    //声明并初始化
	{
		case CGame::EGameStatusSelect: {
			//菜单处理阶段
			break;
		}
		case CGame::EGamestatusNormal: {
			//游戏阶段
			break;
		}
		default: {
			break;
		}

	}
}
//鼠标右键键抬起
void CGame::OnRButtonUp(UINT Flags, CPoint point)
{
	switch (m_eStatus) {
		case CGame::EGameStatusSelect: {
			//菜单阶段
			break;
		}
		case CGame::EGamestatusNormal: {
			//游戏阶段
			break;
		}
		default: {
			break;
		}
	}
}
void CGame::OnRButtonDlbClk(UINT Flags, CPoint point)
{

}
//鼠标移动
void CGame::OnMouseMove(UINT Flags, CPoint point)
{
	switch (m_eStatus) {
		case CGame::EGameStatusSelect: {
			break;
		}
		case CGame::EGamestatusNormal: {
			break;
		}
		default: {
			break;
		}
	}
}
//按下eSC键时的处理
BOOL CGame::OnESC()
{
	switch (m_eStatus) {
		case CGame::EGameStatusSelect: {
			//当前没在游戏，不处理
			return FALSE;
		}
		case CGame::EGamestatusNormal: {
			m_eStatus = EGameStatusSelect;
			//显示鼠标
			{
				//初始状态，计数是0，所以保证不是0就可以显示了
				int i = ShowCursor(TRUE);
				if (i > 0) {
					//减小到0
					while (ShowCursor(FALSE) > 0) {
						;
					}
				}
				else if (i < 0) {
					while (ShowCursor(TRUE) < 0) {
						;
					}
				}

			}
			return TRUE;
		}						   
	default:
		break;
	}
	return FALSE;

}
void CGame::Draw()
{
	HDC hdc = ::GetDC(m_hWnd);
	ON_SCOPE_EXIT([&](){				  //离开函数作用域时，释放DC
		::ReleaseDC(m_hWnd, hdc);
	});
	CDC *dc = CClientDC::FromHandle(hdc); //临时指针
	//双缓冲绘图
	CDC m_dcMemory;						  //内存DC
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, m_rcClient.Width(), m_rcClient.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp); //选入DC
	
	Graphics gh(m_dcMemory.GetSafeHdc());  //构造对象
	gh.SetPageUnit(Gdiplus::UnitPixel);    //设置单位
										   //清除背景
	Color clr;
	clr.SetFromCOLORREF(BACK_GROUND_LAYER);
	gh.Clear(clr);
	gh.ResetClip();
	//根据当前游戏的阶段，绘制不同的东西
	{
		switch (m_eStatus) {
			case CGame::EGameStatusSelect: {
				break;
			}
			case CGame::EGamestatusNormal: {
				break;
			}
			default:
				break;
		}
	}
	DrawFps(gh);						 //画出帧数
	::BitBlt(hdc, 0, 0, m_rcClient.Width(),
		m_rcClient.Height(), m_dcMemory.GetSafeHdc(),
		0, 0, SRCCOPY);                 //复制到屏幕
	return;

}
//画帧数
void CGame::DrawFps(Gdiplus::Graphics &gh) 
{
	static int fps = 0;							//记录当前帧数
	m_fps++;									//每帧加一
	static DWORD dwLast = GetTickCount();		//最后一次输出的时间间隔
	if (GetTickCount() - dwLast >= 1000) {      // 如果超过一秒则输出帧数
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();
	}
	//输出fps
	{
		//输出文字
		CString s;
		s.Format(TEXT("FPS:%d"), fps);
		gh.DrawString(s.GetString(), -1, &m_font, origin,&m_brush);
	}


}