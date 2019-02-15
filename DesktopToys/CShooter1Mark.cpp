#include "stdafx.h"
#include "CShooter1Mark.h"


CShooter1Mark::CShooter1Mark(float x, float y, int index )
{
	//载入图片
	m_img.push_back(Image::FromFile(
		TEXT("res/Pablo The Painter Mark 0.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Pablo The Painter Mark 1.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Pablo The Painter Mark 2.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Pablo The Painter Mark 3.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Pablo The Painter Mark 4.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Pablo The Painter Mark 5.png")));
	m_index = index;

	//设置大小
	RectF rc;
	rc.X = 0;
	rc.Y = 0;
	rc.Width =(float) m_img[0]->GetWidth();
	rc.Height = (float)m_img[0]->GetHeight();
	SetRect(rc);

	//设置中心点
	SetCenterPos(x, y);
}



CShooter1Mark::~CShooter1Mark()
{
}

void CShooter1Mark::Draw(Gdiplus::Graphics &gh)
{
	gh.DrawImage(m_img[m_index], GetRect());
}
bool CShooter1Mark::IsChanging() const
{
	return  false;
}