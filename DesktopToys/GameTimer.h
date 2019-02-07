#pragma once
/*@function:游戏计时器的实现
 *@author:YixiaoHan
 */
#include "windows.h"
class CGameTimer
{
public:
	explicit CGameTimer(unsigned int timeout = 3000,//构造函数参数有默认值
		unsigned int timeval = 300)//当调用时不传参数，值默认为3000,300
	: m_timeout(timeout)
		, m_timeval(timeval)
	{	
	}
	virtual ~CGameTimer()
	{
	}
	//设置时间间隔
	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}
	//设置上一次的时间
	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}
	//重设起始时间为当时时间
	void StartTimer()
	{
		m_timeStart = ::GetTickCount();
		m_times = 0;
	}
	//设置总超时时间
	void SetTimeOut(unsigned int timeout) 
	{
		m_timeout = timeout;
	}
	//判断是否超时
	bool IsTimeOut()const 
	{
		return (GetTickCount() - m_timeLast) >= m_timeout;
	}
	//判断是否到达时间间隔：如果到了，是否更新
	bool IsTimeval(bool bUpdate = true)
	{
		if ((GetTickCount() - m_timeLast) >= m_timeval) {
			if (bUpdate) {
				m_timeLast = GetTickCount();
				m_times++;                         //记录更新了多少次
			}
			return true;
		}
		else {
			return false;
		}
	}
	size_t GetTimes() const
	{
		return m_times;
	}
private:
	unsigned int m_timeout{ 3000 };
	unsigned int m_timeval{ 300 };
	unsigned int m_timeStart{::GetTickCount()};//计时器开始时间
	unsigned int m_timeLast{m_timeStart};//上一次更新时间
	unsigned int m_times{0};//符合ISTImeVal的次数
};
class CGameTimeVal
{
public:
	explicit CGameTimeVal(size_t timeval = 300)
		:m_timeval(timeval)
	{

	}
	virtual ~CGameTimeVal()
	{
	}
	void Restart()
	{
		m_timeLast = GetTickCount();
		m_times = 0;
	}
	void SetTimeval(size_t timeval)
	{
		m_timeval = timeval;
	}
	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}
	bool IsTimeval(bool bUpdate = true)
	{
		if ((GetTickCount() - m_timeLast) >= m_timeval) {
			if (bUpdate) {
				m_timeLast = GetTickCount();
				m_times++;                         //记录更新了多少次
			}
			return true;
		}
		else {
			return false;
		}
	}
	size_t GetTimes()const
	{
		return m_times;
	}
private:
	unsigned int m_timeval{ 300 };
	unsigned int m_timeLast{ GetTickCount() };
	unsigned int m_times{ 0 };
};