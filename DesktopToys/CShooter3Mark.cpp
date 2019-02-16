#include "stdafx.h"
#include "CShooter3Mark.h"


CShooter3Mark::CShooter3Mark(float x, float y)
{
	SetCenterPos(x, y);

	//����1-5֮��������
	int i = 1 + rand() % 5;
	TCHAR szFileName[MAX_PATH] = { 0 };
	_stprintf_s(szFileName, TEXT("res/Eraser Ed Marks %02d.png"), i);
	m_img = Image::FromFile(szFileName);
	//ͼƬ�ĽǶ�
	m_degree = (float)(rand() % 360);

	for (int i = 0; i < (1 + rand() % 20); i++) {
		SDynamic dy;
		dy.m_img2 = Image::FromFile(_T("res/Eraser Ed Marks 06.png"));

		//�ٶ�
		dy.m_speed = PointF(float(rand() % 10 - 5), float(rand() % 10 - 5));

		//λ��
		dy.m_dir = Degree2Radian(rand() % 360);
		//�Ƿ���ʾ
		dy.m_bShow = true;
		m_vD.push_back(dy);
	}
}




CShooter3Mark::~CShooter3Mark()
{
}
static void DrawImageRotate(PointF mousePt, Graphics &gh,
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
		gh.RotateTransform(-degree);
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

void CShooter3Mark::Draw(Gdiplus::Graphics &gh)
{
	DrawImageRotate(GetCenterPos(), gh, m_img, m_degree);

	//�����µ�����
	for (auto &dy : m_vD) {
		if (dy.m_bShow) {
			if (!g_game->GetRectF().Contains(dy.m_pos)) {
				continue;
			}
			//���򻭳���
			{
				DrawImageRotate(dy.m_pos, gh, dy.m_img2, 
					Radian2Degree(dy.m_dir));
			}
			{
				//����λ��
				dy.m_pos.X += dy.m_speed.X;
				dy.m_pos.Y += dy.m_speed.Y;
				//��������y�����������
				dy.m_speed.Y += 1.0f;
				//������ǰ�Ƕ�
				dy.m_dir += PI(0.1f);
				if (dy.m_dir >= PI(2.0f)) {
					dy.m_dir = 0.0f;
				}
			}
		}
	}

	//�Ƴ��䵽���������Ϸ����
	m_vD.erase(std::remove_if(m_vD.begin(),
		m_vD.end(),
		[&](auto &lhs)->bool {
		//�ڴ������ȫ���Ƴ�
		return (!g_game->GetRectF().Contains(lhs.m_pos));
	}), m_vD.end());
}

bool CShooter3Mark::IsChanging()const
{
	//���鲻Ϊ��,˵�����ж�̬����
	return !m_vD.empty();
}