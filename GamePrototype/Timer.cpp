#include "pch.h"
#include "Timer.h"
#include "iostream"
#include <ctime>

Timer::Timer():
	m_SecondsInTotal{21.f},
	m_TotalTimeElapsed{}
{

}
Timer::~Timer()
{

}

void Timer::Print()
{
	int smallSeconds{ (int(m_SecondsInTotal - m_TotalTimeElapsed) % 60) % 10 };
	int seconds{ ((int(m_SecondsInTotal - m_TotalTimeElapsed) % 60) / 10) };
	int minutes{ int(m_SecondsInTotal - m_TotalTimeElapsed) / 60 };

	std::cout << minutes << ":" << seconds << smallSeconds << std::endl;
}

void Timer::Update(float elapsedSec)
{
	m_TotalTimeElapsed += elapsedSec;
}

bool Timer::TimeOut(float elapsedSec)
{
	if (m_TotalTimeElapsed >= m_SecondsInTotal)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Timer::Restart()
{
	m_TotalTimeElapsed = 0.0f;
}

void Timer::AddTime(float elapsedSec)
{
	m_TotalTimeElapsed -= 3.0f;
	if (m_TotalTimeElapsed < 0.0f)
	{
		m_TotalTimeElapsed = 0.0f;
	}
}