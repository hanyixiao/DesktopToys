#pragma once
#include "IDrawable.h"
#include "IMouseAction.h"
/*
	����Ϸ�е�4�й��ߵĸ��࣬�����������ƣ�����Ӧ�����Ϣ
*/
class Shooter:public IDrawable,public IMouseAction
{
public:
	Shooter();
	virtual ~Shooter();
};

