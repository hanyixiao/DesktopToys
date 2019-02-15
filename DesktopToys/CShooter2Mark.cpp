#include "stdafx.h"
#include "CShooter2Mark.h"


CShooter2Mark::CShooter2Mark(float x,float y)
{
	SetCenterPos(x, y);
	//生成1-5之间的随机数
	int i = 1 + rand() % 5;
	TCHAR szfilename[MAX_PATH] = { 0 };
	_stprintf_s(szfilename, TEXT("res/The Toolbox Mark %02d.png"), i);
	m_img = Image::FromFile(szfilename);

	for (int i = 0; i < (1 + rand() % 3); ++i) {
		SDynamic dy;
		dy.m_img2 = Image::FromFile(TEXT("res/The Toolbox Mark 06.png"));

		//速度（方向和大小）
		dy.m_speed = PointF(float(rand() % 10 - 5), float(rand() % 10 - 5));

		//位置
		dy.m_pos.X = x + float(rand() % 80 - 40);
		dy.m_pos.Y = y + float(rand() % 80 - 40);
		//当前角度
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

void CShooter2Mark::Draw(Gdiplus::Graphics &gh)
{
	gh.DrawImage(m_img, GetCenterPos());

	//画落下的物体
	for (auto &dy : m_vD) {
		if (dy.m_bShow) {
			//判断是否落到外面
			if (!g_game->GetRectF().Contains(dy.m_pos)) {
				continue;
			}

			//没有落到外面
			//画
			DrawImageRotate(dy.m_pos, gh, dy.m_img2, Radian2Degree(dy.m_dir));
			{
				dy.m_pos.X += dy.m_speed.X;
				dy.m_pos.Y += dy.m_speed.Y;
				//调整速度,y方向符合重力加速度 
				dy.m_speed.Y += 1.0f;
				//调整当前状态
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
	//移除落到窗口外的对象
	m_vD.erase(std::remove_if(m_vD.begin(),
		m_vD.end(),
		[&](auto &lhs)->bool {
		return (!g_game->GetRectF().Contains(lhs.m_pos)); 
	}), m_vD.end());

}

bool CShooter2Mark::IsChanging()const
{
	//没有空说明还有动态对象
	return !m_vD.empty();
}
