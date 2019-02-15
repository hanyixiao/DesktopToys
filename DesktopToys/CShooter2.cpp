#include "stdafx.h"
#include "CShooter2.h"
#include "CShooter2Mark.h"

CShooter2::CShooter2()
{
	//����ͼƬ
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
	//��ת��ͼƽ��
	PointF center = mousePt;
	center.X += img->GetWidth() / 2.0f;
	center.Y += img->GetHeight() / 2.0f;

	//1ƽ�Ʊ仯�ƶ�ԭ��λ�õ������
	gh.TranslateTransform(center.X, center.Y);
	//2.��ת�任:ʹ��������תdegree��
	gh.RotateTransform(degree);
	//3.�ָ�ԭ��
	gh.TranslateTransform(-center.X, -center.Y);

	//�����˳�ʱ�ָ�������ϵͳ��ƽ�Ƶ�ת��
	ON_SCOPE_EXIT([&]() {
		//1ƽ�Ʊ仯�ƶ�ԭ��λ�õ������
		gh.TranslateTransform(center.X, center.Y);
		//2.��ת�任:ʹ��������תdegree��
		gh.RotateTransform(degree);
		//3.�ָ�ԭ��
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
	//����ͼ��

}
void CShooter2::Draw(Gdiplus::Graphics &gh)
{
	switch (m_status) {
		//����
		case EStatus::EStatusHammer: {
			switch (m_eStatusHammer) {
				//��������һ�ε����������ӵ���ͬʱ����ͼƬ�����仯
				case EStatusHammer::EStatusHammerDownFirst: {
					g_game->Append(std::make_shared<CShooter2Mark>
						(m_mousePos.X, m_mousePos.Y));
					m_eStatusHammer = EStatusHammer::EStatusHammerDown;
				}
				//����������
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
				//������̧��
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
			//��������
			m_eStatusHammer = EStatusHammer::EStatusHammerDownFirst;
			break;
		}
		case EStatus::EStatusSaw: {
			//��⿪ʼ���
			m_eStatusSaw = EStatusSaw::EStatusSawStart;
			//��ǰλ��
			m_sawPos = m_mousePos;
			break;
		}
		default:
			break;
	}
	return false;
}
//������̧��
bool CShooter2::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (m_status) {
		case EStatus::EStatusHammer: {
			//����̧��
			m_eStatusHammer = EStatusHammer::EStatusHammerUp;
			break;
		}
		case EStatus::EStatusSaw: {
			//���
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

//��������֮��ľ���
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

	//���ݲ�ͬ������д���
	switch (m_status) {
		case EStatus::EStatusHammer: {
		    //����ά��ԭ����״̬
			break;
		}
		case EStatus::EStatusSaw: {
			//���û�ж���������ʱ��change the dir
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
					//angle ��degree per 
					m_sawDegree = Radian2Degree(theta);
					//��ס��ε�λ��
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