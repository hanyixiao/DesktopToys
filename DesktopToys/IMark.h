#pragma once
/////////////////////////////////////////
//�ṩһ��IsChanging()������ȷ������Ƿ�ı�
///////////////////////////////////////
/*
	����Ϊ���б�ǣ����䣬ͿĨ����Ļ�ϵĶ�����
	����Ч���ĸ��࣬��һ��������
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

