#pragma once
#include "stdafx.h"
#include <functional>
class ScopeGuard
{
public:
	explicit ScopeGuard(std::function<void()> onExitScope) //构造函数
		:onExitScope_(onExitScope), dismissed_(false)       //初始化列表
	{}
	~ScopeGuard()
	{
		if (!dismissed_) {        //判断是否进行释放资源的动作
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
	ScopeGuard(ScopeGuard const &); //去掉赋值构造函数
	ScopeGuard &operator = (ScopeGuard const &); //去掉赋值操作符
};

