#pragma once
#include "IMark.h"
/*
	�����ڴ��������µĺۼ�
*/
class CShooter2Mark
	:public IMark
{
public:
	CShooter2Mark(float x,float y);
	virtual ~CShooter2Mark();
	
	virtual void Draw(Gdiplus::Graphics &gh);

	virtual bool IsChanging()const;
private:
	Image *m_img;

	typedef struct {
		Image *m_img2;
		
		PointF m_pos;

		PointF m_speed{ 10.0f,10.0f };

		float m_dir{ 0.0f };

		bool m_bShow{ true };
	}SDynamic;
	//��̬���µ�����
	std::vector<SDynamic> m_vD;
};

