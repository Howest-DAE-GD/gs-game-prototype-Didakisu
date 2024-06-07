#pragma once
#include <BaseGame.h>

class TimerCubes
{
public:
	TimerCubes(Point2f shape, float width, float height);
	~TimerCubes();
	void Draw();
	void Update(float elapsedSec);
	Rectf GetShapeOfTimerCubes();
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

