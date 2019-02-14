#include "stdafx.h"
#include "Shooter0.h"
#include "Shooter0Mark.h"

CShooter0::CShooter0()
{
	//载入图片
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 静.png")));     //0
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 右.png")));     //1
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 右上.png")));   //2
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 上.png")));     //3
	m_vImage.push_back(Image::FromFile(   
		TEXT("res/Foton The Desktop Hero 左上.png")));   //4
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 左.png")));     //5
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 左下.png")));   //6 
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 下.png")));    //7
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero 右下.png")));   //8
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
		TEXT("res/Foton The Desktop Hero Right Fire 02.png"))); //17
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Right Fire 03.png"))); //18
	m_vImage.push_back(Image::FromFile(
		TEXT("res/Foton The Desktop Hero Right Fire 04.png"))); //19

	//设置本类的大小
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
			//当前阶段,机器上下晃动
			m_index = 0;
			//判断时间
			if (m_timer0.IsTimeval()) {
				m_bUp = !m_bUp;
				if (m_bUp)
				{
					auto pt = GetCenterPos();
					pt.Y += 1.0f;
					SetCenterPos(pt);
				}
				else {
					//位置向下移动
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
	//只更新位置，直道到达为止，

	//如果到达，更新状态
	if (GetRect().Contains(m_moveTo)) {
		m_eStatus = EStatus0;
		return;
	}
	//否则移动忍者
	PointF pt = GetCenterPos();
	pt.X += 20.0f*cos(PI(2.0f) - m_moveDir);
	pt.Y += 20.0f*sin(PI(2.0f) - m_moveDir);

	//设置中心点位置
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
				case 3:                      //发射子弹//???????
				{
					g_game->Append(std::make_shared<CShooter0Mark>(
						m_fireTo.X, GetRect().Y));
					//此处没有break;
				}
				case 4:
				{
					const float Y = GetRect().Y;
					const float X = GetRect().X;
					const float YY = Y;
					const float XX = m_fireTo.X + 30.0f;

					//画忍者的身体，动作
					{
						auto img = m_vImage[13];
						gh.DrawImage(img, X, Y);
					}

					//画激光中间的部分
					{
						auto img = m_vImage[9];
						float left = X + 52;
						//拼接图片进行输出，因为中间部分长度不确定，不能确定图片的长度
						while (left >= (XX + 60.f))
						{
							gh.DrawImage(img, left, Y, (float)img->GetWidth(),
								(float)img->GetHeight());
							left -= (-2.0f + (float)img->GetWidth());
						}

					}
					//画击中部分
					{
						//这个要根据鼠标左键绘图
						auto img = m_vImage[14];
						gh.DrawImage(img, XX, Y); 
					}
					break;
				}

				case 5:
				{
					auto img = m_vImage[10];
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 6:
				{
					m_eStatus = EStatus0;
					return;
				}
				default:
					break;

			}
			break;
		
		}
		case EStatusFireRight:
		{
			switch (m_index_fire) {
				case 0:
				{
					auto img = m_vImage[15]; //fire 00
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 1:
				{
					auto img = m_vImage[16]; //fire 00
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 2:
				{
					auto img = m_vImage[17]; //fire 00
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 3:                      //发射子弹//???????
				{
					g_game->Append(std::make_shared<CShooter0Mark>(
						m_fireTo.X, GetRect().Y));
					//此处没有break;
				}
				case 4:
				{
					const float Y = GetRect().Y;
					const float X = GetRect().X;
					const float YY = Y;
					const float XX = m_fireTo.X -m_vImage[19]->GetWidth()
						+ 30.0f;

					//画忍者的身体，动作
					{
						auto img = m_vImage[18];
						gh.DrawImage(img, X, Y,
							(float)m_vImage[18]->GetWidth(),
							(float)m_vImage[18]->GetHeight());
					}

					//画激光中间的部分
					{
						auto img = m_vImage[9];
						float left = X + 50;
						//拼接图片进行输出，因为中间部分长度不确定，不能确定图片的长度
						while (left <= (XX))
						{
							gh.DrawImage(img, left, Y+4, (float)img->GetWidth(),
								(float)img->GetHeight());
							left += (-2.0f + (float)img->GetWidth());
						}

					}
					//画击中部分
					{
						//这个要根据鼠标左键绘图
						auto img = m_vImage[19];
						gh.DrawImage(img, XX, Y,
							(float)m_vImage[19]->GetWidth(),
							(float)m_vImage[19]->GetHeight());
					}
					break;
				}

				case 5:
				{
					auto img = m_vImage[15];
					RectF r = GetRect();
					r.Width = (float)img->GetWidth();
					r.Height = (float)img->GetHeight();
					gh.DrawImage(img, r);
					break;
				}
				case 6:
				{
					m_eStatus = EStatus0;
					return;
				}
				default:
					break;

				}
			break;
			
		}
		
		default:
			break;
	}
	//判断状态
	if (m_timerFire.IsTimeval()) {//若果时间间隔达到，才进行状态切换的操作
		int times = m_timerFire.GetTimes();
		if (times > 6) {
			m_index_fire = 6;
		}
		else if (times > 5) {
			m_index_fire = 5;
		}
		else if (times > 4) {
			m_index_fire = 4;
		}
		else if (times > 3) {
			m_index_fire = 3;
		}
		else if (times > 2) {
			m_index_fire = 2;
		}
		else if (times > 1) {
			m_index_fire = 1;
		}
		else if (times > 0) {
			m_index_fire = 0;
		}
	}
}
bool CShooter0::OnLButtonDown(UINT nFlags, CPoint point)
{
	PointF ptCenter = GetCenterPos();
	PointF ptDest(static_cast<float>(point.x),
		static_cast<float>(point.y));
	//记录移动的目的地
	m_moveTo = ptDest;
	//计算夹角
	float theta = std::atan2<float>(-(ptDest.Y - ptCenter.Y),
		ptDest.X - ptCenter.X);
	if (theta < 0.0f) {
		theta = (PI(2.0f) + theta);
	}
	//记录移动的方向
	m_moveDir = theta;

	//平面坐标系被分成八份，当角度落在某个区间时，分别处理
	float a_per = PI(2.0f / 8.0f);
	float a_per_half = (a_per / 2.0f);
	float a_start = -a_per_half;
	int i = 0;
	for (; i < 7; ++i)
	{
		float min = a_start + i * a_per;
		float max = a_start + (i + 1)*a_per;
		if (min<theta&&max>theta) {
			//设置成当前状态
			m_eStatus = (EStatus)(i + EStatusMove0);
			break;
		}
	}
	//直接落入第8个状态
	if (i == 7)
	{
		//设置当前状态
		m_eStatus = (EStatus)(i + EStatusMove0);
		return true;
	}
	return true;
}

bool CShooter0::OnRButtonDown(UINT nFlags, CPoint point)
{
	PointF ptCenter = GetCenterPos();
	//单击位置
	PointF ptDest(static_cast<float>(point.x),
		static_cast<float>(point.y));
	
	//记录鼠标单击位置，也就是开火的地方
	m_fireTo = ptDest;

	//向右开火
	if (ptDest.X > ptCenter.X) {
		m_eStatus = EStatusFireRight;
	}
	//向左开火
	else {
		m_eStatus = EStatusFireLeft;
	}
	//重新开始计时
	m_timerFire.Restart();
	//重置帧序列号
	m_index_fire = 0;

	return true;
}