#include "pch.h"
#include "TimerCubes.h"
#include "utils.h"

TimerCubes::TimerCubes(Point2f shape, float width, float height) :
	m_Shape{ shape }, m_Width{ width }, m_Height{ height }, m_Velocity{ 150.f }
{

}

TimerCubes::~TimerCubes()
{

}

void TimerCubes::Draw()
{
	Rectf avatar{ m_Shape.x , m_Shape.y , m_Width , m_Height };
	utils::SetColor(Color4f{ 1.f , 0.f , 1.f , 1.f });
	utils::FillRect(avatar);
}

void TimerCubes::Update(float elapsedSec)
{
	m_Shape.y -= m_Velocity * elapsedSec;
}

Rectf TimerCubes::GetShapeOfTimerCubes()
{
	return Rectf{ m_Shape.x , m_Shape.y , m_Width , m_Height };
}

void TimerCubes::SetColour(const Color4f& colour)
{
	utils::SetColor(colour);
}