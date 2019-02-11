#include "stdafx.h"
#include "Shooter0Mark.h"


CShooter0Mark::CShooter0Mark(float x,float y)
{
	// 载入图片
	m_img.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire Marks 0.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire Marks 1.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire Marks 2.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire Marks 3.png")));
	m_img.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire Marks 4.png")));
	srand(GetTickCount());				// 生成0-5之间的随机数
	m_index = rand() % 5;
	m_dir = Degree2Radian((rand() / 360));

	//设置自己的大小
	RectF rc;
	rc.X = 0;
	rc.Y = 0;
	rc.Width = (float)m_img[0] ->GetWidth();
	rc.Height = (float)m_img[0]->GetHeight();
	SetRect(rc);

	SetCenterPos(x, y);
}


CShooter0Mark::~CShooter0Mark()
{
}

void CShooter0Mark::Draw(Gdiplus::Graphics &gh)
{
	gh.DrawImage(m_img[m_index], GetRect());
}
bool CShooter0Mark::IsChanging() const
{
	return false;
}