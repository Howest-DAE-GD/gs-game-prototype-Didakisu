#pragma once
#include "RottenFood.h"
#include <BaseGame.h>

class RottenFood
{
public:
	RottenFood(Point2f shape, float width, float height);
	~RottenFood();
	void Draw();
	void Update(float elapsedSec);
	Rectf GetShapeOfRottenFood();
	void SetColour(const Color4f& colour);

	bool IsEaten() const { return m_eaten; }
	void SetEaten(bool eaten) { m_eaten = eaten; }
private:
	float m_Width;
	float m_Height;
	Point2f m_Shape;
	float m_Velocity;

	bool m_eaten{ false };
};
