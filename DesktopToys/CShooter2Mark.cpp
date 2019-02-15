#include "stdafx.h"
#include "CShooter2Mark.h"


CShooter2Mark::CShooter2Mark(float x,float y)
{
	SetCenterPos(x, y);
	//����1-5֮��������
	int i = 1 + rand() % 5;
	TCHAR szfilename[MAX_PATH] = { 0 };
	_stprintf_s(szfilename, TEXT("res/The Toolbox Mark %02d.png"), i);
	m_img = Image::FromFile(szfilename);

	for (int i = 0; i < (1 + rand() % 3); ++i) {
		SDynamic dy;
		dy.m_img2 = Image::FromFile(TEXT("res/The Toolbox Mark 06.png"));

		//�ٶȣ�����ʹ�С��
		dy.m_speed = PointF(float(rand() % 10 - 5), float(rand() % 10 - 5));

		//λ��
		dy.m_pos.X = x + float(rand() % 80 - 40);
		dy.m_pos.Y = y + float(rand() % 80 - 40);
		//��ǰ�Ƕ�
		dy.m_dir = Degree2Radian(rand() % 360);
		dy.m_bShow = true;
		m_vD.push_back(dy);
	}
}


CShooter2Mark::~CShooter2Mark()
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

void CShooter2Mark::Draw(Gdiplus::Graphics &gh)
{
	gh.DrawImage(m_img, GetCenterPos());

	//�����µ�����
	for (auto &dy : m_vD) {
		if (dy.m_bShow) {
			//�ж��Ƿ��䵽����
			if (!g_game->GetRectF().Contains(dy.m_pos)) {
				continue;
			}

			//û���䵽����
			//��
			DrawImageRotate(dy.m_pos, gh, dy.m_img2, Radian2Degree(dy.m_dir));
			{
				dy.m_pos.X += dy.m_speed.X;
				dy.m_pos.Y += dy.m_speed.Y;
				//�����ٶ�,y��������������ٶ� 
				dy.m_speed.Y += 1.0f;
				//������ǰ״̬
				dy.m_dir += PI(0.1f);
				if (dy.m_dir >= PI(2.0f)) {
					dy.m_dir = 0.0f;
				}

			}
		}
	}
	/////////////////////////////////////
	/////////what is this code?????????//
	/////////////////////////////////////
	//�Ƴ��䵽������Ķ���
	m_vD.erase(std::remove_if(m_vD.begin(),
		m_vD.end(),
		[&](auto &lhs)->bool {
		return (!g_game->GetRectF().Contains(lhs.m_pos)); 
	}), m_vD.end());

}

bool CShooter2Mark::IsChanging()const
{
	//û�п�˵�����ж�̬����
	return !m_vD.empty();
}
