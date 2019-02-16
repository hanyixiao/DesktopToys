#pragma once
#include "Shooter.h"
class CShooter3 :
	public Shooter
{
public:
	CShooter3();
	~CShooter3();

	virtual void Draw(Gdiplus::Graphics &gh);
	//////////////////////////
	//////////////////////////
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);

	virtual bool OnLButtonUp(UINT nFlags, CPoint point);

	virtual bool OnLButtonDlbClk(UINT nFlags, CPoint point)
	{
		return false;
	}

	virtual bool OnRButtonDown(UINT nFlags, CPoint point);

	virtual bool OnRButtonUp(UINT nFlags, CPoint point);

	virtual bool OnRButtonDlbClk(UINT nFlags, CPoint point)
	{
		return false;
	}

	virtual bool OnMouseMove(UINT nFlags, CPoint point);
private:
	enum class EStatus{EStatusLeftUp,EStatusLeftDown};
	EStatus m_status{ EStatus::EStatusLeftUp };
	bool m_bRightDown{ 0 };

	//当前的鼠标位置
	PointF m_mousePos{ 0.0f,0.0f };

	//鼠标左键抬起
	std::vector<Image *>m_vImgUp;
	//鼠标左键放下
	std::vector<Image *>m_vImgDown;
};

