#include "pch.h"
#include "Avatar.h"
#include "utils.h"

Avatar::Avatar(Point2f shape, float width, float height) :
	m_Shape{ shape }, m_Width {width}, m_Height{height}
{

}

Avatar::~Avatar()
{

}

void Avatar::Draw()
{
	Rectf avatar{ m_Shape.x , m_Shape.y , m_Width , m_Height };
	utils::SetColor(Color4f{ 1.f , 0.f , 1.f , 1.f });
	utils::DrawRect(avatar);
	utils::FillRect(avatar);
}

void Avatar::Update(float elapsedSec)
{
}
