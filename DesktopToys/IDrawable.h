#pragma once
/*������Ҫ���ͼ�ε������̳б��࣬��ʵ���Լ���DRAW����
*/
class IDrawable
{
public:
	IDrawable();
	virtual ~IDrawable();
	//�����Լ����������Ի����Լ�
	virtual void Draw(Gdiplus::Graphics &gh) = 0;
	//��ȡ����ķ�Χ
	RectF GetRect()const
	{
		return m_rect;
	};
	void SetRect(RectF rect)
	{
		m_rect = rect;
	};
	//��������Χ
	void SetRect(float x,float y,float width,float height)
	{
		m_rect.X = x;
		m_rect.Y = y;
		m_rect.Width = width;
		m_rect.Height = height;
	};
	//�������ĵ�
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
	//��ȡ���ĵ�λ��
	PointF GetCenterPos()
	{
		PointF pt;
		pt.X = m_rect.X + m_rect.Width / 2.0f;
		pt.Y = m_rect.Y + m_rect.Height / 2.0f;
		return pt;
	}
	//���ô�С
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

