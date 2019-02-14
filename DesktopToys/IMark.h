#pragma once
/////////////////////////////////////////
//提供一个IsChanging()方法，确定标记是否改变
///////////////////////////////////////
/*
	本类为所有标记（喷射，涂抹在屏幕上的东西及
	碎裂效果的父类，是一个抽象类
*/
#include "IDrawable.h"
class IMark :
	public IDrawable
{
public:
	IMark();
	virtual ~IMark();
	virtual bool IsChanging()const = 0;
};

