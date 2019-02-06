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
#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

//ʹ�þ���
/*
char *pBuf = new char[1024];
ON_SCOPE_EIXT([&])()
{
	if (pBuf) {
		delete[] pBuf;
	}
}
*/