#include "stdafx.h"
#include "CShooter1.h"
#include "CShooter1Mark.h"

CShooter1::CShooter1(int height):m_nHeight(height)
{
	//载入图片
	m_img0 = Image::FromFile(TEXT(
		"res/Pablo The Painter 00.png"));
	m_img1 = Image::FromFile(TEXT(
		"res/Pablo The Painter 01.png"));
	m_img2 = Image::FromFile(TEXT(
		"res/Pablo The Painter 02.png"));
	m_img3 = Image::FromFile(TEXT(
		"res/Pablo The Painter 03.png"));
	m_img4 = Image::FromFile(TEXT(
		"res/Pablo The Painter 04.png"));
	m_img5 = Image::FromFile(TEXT(
		"res/Pablo The Painter 05.png"));
}


CShooter1::~CShooter1()
{
}

//根据自己的属性绘制自己
void CShooter1::Draw(Gdiplus::Graphics &gh)
{
	//先画梯子
	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////
	auto drawImg = [&](Image *img) {
		RectF rc;
		rc.X = m_mousePos.X;
		rc.Y = m_mousePos.Y;
		rc.Width = (float)img->GetWidth();
		rc.Height = (float)img->GetHeight();
		rc.Offset(-(rc.Width / 3.0f - 10.0f), 0);
		gh.DrawImage(img, rc);
	};
	//重复画出相同的图片，拼接成一个梯子
	{
		//获取图片大小
		float h = (float)m_img0->GetHeight();
		float w = (float)m_img0->GetWidth();

		RectF rc;
		rc.Width = w;
		rc.Height = h;
		rc.X = m_mousePos.X;
		//循环绘制
		for (int y = 0; y < m_nHeight; ++y)
		{
			rc.Y = y * h;
			gh.DrawImage(m_img0, rc);
		}
	}
	//根据当前的状态，绘制不同的图片
	switch (m_status) {
		case 0: {
			break;
			}
		case 1: {
			drawImg(m_img1);
			break;
		}
		case 2: {
			drawImg(m_img2);
			break;
		}
		case 3: {
			drawImg(m_img3);
			break;
		}
		case 4: {
			drawImg(m_img4);
			break;
		}
		case 5:
		{
			drawImg(m_img5);
			break;
		}
		default:
			break;
	}
}
///////////////////////////////////////////
//处理鼠标消息
///////////////////////////////////////////
bool CShooter1::OnLButtonDown(UINT nFlags, CPoint point)
{
	//粉刷状态
	m_status = 5;
	return true;
}
bool CShooter1::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_status = 1;
	return true;
}
bool CShooter1::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (1 + m_iColorIndex >= 6) {
		m_iColorIndex = 0;
	}
	else {
		m_iColorIndex++;
	}
	return false;
}
//鼠标移动
bool CShooter1::OnMouseMove(UINT nFlags, CPoint point)
{
	m_mousePos.X = (float)point.x;
	m_mousePos.Y = (float)point.y;
	//切换粉刷状态
	if (m_status == 5) {
		m_status = 5;
		//判断是否需要增加一个标记
		RectF rc;
		rc.X = m_mousePos.X;
		rc.Y = m_mousePos.Y;
		rc.Height = 1;
		rc.Width = 1;
		if (!rc.Contains(m_mousePos)) {
			//记录位置
			m_mousePosLast = m_mousePos;
			g_game->Append(std::make_shared<CShooter1Mark>(
				m_mousePos.X, m_mousePos.Y, m_iColorIndex));
		}
		return true;
	}
	/*****不是粉刷状态，绘制人物的移动动画*******/
	//判断是否需要换腿
	//向下移动
	if ((point.y > m_lastChangePos.Y) &&
		(m_distanceChange <= abs(point.y - m_lastChangePos.Y))) {
		switch (m_status) {
			case 1: {
				m_status = 3;
				break;
				}
			case 2: {
				m_status = 3;
				break;
			}
			case 3: {
				m_status = 1;
				break;
			}
			case 4: {
				m_status = 1;
				break;
			}
			default:
				break;
		}
		//记录最后一次的位置
		m_lastChangePos = m_mousePos;
	}
	else if ((point.y < m_lastChangePos.Y) &&
		(m_distanceChange <= abs(point.y - m_lastChangePos.Y))) {
			switch (m_status) {
			case 1: {
				m_status = 3;
				break;
			}
			case 2: {
				m_status = 3;
				break;
			}
			case 3: {
				m_status = 1;
				break;
			}
			case 4: {
				m_status = 1;
				break;
			}
			default:
				break;
			}
			m_lastChangePos = m_mousePos;
	}
	else {
		//移动距离太小，不做移动
	}
	return true;

}