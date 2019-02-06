#pragma once
#include "IDrawable.h"
#include "IMouseAction.h"
/*
	本游戏中的4中工具的父类，可以自生绘制，并相应鼠标消息
*/
class Shooter:public IDrawable,public IMouseAction
{
public:
	Shooter();
	virtual ~Shooter();
};

