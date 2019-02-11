#include "stdafx.h"
#include "MenuItem.h"
/*
	ѡ�񹤾ߵĲ˵�����
 */

CMenuItem::CMenuItem()
{
}

CMenuItem::CMenuItem(float x, float y, PCTSTR szImg, PCTSTR szTips)
{
	m_img = Image::FromFile(szImg);

	int width = m_img->GetWidth();
	int height = m_img->GetHeight();

	//����˵�ռ�õ�����
	RectF r(static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(width),
		static_cast<float>(height)
	);
	SetRect(r);
	m_sizeInit.Width = (float)width;
	m_sizeInit.Height = (float)height;

}
CMenuItem::~CMenuItem()
{
}
//�����Լ�
void CMenuItem::Draw(Gdiplus::Graphics &gh)
{
	if (m_indexAnimate >= m_vAnimateInfo.size()) {
		//���������ţ��ƶ�λ�õȲ���
		m_indexAnimate = m_vAnimateInfo.size();
		if (m_indexAnimate == 0) {
			return;
		}
		m_indexAnimate--;
	}
	{
		auto const &info = m_vAnimateInfo[m_indexAnimate++];
		SetCenterPos(info.pos);						//�ƶ�λ��
		SetSize(info.size.Width, info.size.Height); //����

	}
	gh.DrawImage(m_img, GetRect());
}

//����������
bool CMenuItem::OnLButtonDown(UINT nFlags, CPoint point)
{
	//�鿴�������ĸ��˵�
	if (this->GetRect().Contains((float)point.x, (float)point.y)){
		return true;
	}
	else {
		return false;
	}
}

//����������
bool CMenuItem::OnRButtonDown(UINT nFLags, CPoint point)
{
	return false;
}

//����ƶ�
bool CMenuItem::OnMouseMove(UINT nFlags, CPoint point) 
{	
	return false;
}

//��ʼ���Ż���
void CMenuItem::StartAnimate()
{

}

//���ö�����Ϣ���ɳ���ɢ��������
void CMenuItem::InitAnimateInfo0(float x, float y, float dir)
{
	if (m_bAnimate) {
		return;
	}
	else {
		m_bAnimate = true;
	}
	//��ʼ
	m_indexAnimate = 0;
	//�˶�·����Ϣ���
	m_vAnimateInfo.clear();
	//��ʼ��С
	float w = m_sizeInit.Width*0.01f, h = m_sizeInit.Height*0.01f;
	//ԭʼ��С
	float ww = m_sizeInit.Width, hh = m_sizeInit.Height;
	//���
	float www = m_sizeInit.Width*2.0f, hhh = m_sizeInit.Height*2.0f;

	SAnimateInfo info;

	//��һ��λ��
	{
		info.size.Width = w;
		info.size.Height = h;
		info.pos.X = x;
		info.pos.Y = y;
		m_vAnimateInfo.push_back(info);
	}
	float distance = 1.0f;
	//�ﵽ���ֵ
	while (true) {
		//��Сÿ������0.1
		w *= (1 + 0.1f);
		h *= (1 + 0.1f);
		if (w > www&&h > hhh) {
			break;
		}
		//λ��ÿ������distance����
		x += distance * cos(PI(2) - dir);
		y += distance * sin(PI(2) - dir);
		{
			info.size.Width = w;
			info.size.Height = h;
			info.pos.X = x;
			info.pos.Y = y;
			m_vAnimateInfo.push_back(info);
		}
	}
	distance = 4.0f;
	//�ָ�����ʼֵ
	while (true) 
	{
		//��Сÿ�μ�С0.03
		w *= (1 - 0.03f);
		h *= (1 - 0.03f);
		if (w <= ww&&h <= hh) {
			break;
		}
		//λ��ÿ������distance����
		x += distance * cos(PI(2) - dir);
		y += distance * sin(PI(2) - dir);
		{
			info.size.Width = w;
			info.size.Height = h;
			info.pos.X = x;
			info.pos.Y = y;
			m_vAnimateInfo.push_back(info);
		}
	}
	//����ʼ����Ϣ��������
	info.size = m_sizeInit;
	info.pos.X = x;
	info.pos.Y = y;
	m_vAnimateInfo.push_back(info);
}

//���ö�����Ϣ�����м俪ʼ��ת
void CMenuItem::InitAnimateInfo1(float x, float y, float dir)
{
	if (m_bAnimate) {
		return;
	}
	else {
		m_bAnimate = true;
	}
	m_indexAnimate = 0;
	m_vAnimateInfo.clear();

	float w = m_sizeInit.Width, h = m_sizeInit.Height;
	SAnimateInfo info;
	//��һ��λ��
	{
		info.size.Width = w;
		info.size.Height = h;
		info.pos.Y = y;
		info.pos.X = x;
		m_vAnimateInfo.push_back(info);
	}
	for (int i = 0; i < 25; ++i)
	{
		//�߶�ÿ������10%
		h *= (1 - 0.1f);
		{

			info.size.Width = w;
			info.size.Height = h;
			info.pos.X = x;
			info.pos.Y = y;
			m_vAnimateInfo.push_back(info);
		}
	}
}
//���ö�����Ϣ�������ĵ�����ת������ת
void CMenuItem::InitAnimateInfoReverse()
{
	if (m_bAnimate) {
		return;
	}
	else {
		m_bAnimate = true;
	}
	//��ʼ��
	m_indexAnimate = 0;
	//�Ѳ��ŵ���Ϣ��������������һ��
	std::reverse(m_vAnimateInfo.begin(), m_vAnimateInfo.end());
}

//���ö�����Ϣ���޶���
void CMenuItem::InitAnimateInfo3(float x, float y)
{
	if (m_bAnimate) {
		return;
	}
	else {
		m_bAnimate = true;
	}
	//��ʼ
	m_indexAnimate = 0;
	//�˶�·����Ϣ���
	m_vAnimateInfo.clear();
	float w = m_sizeInit.Width*0.01f, h = m_sizeInit.Height*0.01f;// �����ʲô�ã�
	SAnimateInfo info;
	//�����ʼ����������
	info.size = m_sizeInit;
	info.pos.X = x;
	info.pos.Y = y;
	m_vAnimateInfo.push_back(info);
}