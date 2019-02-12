#pragma once
#include "Shooter.h"
#include "GameTimer.h"
/*
	忍者类
 */
class CShooter0
	:public Shooter
{
public:
	CShooter0();
	virtual ~CShooter0();
	//绘制自己
	virtual void Draw(Gdiplus::Graphics &gh);
	/////////////////////////////////////////
	//处理鼠标消息 需要在子类中处理
	//如果不处理 返回false，
	
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);

	virtual bool OnLButtonUp(UINT nFLags, CPoint point)
	{
		return false;
	}

	virtual bool OnLButtonDlbClk(UINT nFLags, CPoint point)
	{
		return false;
	}

	virtual bool OnRButtonDown(UINT nFlags, CPoint point);

	virtual bool OnRButtonUp(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnRButtonDlbClk(UINT nFlags, CPoint point)
	{
		return false;
	}

	virtual bool OnMouseMove(UINT nFlags, CPoint point)
	{
		return false;
	}
private:
	//当前所处的阶段
	std::vector<Image *> m_vImage;
	typedef enum{
		EStatus0 = 0,
	    EStatusMove0,
	    EStatusMove1,
		EStatusMove2,
		EStatusMove3,
		EStatusMove4,
		EStatusMove5,
		EStatusMove6,
		EStatusMove7,

		EStatusFireLeft,
		EStatusFireRight,
	}EStatus;
	EStatus m_eStatus{ EStatus0 };
	//当前显示的图片
	size_t m_index{ 0 };
	//无动作时候，上下晃动
	CGameTimeVal m_timer0{ 500 };

	//记录当前是向上还是向下
	bool m_bUp{ false };
	/*  向某方向移动
		开始移动
		到达后恢复静止状态
	*/
	void DrawMove(Gdiplus::Graphics &gh);

	//鼠标左键单击的位置
	PointF m_moveTo;

	//移动的方向
	float m_moveDir;

	//开火动画处理
	
	//两帧图画之间的间隔
	CGameTimeVal m_timerFire{ 100 };

	//当前显示第几幅图片
	size_t m_index_fire{ 0 };

	//绘制开火动画
	void DrawFire(Gdiplus::Graphics &gh);

	//鼠标右键单击的位置
	PointF m_fireTo;
};

