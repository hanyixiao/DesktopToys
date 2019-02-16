#include "stdafx.h"
#include "CShooter3.h"
#include "GameTimer.h"
#include "CShooter3Mark.h"

CShooter3::CShooter3()
{
	m_vImgUp.push_back(Image::FromFile(TEXT("res/Eraser Ed 0.png")));
	m_vImgUp.push_back(Image::FromFile(TEXT("res/Eraser Ed 1.png")));
	m_vImgUp.push_back(Image::FromFile(TEXT("res/Eraser Ed 2.png")));
	m_vImgDown.push_back(Image::FromFile(TEXT("res/Eraser Ed 00.png")));
	m_vImgDown.push_back(Image::FromFile(TEXT("res/Eraser Ed 01.png")));
}


CShooter3::~CShooter3()
{
}

//根据自己的当前的属性绘制自己
void CShooter3::Draw(Gdiplus::Graphics &gh)
{
	switch (m_status) {
		case EStatus::EStatusLeftUp: {
			if (!m_bRightDown) {
				//反复显示三张照片:眨眼
				static size_t index = 0;
				if (index >= 3) {
					index = 0;
				}
				//画当前的图片
				{
					auto img = m_vImgUp[index];
					RectF rc;
					rc.X = m_mousePos.X;
					rc.Y = m_mousePos.Y;
					rc.Width = (float)img->GetWidth();
					rc.Height = (float)img->GetHeight();
					gh.DrawImage(img, rc);
				}
				//到达时间间隔，增加
				static CGameTimeVal val(200);
				if (val.IsTimeval()) {
					index++;
				}
				//判断是否需要眨眼
				{
					if (index == 2) {
						if (0 == rand() % 4) {

						}
						else {
							index = 0;
						}
					}
				}
			}
			else {
				//只显示闭眼的图片
				size_t index = 0;
				{
					auto img = m_vImgUp[index];
					RectF  rect;
					rect.X = m_mousePos.X;
					rect.Y = m_mousePos.Y;
					rect.Width = (float)img->GetWidth();
					rect.Height = (float)img->GetHeight();
					gh.DrawImage(img, rect);
				}
			}
			break;
		}
		//左键按下：擦屏幕
		case EStatus::EStatusLeftDown: {
			//反复显示两张图片
			static size_t index = 0;
			if (index > 1) {
				index = 0;
		
			}
			auto img = m_vImgDown[index];
			RectF  rect;
			rect.X = m_mousePos.X;
			rect.Y = m_mousePos.Y;
			rect.Width = (float)img->GetWidth();
			rect.Height = (float)img->GetHeight();
			gh.DrawImage(img, rect);
			if (index == 1) {
				//释放碎片
				g_game->Append(std::make_shared<CShooter3Mark>(m_mousePos.X,
					m_mousePos.Y));
			}
			//30ms update
			static CGameTimeVal val(30);
			if (val.IsTimeval()) {
				index ++;
			}
			break;

		}
		default:
			break;
	}
}

bool CShooter3::OnLButtonDown(UINT nFlags, CPoint point) {
	m_status = EStatus::EStatusLeftDown;
	return true;
}
bool CShooter3::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_status = EStatus::EStatusLeftUp;
	return true;
}
bool CShooter3::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bRightDown = true;
	return true;
}
bool CShooter3::OnRButtonUp(UINT nFlags, CPoint point) {
	m_bRightDown = false;
	return true;
}
bool CShooter3::OnMouseMove(UINT nFlags, CPoint point) {
	m_mousePos.X = point.x;
	m_mousePos.Y = point.y;
	return true;
}