#pragma once
#include "MenuItem.h"
#include "IMouseAction.h"
#include "IDrawable.h"
class CDMenu
	:public IDrawable
	,public IMouseAction
{
public:
	CDMenu(HWND hWnd);
	virtual ~CDMenu();

	//���³�ʼ�������˵������λ����Ϣ
	void InitAnimateInfo0();

	//���ݵ�ǰ�����Ի����Լ�
	virtual void Draw(Gdiplus::Graphics &gh);

	///////////////////////////////////////
	//���������Ϣ
	//�������������false,������Ը����ж��Ƿ���д���
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	
	virtual bool OnMouseMove(UINT nFLags, CPoint point);
private:
	HWND m_hWnd;
	//�˵�����
	//����
	std::shared_ptr<CMenuItem> m_box;
	//�и�1����
	std::shared_ptr<CMenuItem> m_cover;
	//�и�2���ر�
	std::shared_ptr<CMenuItem> m_cover2;
	//ѡ��
	std::shared_ptr<CMenuItem> m_item0;
	std::shared_ptr<CMenuItem> m_item1;
	std::shared_ptr<CMenuItem> m_item2;
	std::shared_ptr<CMenuItem> m_item3;

	//������������
	void EndAnimate();

	typedef enum {
		EStatusOverCover1,
		EStatusItem0,                       //���Ŷ���
		EStatusItem1,
		EStatusItem2,
		EStatusItem3,
		EStatusOverCover2,                  //���Źغ��ӵĶ���
		EStatusAll
	}EStatus;
	EStatus m_eStatus{ EStatusOverCover1 };
};

