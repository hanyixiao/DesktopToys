#pragma once
/*所有需要输出图形的类必须继承本类，并实现自己的DRAW方法
*/
class IDrawable
{
public:
	IDrawable();
	virtual ~IDrawable();
	//根据自己的需求属性绘制自己
	virtual void Draw(Gdiplus::Graphics &gh) = 0;
	//获取自身的范围
	RectF GetRect()const
	{
		return m_rect;
	};
	void SetRect(RectF rect)
	{
		m_rect = rect;
	};
	//设置自身范围
	void SetRect(float x,float y,float width,float height)
	{
		m_rect.X = x;
		m_rect.Y = y;
		m_rect.Width = width;
		m_rect.Height = height;
	};
	//设置中心点
	void SetCenterPos(float x, float y)
	{
		PointF ptCenter(x, y);
		SetCenterPos(ptCenter);
	};
	void SetCenterPos(PointF &ptcenter)
	{
		RectF r = m_rect;
		r.X = ptcenter.X - r.Width / 2.0f;
		r.Y = ptcenter.Y - r.Height / 2.0f;
		SetRect(r);
	};
	//获取中心点位置
	PointF GetCenterPos()
	{
		PointF pt;
		pt.X = m_rect.X + m_rect.Width / 2.0f;
		pt.Y = m_rect.Y + m_rect.Height / 2.0f;
		return pt;
	}
	//设置大小
	void SetSize(float w, float h)
	{
		PointF ptCenter = GetCenterPos();
		RectF rr = m_rect;
		rr.Width = w;
		rr.Height = h;
		SetRect(rr);
		SetCenterPos(ptCenter);
	}
protected:
	RectF m_rect;
};

