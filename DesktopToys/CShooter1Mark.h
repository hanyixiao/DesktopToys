#pragma once
#include "IMark.h"

class CShooter1Mark
	: public IMark
{
public:
	CShooter1Mark(float x,float y,int index = 0);
	virtual ~CShooter1Mark();
	virtual void Draw(Gdiplus::Graphics &gh);
	virtual bool IsChanging() const;
private:
	std::vector<Image*> m_img;

	//µÚ¼¸·ùÍ¼Æ¬
	size_t m_index{ 0 };
};

