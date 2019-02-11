#pragma once
#include "Shooter.h" 
#include "CDMenu.h"
class IMark; //��ǰ��������Ϊ����Ҫ�õ��ýӿ����͵�ָ��
class CGame
{
public:
	/*���캯����
	 *hWnd����Ϸ����
	 *x,y��λ��
	 *w,h:���ڿ��
	 */
	CGame(HWND hWnd,float x,float y,float w,float h);
	~CGame();
public:
	//��Ϸ��ÿһ֡
	bool EnterFrame(DWORD dwTime);
	//���������Ϣ
	//����������
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	//������˫��
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDlbClk(UINT nFlags, CPoint point);
	//����ƶ�
	void OnMouseMove(UINT nFlags, CPoint point);
	//����ESC�����ĺ�����Ӧ
	BOOL OnESC();
	//����һ���ƻ���
	void Append(std::shared_ptr<IMark> pMark)
	{
		m_vMarks.push_back(pMark);
	}
	//��ȡ��Ϸ���ڵĿ��
	float GetWidth()const
	{
		return m_width;
	}
	//��ȡ��Ϸ���ڵĸ߶�
	float GetHeight()const
	{
		return m_height;
	}
	//��ȡ��Χ
	RectF GetRectF()const
	{
		return RectF(m_x, m_y, m_width, m_height);
	}
private:
	HWND m_hWnd;
	//���ڵ���ʼλ��
	float m_x;
	float m_y;

	//��Ϸ���ڵĿ�Ⱥ͸߶�
	float m_width;
	float m_height;
	//��Ϸ�׶�
	//��Ϸֻ��Ϊ�����׶Σ��˵��׶κ���Ϸ�׶�
	typedef enum EGameStatus {EGameStatusSelect,EGamestatusNormal}EGameStatus;
	EGameStatus m_eStatus{ EGameStatusSelect };//��������ʼ��
private:
	//�ͻ�����С
	CRect m_rcClient;

	//��¼��Ϸ�ж���֡
	int m_fps{ 0 };
	//���FPS���ֵĻ�ˢ
	SolidBrush m_brush{ Color{254,0xFF,0x00,0x00} };
	//���FPS����������
	Gdiplus::Font m_font{ L"����",10.0 };
	//�����Ͻ���ʾ
	PointF origin{ 0.0f,0.0f };
	//�����ж���
	void Draw();
	//���pfs
	void DrawFps(Gdiplus::Graphics &gh);
	//�ƻ��������µĶ���
	std::vector<std::shared_ptr<IMark>> m_vMarks;
	//����ͼ
	Gdiplus::Bitmap *m_imgBK;
	//�˵��͹�����
	std::shared_ptr<CDMenu> m_menu;
	std::shared_ptr<Shooter> m_pTool;
};