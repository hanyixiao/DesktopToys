#include "stdafx.h"
#include "CShooter2.h"
#include "CShooter2Mark.h"

CShooter2::CShooter2()
{
	//载入图片
	m_img0 = Image::FromFile(TEXT("res/The Toolbox01.png"));
	m_img1 = Image::FromFile(TEXT("res/The Toolbox02.png"));
	m_img2 = Image::FromFile(TEXT("res/The Toolbox03.png"));
}


CShooter2::~CShooter2()
{
}

void DrawImageRotate(PointF mousePt, Graphics &gh,
	Image *img, float degree)
{
	//旋转绘图平面
	PointF center = mousePt;
	center.X += img->GetWidth() / 2.0f;
	center.Y += img->GetHeight() / 2.0f;

	//1平移变化移动原点位置到坐标点
	gh.TranslateTransform(center.X, center.Y);
	//2.旋转变换:使坐标轴旋转degree度
	gh.RotateTransform(degree);
	//3.恢复原点
	gh.TranslateTransform(-center.X, -center.Y);

	//方法退出时恢复对坐标系统和平移的转换
	ON_SCOPE_EXIT([&]() {
		//1平移变化移动原点位置到坐标点
		gh.TranslateTransform(center.X, center.Y);
		//2.旋转变换:使坐标轴旋转degree度
		gh.RotateTransform(degree);
		//3.恢复原点
		gh.TranslateTransform(-center.X, -center.Y);
	});

	{
		RectF rc;
		rc.X = mousePt.X;
		rc.Y = mousePt.Y;
		rc.Width = (float)img->GetWidth();
		rc.Height = (float)img->GetHeight();
		gh.DrawImage(img, rc);
	}
	//画出图像

}
void CShooter2::Draw(Gdiplus::Graphics &gh)
{
	switch (m_status) {
		//锤子
		case EStatus::EStatusHammer: {
			switch (m_eStatusHammer) {
				//鼠标左键第一次单击：发射子弹，同时锤子图片发生变化
				case EStatusHammer::EStatusHammerDownFirst: {
					g_game->Append(std::make_shared<CShooter2Mark>
						(m_mousePos.X, m_mousePos.Y));
					m_eStatusHammer = EStatusHammer::EStatusHammerDown;
				}
				//鼠标左键单击
				case EStatusHammer::EStatusHammerDown: {
					auto img = m_img1;
					RectF rc;
					rc.X = m_mousePos.X;
					rc.Y = m_mousePos.Y;
					rc.Width = (float)img->GetWidth();
					rc.Height =(float) img->GetHeight();
					gh.DrawImage(img, rc);
					break;
				}
				//鼠标左键抬起
				case EStatusHammer::EStatusHammerUp: {
					auto img = m_img2;
					RectF rc;
					rc.X = m_mousePos.X;
					rc.Y = m_mousePos.Y;
					rc.Width = (float)img->GetWidth();
					rc.Height = (float)img->GetHeight();
					gh.DrawImage(img, rc);
					break;
				}
				default:
					break;
			}

			break;
				}
		default:
			break;
	}

}
////////////////////////////
/**************************/
bool CShooter2::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch (m_status) {
		case EStatus::EStatusHammer: {
			//锤子砸下
			m_eStatusHammer = EStatusHammer::EStatusHammerDownFirst;
			break;
		}
		case EStatus::EStatusSaw: {
			//电锯开始割东西
			m_eStatusSaw = EStatusSaw::EStatusSawStart;
			//当前位置
			m_sawPos = m_mousePos;
			break;
		}
		default:
			break;
	}
	return false;
}
//鼠标左键抬起
bool CShooter2::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (m_status) {
		case EStatus::EStatusHammer: {
			//锤子抬起
			m_eStatusHammer = EStatusHammer::EStatusHammerUp;
			break;
		}
		case EStatus::EStatusSaw: {
			//电锯
			m_eStatusSaw = EStatusSaw::EStatusSawStop;
			break;
		}
		default:
			break;
		}
	return false;
}

bool CShooter2::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_status = EStatus::EStatusHammer;
	return true;
}

//计算两点之间的距离
float distance(PointF pt1, PointF pt2)
{
	return std::sqrt(std::pow(pt1.X - pt2.X,2) + 
		std::pow(pt1.Y - pt2.Y,2));

}
//
bool CShooter2::OnMouseMove(UINT nFlags, CPoint point)
{
	m_mousePos.X = (float)point.x;
	m_mousePos.Y = (float)point.y;

	//根据不同情况进行处理
	switch (m_status) {
		case EStatus::EStatusHammer: {
		    //锤子维持原来的状态
			break;
		}
		case EStatus::EStatusSaw: {
			//如果没有东西可依据时候，change the dir
			if (m_eStatusSaw == EStatusSaw::EStatusSawStop) {
				m_sawPos = m_mousePos;
				// change the direction
				if (distance(m_mousePosLast, m_mousePos) > 10) {
					//caculate the angle
					float theta = (atan2(m_mousePos.Y - m_mousePosLast.Y,
						m_mousePos.X-m_mousePos.X));
					if (theta < 0.0f) {
						theta = PI(2.0f) + theta;
					}
					//angle ：degree per 
					m_sawDegree = Radian2Degree(theta);
					//记住这次的位置
					m_mousePosLast = m_mousePos;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return true;
}