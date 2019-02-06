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
	//����ȫ��ָ��
	g_game = this;
	{
		//��ͼ������Ļ�����Լ��Ĵ�����
		RECT r{ (long)x,(long)y,(long)(x + w),(long)(y + h) };
		HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
		m_imgBK = Bitmap::FromHBITMAP(hBmp, NULL);  //����GDIͼ��Ա���ͼ���б���
	}
	//��ȡ���ڴ�С
	GetClientRect(m_hWnd, &m_rcClient);
}


CGame::~CGame()
{
}

//��Ϸ��һ֡
bool CGame::EnterFrame(DWORD dwTime)
{
	Draw();
	return false;
}
 
//����������
void CGame::OnLButtonDown(UINT Flags, CPoint point)
{
	switch(m_eStatus)    //��������ʼ��
	{
		case CGame::EGameStatusSelect: {
			//�˵�����׶�
			break;
		}
		case CGame::EGamestatusNormal: {
			//��Ϸ�׶�
			break;
		}
		default: {
			break;
		}

	}
}
//������̧��
void CGame::OnLButtonUp(UINT Flags, CPoint point)
{
	switch (m_eStatus) {
		case CGame::EGameStatusSelect: {
			//�˵��׶�
			break;
		}
		case CGame::EGamestatusNormal: {
			//��Ϸ�׶�
			break;
		}
		default: {
			break;
		}
	}
}
//������˫��
void CGame::OnLButtonDblClk(UINT Flags, CPoint point)
{
   
}
//����Ҽ�����
void CGame::OnRButtonDown(UINT Flags, CPoint point)
{
	switch (m_eStatus)    //��������ʼ��
	{
		case CGame::EGameStatusSelect: {
			//�˵�����׶�
			break;
		}
		case CGame::EGamestatusNormal: {
			//��Ϸ�׶�
			break;
		}
		default: {
			break;
		}

	}
}
//����Ҽ���̧��
void CGame::OnRButtonUp(UINT Flags, CPoint point)
{
	switch (m_eStatus) {
		case CGame::EGameStatusSelect: {
			//�˵��׶�
			break;
		}
		case CGame::EGamestatusNormal: {
			//��Ϸ�׶�
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
//����ƶ�
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
//����eSC��ʱ�Ĵ���
BOOL CGame::OnESC()
{
	switch (m_eStatus) {
		case CGame::EGameStatusSelect: {
			//��ǰû����Ϸ��������
			return FALSE;
		}
		case CGame::EGamestatusNormal: {
			m_eStatus = EGameStatusSelect;
			//��ʾ���
			{
				//��ʼ״̬��������0�����Ա�֤����0�Ϳ�����ʾ��
				int i = ShowCursor(TRUE);
				if (i > 0) {
					//��С��0
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
	ON_SCOPE_EXIT([&](){				  //�뿪����������ʱ���ͷ�DC
		::ReleaseDC(m_hWnd, hdc);
	});
	CDC *dc = CClientDC::FromHandle(hdc); //��ʱָ��
	//˫�����ͼ
	CDC m_dcMemory;						  //�ڴ�DC
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, m_rcClient.Width(), m_rcClient.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp); //ѡ��DC
	
	Graphics gh(m_dcMemory.GetSafeHdc());  //�������
	gh.SetPageUnit(Gdiplus::UnitPixel);    //���õ�λ
										   //�������
	Color clr;
	clr.SetFromCOLORREF(BACK_GROUND_LAYER);
	gh.Clear(clr);
	gh.ResetClip();
	//���ݵ�ǰ��Ϸ�Ľ׶Σ����Ʋ�ͬ�Ķ���
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
	DrawFps(gh);						 //����֡��
	::BitBlt(hdc, 0, 0, m_rcClient.Width(),
		m_rcClient.Height(), m_dcMemory.GetSafeHdc(),
		0, 0, SRCCOPY);                 //���Ƶ���Ļ
	return;

}
//��֡��
void CGame::DrawFps(Gdiplus::Graphics &gh) 
{
	static int fps = 0;							//��¼��ǰ֡��
	m_fps++;									//ÿ֡��һ
	static DWORD dwLast = GetTickCount();		//���һ�������ʱ����
	if (GetTickCount() - dwLast >= 1000) {      // �������һ�������֡��
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();
	}
	//���fps
	{
		//�������
		CString s;
		s.Format(TEXT("FPS:%d"), fps);
		gh.DrawString(s.GetString(), -1, &m_font, origin,&m_brush);
	}


}