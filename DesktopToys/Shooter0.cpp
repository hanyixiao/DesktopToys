#include "stdafx.h"
#include "Shooter0.h"
#include "Shooter0Mark.h"

CShooter0::CShooter0()
{
	//����ͼƬ
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ��.png")));     //0
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ��.png")));     //1
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ����.png")));   //2
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ��.png")));     //3
	m_vImage.push_back(Image::FromFile(   
		TEXT("res/Foton The Desktop Hero ����.png")));   //4
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ��.png")));     //5
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ����.png")));   //6 
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ��.png")));    //7
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero ����.png")));   //8
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Fire Path.png"))); //9
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire 00.png"))); //10
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire 01.png")));  //11
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire 02.png"))); //12
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire 03.png"))); //13
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Left Fire 04.png"))); //14
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Right Fire 00.png"))); //15
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Right Fire 01.png"))); //16
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Right Fire 03.png"))); //17
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Right Fire 04.png")));

	//���ñ���Ĵ�С
	RectF rc;
	rc.Width = (float)m_vImage[0]->GetWidth();
	rc.Height = (float)m_vImage[0]->GetHeight();
	rc.X = 800.0f;
	rc.Y = 600.0f;
	SetRect(rc);
}


CShooter0::~CShooter0()
{
}

void CShooter0::Draw(Gdiplus::Graphics &gh)
{
	switch (m_eStatus) {
		case EStatus0:
		{
			//��ǰ�׶�,�������»ζ�
			m_index = 0;
			//�ж�ʱ��
			if (m_timer0.IsTimeval()) {
				m_bUp = !m_bUp;
				if (m_bUp)
				{
					auto pt = GetCenterPos();
					pt.Y += 1.0f;
					SetCenterPos(pt);
				}
				else {
					//λ�������ƶ�
					auto pt = GetCenterPos();
					pt.Y -= 1.0f;
					SetCenterPos(pt);
				}
			}
			gh.DrawImage(m_vImage[m_index], GetRect());
			break;
		}
		case EStatusMove0:
		{
			m_index = 1 + (EStatusMove0 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}
		case EStatusMove1:
		{
			m_index = 1 + (EStatusMove1 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}
		case EStatusMove2:
		{
			m_index = 1 + (EStatusMove2 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}	
		case EStatusMove3:
		{
			m_index = 1 + (EStatusMove3 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}	
		case EStatusMove4:
		{
			m_index = 1 + (EStatusMove4 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}
		case EStatusMove5:
		{
			m_index = 1 + (EStatusMove5 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}
		case EStatusMove6:
		{
			m_index = 1 + (EStatusMove6 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}
		case EStatusMove7:
		{
			m_index = 1 + (EStatusMove7 - EStatusMove0);
			gh.DrawImage(m_vImage[m_index], GetRect());
			DrawMove(gh);
			break;
		}
		case EStatusFireLeft:
		{
			DrawFire(gh);
			break;
		}
		case EStatusFireRight:
		{
			DrawFire(gh);
			break;
		}
		default:
			break;
	}
}

void CShooter0::DrawMove(Gdiplus::Graphics &gh)
{
	//ֻ����λ�ã�ֱ������Ϊֹ��

	//����������״̬
	if (GetRect().Contains(m_moveTo)) {
		m_eStatus = EStatus0;
		return;
	}
	//�����ƶ�����
	PointF pt = GetCenterPos();
	pt.X += 20.0f*cos(PI(2.0f) - m_moveDir);
	pt.Y += 20.0f*sin(PI(2.0f) - m_moveDir);

	//�������ĵ�λ��
	SetCenterPos(pt);
}

void CShooter0::DrawFire(Gdiplus::Graphics &gh)
{
	switch (m_eStatus) {
		case EStatusFireLeft:
		{
			switch (m_index_fire) {
				case 0:
				{
					auto img = m_vImage[10]; //fire 00
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 1:
				{
					auto img = m_vImage[11]; //fire 00
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 2:
				{
					auto img = m_vImage[12]; //fire 00
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 3:
				{
					auto img = m_vImage[13]; //fire 00
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}

			}
		}
	}
}