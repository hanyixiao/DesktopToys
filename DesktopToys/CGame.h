#pragma once
#include "Shooter.h" 
#include "CDMenu.h"
class IMark; //向前声明，因为下面要用到该接口类型的指针
class CGame
{
public:
	/*构造函数：
	 *hWnd：游戏窗口
	 *x,y：位置
	 *w,h:窗口宽度
	 */
	CGame(HWND hWnd,float x,float y,float w,float h);
	~CGame();
public:
	//游戏的每一帧
	bool EnterFrame(DWORD dwTime);
	//处理鼠标消息
	//鼠标左键按下
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	//鼠标左键双击
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDlbClk(UINT nFlags, CPoint point);
	//鼠标移动
	void OnMouseMove(UINT nFlags, CPoint point);
	//按下ESC按键的函数响应
	BOOL OnESC();
	//增加一个破坏物
	void Append(std::shared_ptr<IMark> pMark)
	{
		m_vMarks.push_back(pMark);
	}
	//获取游戏窗口的宽度
	float GetWidth()const
	{
		return m_width;
	}
	//获取游戏窗口的高度
	float GetHeight()const
	{
		return m_height;
	}
	//获取范围
	RectF GetRectF()const
	{
		return RectF(m_x, m_y, m_width, m_height);
	}
private:
	HWND m_hWnd;
	//窗口的起始位置
	float m_x;
	float m_y;

	//游戏窗口的宽度和高度
	float m_width;
	float m_height;
	//游戏阶段
	//游戏只分为两个阶段，菜单阶段和游戏阶段
	typedef enum EGameStatus {EGameStatusSelect,EGamestatusNormal}EGameStatus;
	EGameStatus m_eStatus{ EGameStatusSelect };//声明并初始化
private:
	//客户区大小
	CRect m_rcClient;

	//记录游戏有多少帧
	int m_fps{ 0 };
	//输出FPS文字的画刷
	SolidBrush m_brush{ Color{254,0xFF,0x00,0x00} };
	//输出FPS的文字字体
	Gdiplus::Font m_font{ L"宋体",10.0 };
	//在左上角显示
	PointF origin{ 0.0f,0.0f };
	//画所有对象
	void Draw();
	//输出pfs
	void DrawFps(Gdiplus::Graphics &gh);
	//破坏窗口留下的东西
	std::vector<std::shared_ptr<IMark>> m_vMarks;
	//背景图
	Gdiplus::Bitmap *m_imgBK;
	//菜单和工具类
	std::shared_ptr<CDMenu> m_menu;
	std::shared_ptr<Shooter> m_pTool;
};