#include "pch.h"
#include "RottenFood.h"
#include "utils.h"

RottenFood::RottenFood(Point2f shape, float width, float height) :
	m_Shape{ shape }, m_Width{ width }, m_Height{ height }  ,m_Velocity {150.f}
{

}

RottenFood::~RottenFood()
{

}

void RottenFood::Draw()
{
	Rectf avatar{ m_Shape.x , m_Shape.y , m_Width , m_Height };
	utils::SetColor(Color4f{ 1.f , 0.f , 0.f , 1.f });
	utils::FillRect(avatar);
}

void RottenFood::Update(float elapsedSec)
{
	m_Shape.y -= m_Velocity * elapsedSec;
}

Rectf RottenFood::GetShapeOfRottenFood()
{
	return Rectf{ m_Shape.x , m_Shape.y , m_Width , m_Height };
}

void RottenFood::SetColour(const Color4f& colour)
{
	utils::SetColor(colour);
}