#pragma once
/*该类主要提供响应鼠标的方法，子类在继承该类接口之后
 *可以根据需要对方法进行重写，
 */
class IMouseAction
{
public:
	IMouseAction();
	virtual ~IMouseAction();
	////////////////////////////////////////
	////////////////////////////////////////
	///处理鼠标消息
	
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) { return false; };
	virtual bool OnLButtonUp(UINT nFlags, CPoint point) { return false; };
	virtual bool OnLButtonDlbClk(UINT nFlags, CPoint point) { return false; };
	virtual bool OnRButtonDown(UINT nFLags, CPoint point) { return false; };
	virtual bool OnRButtonUp(UINT nFlags, CPoint point) { return false; };
	virtual bool OnRButtonDlbClk(UINT nFlags, CPoint point) { return false; };
	virtual bool OnMouseMove(UINT nFlags, CPoint point) { return false; };
};

