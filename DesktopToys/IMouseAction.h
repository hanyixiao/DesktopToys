#pragma once
/*������Ҫ�ṩ��Ӧ���ķ����������ڼ̳и���ӿ�֮��
 *���Ը�����Ҫ�Է���������д��
 */
class IMouseAction
{
public:
	IMouseAction();
	virtual ~IMouseAction();
	////////////////////////////////////////
	////////////////////////////////////////
	///���������Ϣ
	
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) { return false; };
	virtual bool OnLButtonUp(UINT nFlags, CPoint point) { return false; };
	virtual bool OnLButtonDlbClk(UINT nFlags, CPoint point) { return false; };
	virtual bool OnRButtonDown(UINT nFLags, CPoint point) { return false; };
	virtual bool OnRButtonUp(UINT nFlags, CPoint point) { return false; };
	virtual bool OnRButtonDlbClk(UINT nFlags, CPoint point) { return false; };
	virtual bool OnMouseMove(UINT nFlags, CPoint point) { return false; };
};

