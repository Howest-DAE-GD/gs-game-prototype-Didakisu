#pragma once
#include <BaseGame.h>

class Avatar
{
public:
	Avatar(Point2f shape , float width , float height);
	~Avatar();
	void Draw();
	void Update(float elapsedSec);
private:
	float m_Width;
	float m_Height;
	Point2f m_Shape;
	//float m_Velocity;
};