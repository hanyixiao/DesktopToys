#pragma once
#include "stdafx.h"
#include <functional>
class ScopeGuard
{
public:
	explicit ScopeGuard(std::function<void()> onExitScope) //���캯��
		:onExitScope_(onExitScope), dismissed_(false)       //��ʼ���б�
	{}
	~ScopeGuard()
	{
		if (!dismissed_) {        //�ж��Ƿ�����ͷ���Դ�Ķ���
			onExitScope_();   
		}
	}
	void Dismiss()
	{
		dismissed_ = true;
	}
private:
	std::function<void()> onExitScope_;
	bool dismissed_;
private:
	ScopeGuard(ScopeGuard const &); //ȥ����ֵ���캯��
	ScopeGuard &operator = (ScopeGuard const &); //ȥ����ֵ������
};

