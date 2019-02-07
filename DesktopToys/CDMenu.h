#pragma once
#include "MenuItem.h"
#include "IMouseAction.h"
#include "IDrawable.h"
class CDMenu
	:public IDrawable
	,public IMouseAction
{
public:
	CDMenu(HWND hWnd);
	virtual ~CDMenu();

	//重新初始化各个菜单子项的位置信息
	void InitAnimateInfo0();

	//根据当前的属性绘制自己
	virtual void Draw(Gdiplus::Graphics &gh);

	///////////////////////////////////////
	//处理鼠标消息
	//如果不处理，返回false,父类可以根据判断是否进行处理
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	
	virtual bool OnMouseMove(UINT nFLags, CPoint point);
private:
	HWND m_hWnd;
	//菜单子项
	//盒子
	std::shared_ptr<CMenuItem> m_box;
	//盒盖1：打开
	std::shared_ptr<CMenuItem> m_cover;
	//盒盖2：关闭
	std::shared_ptr<CMenuItem> m_cover2;
	//选项
	std::shared_ptr<CMenuItem> m_item0;
	std::shared_ptr<CMenuItem> m_item1;
	std::shared_ptr<CMenuItem> m_item2;
	std::shared_ptr<CMenuItem> m_item3;

	//结束动画播放
	void EndAnimate();

	typedef enum {
		EStatusOverCover1,
		EStatusItem0,                       //播放动画
		EStatusItem1,
		EStatusItem2,
		EStatusItem3,
		EStatusOverCover2,                  //播放关盒子的动画
		EStatusAll
	}EStatus;
	EStatus m_eStatus{ EStatusOverCover1 };
};

