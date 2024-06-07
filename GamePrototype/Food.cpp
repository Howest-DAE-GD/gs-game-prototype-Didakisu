#include "pch.h"
#include "Food.h"
#include "utils.h"

Food::Food(Point2f shape, float width, float height) :
	m_Shape{ shape }, m_Width{ width }, m_Height{ height }  ,m_Velocity {150.f}
{

}

Food::~Food()
{

}

void Food::Draw()
{
	Rectf avatar{ m_Shape.x , m_Shape.y , m_Width , m_Height };
	utils::SetColor(Color4f{ 1.f , 1.f , 0.f , 1.f });
	utils::FillRect(avatar);
}

void Food::Update(float elapsedSec)
{
	m_Shape.y -= m_Velocity * elapsedSec;
}

Rectf Food::GetShapeOfFood()
{
	return Rectf{ m_Shape.x , m_Shape.y , m_Width , m_Height };
}

void Food::SetColour(const Color4f& colour)
{
	utils::SetColor(colour);
}