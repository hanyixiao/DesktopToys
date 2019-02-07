#pragma once
/*@function:��Ϸ��ʱ����ʵ��
 *@author:YixiaoHan
 */
#include "windows.h"
class CGameTimer
{
public:
	explicit CGameTimer(unsigned int timeout = 3000,//���캯��������Ĭ��ֵ
		unsigned int timeval = 300)//������ʱ����������ֵĬ��Ϊ3000,300
	: m_timeout(timeout)
		, m_timeval(timeval)
	{	
	}
	virtual ~CGameTimer()
	{
	}
	//����ʱ����
	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}
	//������һ�ε�ʱ��
	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}
	//������ʼʱ��Ϊ��ʱʱ��
	void StartTimer()
	{
		m_timeStart = ::GetTickCount();
		m_times = 0;
	}
	//�����ܳ�ʱʱ��
	void SetTimeOut(unsigned int timeout) 
	{
		m_timeout = timeout;
	}
	//�ж��Ƿ�ʱ
	bool IsTimeOut()const 
	{
		return (GetTickCount() - m_timeLast) >= m_timeout;
	}
	//�ж��Ƿ񵽴�ʱ������������ˣ��Ƿ����
	bool IsTimeval(bool bUpdate = true)
	{
		if ((GetTickCount() - m_timeLast) >= m_timeval) {
			if (bUpdate) {
				m_timeLast = GetTickCount();
				m_times++;                         //��¼�����˶��ٴ�
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
	unsigned int m_timeStart{::GetTickCount()};//��ʱ����ʼʱ��
	unsigned int m_timeLast{m_timeStart};//��һ�θ���ʱ��
	unsigned int m_times{0};//����ISTImeVal�Ĵ���
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
				m_times++;                         //��¼�����˶��ٴ�
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