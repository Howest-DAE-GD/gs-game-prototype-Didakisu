#pragma once
#include "BaseGame.h"
//#include "Avatar.h"
#include "utils.h"
#include <vector>
#include "Food.h"
#include <memory>
#include "RottenFood.h"
#include "Timer.h"
#include "PowerUps.h"
#include "TimerCubes.h"


class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;
	bool IsOverlapping(const Rectf& r1, const Rectf& r2);
	void RestartAvatar();
	void LoadFood();
	void LoadRottenFood();
	void LoadPowerUps();
	void LoadTimerCubes();
	void RestartFood();
	void Instructions();

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	//avatar variables:

	float g_Width{50.f};
	float g_Height{50.f};
	Point2f g_ShapeOfAvatar{225.f , 0.f};
	Point2f g_VelocityOfAvatar{ 180.f , 10.f };

	std::vector<Food*> m_pFood;
	std::vector<RottenFood*>m_pRottenFood;
	std::vector<PowerUps*>m_pPowerUps;
	std::vector<TimerCubes*>m_pTimerCubes;

	Timer* m_pTimer;

	bool m_FoodIsEaten = false;
	bool m_RottenFoodIsEaten = false;

	bool m_GameOver = false;
	bool m_StartGame = false;

	bool m_IsTimerPrinting = false;

	int m_Score{};

	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};