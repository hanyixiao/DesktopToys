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
	//处理鼠标消息
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

	//0:梯子，1：右，2，右回头。。。。。。。
	int m_status{ 1 };
	//前一次的状态
	int m_statusLast{ 1 };
	
	//当前鼠标所在的位置
	PointF m_mousePos{ 0.0f,0.0f };

	//上一次鼠标所在的位置
	PointF m_mousePosLast{ 0.0f,0.0f };

	//鼠标上下移动，忍者也跟着移动
	//记录上次换腿时的位置和距离
	PointF m_lastChangePos{ 0.0f,0.0f };

	//变化的距离
	const float m_distanceChange{ 23.0f };

	//记录当前的颜色
	int m_iColorIndex{ 0 };

	//梯子的图片
	Image *m_img0;
	Image *m_img1;
	Image *m_img2;
	Image *m_img3;
	Image *m_img4;
	//绘图
	Image *m_img5;
};

