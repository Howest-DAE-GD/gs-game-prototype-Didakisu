#include "pch.h"
#include "PowerUps.h"
#include "utils.h"

PowerUps::PowerUps(Point2f shape, float width, float height) :
	m_Shape{ shape }, m_Width{ width }, m_Height{ height }, m_Velocity{ 150.f }
{

}

PowerUps::~PowerUps()
{

}

void PowerUps::Draw()
{
	Rectf avatar{ m_Shape.x , m_Shape.y , m_Width , m_Height };
	utils::SetColor(Color4f{ 0.f , 1.f , 0.f , 1.f });
	utils::FillRect(avatar);
}

void PowerUps::Update(float elapsedSec)
{
	m_Shape.y -= m_Velocity * elapsedSec;
}

Rectf PowerUps::GetShapeOfPowerUps()
{
	return Rectf{ m_Shape.x , m_Shape.y , m_Width , m_Height };
}

void PowerUps::SetColour(const Color4f& colour)
{
	utils::SetColor(colour);
}