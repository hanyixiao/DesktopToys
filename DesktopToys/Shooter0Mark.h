#pragma once
#include "IMark.h"
/*
	�����ڴ��������µ�ӡ��
*/
class CShooter0Mark
	:public IMark
{
public:
	CShooter0Mark(float x,float y);

	virtual ~CShooter0Mark();

	//���Լ�
	virtual void Draw(Gdiplus::Graphics &gh);
	//״̬�Ƿ��ڸı���
	virtual bool IsChanging() const;
private:
	std::vector < Image *>m_img;           //ͼƬ
	size_t m_index{ 0 };
	float m_dir;						   //��ת�ĽǶ�
	
};

