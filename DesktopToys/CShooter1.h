#pragma once
#include "Shooter.h"
class CShooter1
	:public Shooter
{
public:
	CShooter1(int height);
	virtual ~CShooter1();
	virtual void Draw(Gdiplus::Graphics &gh);

	///////////////////////////////////////
	//���������Ϣ
	//
	////////////////////////////////////////
	virtual bool OnLButtonDown(UINT nFLags, CPoint point);
	virtual bool OnLButtonUp(UINT nFLags, CPoint point);
	virtual bool OnLButtonDlbClk(UINT nFLags, CPoint point)
	{
		return false;
	}
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	virtual bool OnRButtonUp(UINT nFLags, CPoint point)
	{
		return false;
	}
	virtual bool OnRButtonDlbClk(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
private:
	int m_nHeight{ 0 };

	//0:���ӣ�1���ң�2���һ�ͷ��������������
	int m_status{ 1 };
	//ǰһ�ε�״̬
	int m_statusLast{ 1 };
	
	//��ǰ������ڵ�λ��
	PointF m_mousePos{ 0.0f,0.0f };

	//��һ��������ڵ�λ��
	PointF m_mousePosLast{ 0.0f,0.0f };

	//��������ƶ�������Ҳ�����ƶ�
	//��¼�ϴλ���ʱ��λ�ú;���
	PointF m_lastChangePos{ 0.0f,0.0f };

	//�仯�ľ���
	const float m_distanceChange{ 23.0f };

	//��¼��ǰ����ɫ
	int m_iColorIndex{ 0 };

	//���ӵ�ͼƬ
	Image *m_img0;
	Image *m_img1;
	Image *m_img2;
	Image *m_img3;
	Image *m_img4;
	//��ͼ
	Image *m_img5;
};

