#pragma once
#include "Shooter.h"
#include "GameTimer.h"
/*
	������
 */
class CShooter0
	:public Shooter
{
public:
	CShooter0();
	virtual ~CShooter0();
	//�����Լ�
	virtual void Draw(Gdiplus::Graphics &gh);
	/////////////////////////////////////////
	//���������Ϣ ��Ҫ�������д���
	//��������� ����false��
	
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
	//��ǰ�����Ľ׶�
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
	//��ǰ��ʾ��ͼƬ
	size_t m_index{ 0 };
	//�޶���ʱ�����»ζ�
	CGameTimeVal m_timer0{ 500 };

	//��¼��ǰ�����ϻ�������
	bool m_bUp{ false };
	/*  ��ĳ�����ƶ�
		��ʼ�ƶ�
		�����ָ���ֹ״̬
	*/
	void DrawMove(Gdiplus::Graphics &gh);

	//������������λ��
	PointF m_moveTo;

	//�ƶ��ķ���
	float m_moveDir;

	//���𶯻�����
	
	//��֡ͼ��֮��ļ��
	CGameTimeVal m_timerFire{ 100 };

	//��ǰ��ʾ�ڼ���ͼƬ
	size_t m_index_fire{ 0 };

	//���ƿ��𶯻�
	void DrawFire(Gdiplus::Graphics &gh);

	//����Ҽ�������λ��
	PointF m_fireTo;
};

