#pragma once
#include "IDrawable.h"
#include "IMouseAction.h"
/*
	选择工具的菜单项
*/
class CMenuItem
	: public IDrawable
	, public IMouseAction
{
public:
	CMenuItem();
	CMenuItem(float x, float y, PCTSTR szImg, PCTSTR szTips);

	virtual ~CMenuItem();

	//根据自己的属性画自己
	virtual void Draw(Gdiplus::Graphics &gh);
	///////////////////////////////////////////////////
	//			处理鼠标消息                           //
	///////////////////////////////////////////////////
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);

	virtual bool OnRButtonDown(UINT nFlags, CPoint point);

	virtual bool OnMouseMove(UINT nFlags, CPoint point);

	//开始播放动画
	void StartAnimate();
	//设置动画信息:飞出，散步在四周
	void InitAnimateInfo0(float x, float y, float dir);
	//设置动画信息，以中心点翻转
	void InitAnimateInfo1(float x, float y, float dir);
	//设置动画信息，以中心点做翻转，逆向翻转
	void InitAnimateInfoReverse();
	//设置动画信息：什么也不干
	void InitAnimateInfo3(float x, float y);

	//停止播放动画，直接跳转到最后
	void EndAnimate()
	{
		m_indexAnimate = m_vAnimateInfo.size();
	}
	//动画是否播放完毕
	bool IsAnimateEnd()const
	{
		return m_indexAnimate != 0 && m_indexAnimate >= m_vAnimateInfo.size();
	 }
private:
	Image *m_img{ nullptr };
	//初始大小
	SizeF m_sizeInit;
	//动画相关信息
	typedef struct {
		SizeF size;
		PointF pos;
	 }SAnimateInfo;
	std::vector<SAnimateInfo> m_vAnimateInfo;
	//当前在第几帧的位置
	size_t m_indexAnimate;
	bool m_bAnimate{ false };
	bool m_bAnimate2{ false };
};

