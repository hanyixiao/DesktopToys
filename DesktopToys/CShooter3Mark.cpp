#include "stdafx.h"
#include "CShooter3Mark.h"


CShooter3Mark::CShooter3Mark(float x, float y)
{
	SetCenterPos(x, y);

	//生成1-5之间的随机数
	int i = 1 + rand() % 5;
	TCHAR szFileName[MAX_PATH] = { 0 };
	_stprintf_s(szFileName, TEXT("res/Eraser Ed Marks %02d.png"), i);
	m_img = Image::FromFile(szFileName);
	//图片的角度
	m_degree = (float)(rand() % 360);

	for (int i = 0; i < (1 + rand() % 20); i++) {
		SDynamic dy;
		dy.m_img2 = Image::FromFile(_T("res/Eraser Ed Marks 06.png"));

		//速度
		dy.m_speed = PointF(float(rand() % 10 - 5), float(rand() % 10 - 5));

		//位置
		dy.m_dir = Degree2Radian(rand() % 360);
		//是否显示
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
		gh.RotateTransform(-degree);
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

void CShooter3Mark::Draw(Gdiplus::Graphics &gh)
{
	DrawImageRotate(GetCenterPos(), gh, m_img, m_degree);

	//画落下的物体
	for (auto &dy : m_vD) {
		if (dy.m_bShow) {
			if (!g_game->GetRectF().Contains(dy.m_pos)) {
				continue;
			}
			//否则画出来
			{
				DrawImageRotate(dy.m_pos, gh, dy.m_img2, 
					Radian2Degree(dy.m_dir));
			}
			{
				//调整位置
				dy.m_pos.X += dy.m_speed.X;
				dy.m_pos.Y += dy.m_speed.Y;
				//调整方向，y符合重力情况
				dy.m_speed.Y += 1.0f;
				//调整当前角度
				dy.m_dir += PI(0.1f);
				if (dy.m_dir >= PI(2.0f)) {
					dy.m_dir = 0.0f;
				}
			}
		}
	}

	//移除落到窗口外的游戏对象
	m_vD.erase(std::remove_if(m_vD.begin(),
		m_vD.end(),
		[&](auto &lhs)->bool {
		//在窗口外的全部移除
		return (!g_game->GetRectF().Contains(lhs.m_pos));
	}), m_vD.end());
}

bool CShooter3Mark::IsChanging()const
{
	//数组不为空,说明还有动态对象
	return !m_vD.empty();
}