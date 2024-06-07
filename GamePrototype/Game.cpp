#include "pch.h"
#include "Game.h"
#include "iostream"
#include <random>
#include <thread>
#include <chrono>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	Instructions();
	LoadFood();
	LoadRottenFood();
	LoadPowerUps();
	LoadTimerCubes();

	m_pTimer = new Timer();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	if (m_GameOver) return;

	if (m_StartGame == true)
	{
		m_pTimer->Update(elapsedSec);

		//Printing Timer
		static std::chrono::time_point<std::chrono::system_clock> last_print_time = std::chrono::system_clock::now();

		// Calculate elapsed time since last print
		std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - last_print_time;

		// Check if one second has passed
		if (elapsed_time.count() >= 1.0) {
			// Update last print time
			last_print_time = std::chrono::system_clock::now();

			// Print the timer
			m_pTimer->Print();
		}
		

		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[SDL_SCANCODE_RIGHT] && g_ShapeOfAvatar.x + g_Width < GetViewPort().left + GetViewPort().width) {
			g_ShapeOfAvatar.x += g_VelocityOfAvatar.x * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_LEFT] && g_ShapeOfAvatar.x > GetViewPort().left) {
			g_ShapeOfAvatar.x -= g_VelocityOfAvatar.x * elapsedSec;
		}
		if (g_ShapeOfAvatar.y < 0) {
			g_ShapeOfAvatar.y = 0;
			g_VelocityOfAvatar.y = 0;
		}

		//food:
		for (auto& food : m_pFood)
		{
			food->Update(elapsedSec);

			// Check for collisions with avatar
			Rectf avatar{ g_ShapeOfAvatar.x , g_ShapeOfAvatar.y , g_Width , g_Height };
			if (IsOverlapping(food->GetShapeOfFood(), avatar) && !food->IsEaten())
			{
				m_Score += 1;
				std::cout << "Current score: " << m_Score << std::endl;
				food->SetEaten(true);

				//"inflate our avatar"
				g_Width += 5.f;
				g_Height += 5.f;

				g_ShapeOfAvatar.x -= 2.5f;

			}
		}

		// Remove eaten food objects
		m_pFood.erase(std::remove_if(m_pFood.begin(), m_pFood.end(), [](const Food* food) {
			return food->IsEaten();
			}), m_pFood.end());


		//rottenFood:
		for (auto& Rottenfood : m_pRottenFood)
		{

			Rottenfood->Update(elapsedSec);

			// Check for collisions with avatar
			Rectf avatar{ g_ShapeOfAvatar.x , g_ShapeOfAvatar.y , g_Width , g_Height };
			if (IsOverlapping(Rottenfood->GetShapeOfRottenFood(), avatar) && !Rottenfood->IsEaten())
			{
				std::cout << "Game Over!" << std::endl;
				Rottenfood->SetEaten(true);
				m_GameOver = true;
			}
		}

		// Remove eaten rotten food objects
		m_pRottenFood.erase(std::remove_if(m_pRottenFood.begin(), m_pRottenFood.end(), [](const RottenFood* rottenfood) {
			return rottenfood->IsEaten();
			}), m_pRottenFood.end());

		for (auto& PowerUps : m_pPowerUps)
		{

			PowerUps->Update(elapsedSec);

			// Check for collisions with avatar
			Rectf avatar{ g_ShapeOfAvatar.x , g_ShapeOfAvatar.y , g_Width , g_Height };
			if (IsOverlapping(PowerUps->GetShapeOfPowerUps(), avatar) && !PowerUps->IsEaten())
			{
				g_Width = 50.f;
				g_Height = 50.f;
				std::cout << "You went back to your default size!" << std::endl;
				PowerUps->SetEaten(true);
			}
		}

		// Remove eaten power ups objects
		m_pPowerUps.erase(std::remove_if(m_pPowerUps.begin(), m_pPowerUps.end(), [](const PowerUps* rottenfood) {
			return rottenfood->IsEaten();
			}), m_pPowerUps.end());

		//timer cubes:

		for (auto& timerCubes : m_pTimerCubes)
		{
			timerCubes->Update(elapsedSec);

			// Check for collisions with avatar
			Rectf avatar{ g_ShapeOfAvatar.x , g_ShapeOfAvatar.y , g_Width , g_Height };
			if (IsOverlapping(timerCubes->GetShapeOfTimerCubes(), avatar) && !timerCubes->IsEaten())
			{
				std::cout << "A timer cube is eaten!" << std::endl;
				m_pTimer->AddTime(elapsedSec);
				timerCubes->SetEaten(true);
			}
		}

		// Remove eaten food objects
		m_pTimerCubes.erase(std::remove_if(m_pTimerCubes.begin(), m_pTimerCubes.end(), [](const TimerCubes* timerCube) {
			return timerCube->IsEaten();
			}), m_pTimerCubes.end());
	}


	//timer
	if (m_pTimer->TimeOut(elapsedSec) == true)
	{
		std::cout << "The timer ran out!" << std::endl;
		m_GameOver = true;
	}

	if (m_GameOver)
	{
		std::cout << "Total score:" << m_Score << std::endl;
	}
}



void Game::Draw() const
{
	ClearBackground();
	//draw avatar:
	utils::SetColor(Color4f{ 1.f , 1.f , 1.f , 1.f });
	utils::FillRect(g_ShapeOfAvatar.x, g_ShapeOfAvatar.y, g_Width, g_Height);

	//draw food:
	if (m_FoodIsEaten == true)
	{
	
	}
	else
	{
		for (const auto& food : m_pFood)
		{
			food->Draw();
		}

		for (const auto& rottenfood : m_pRottenFood)
		{
			rottenfood->Draw();
		}

		for (const auto& powerUps : m_pPowerUps)
		{
			powerUps->Draw();
		}

		for (const auto& timerCubes : m_pTimerCubes)
		{
			timerCubes->Draw();
		}
	}

	
	
	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_r:
		RestartAvatar();
		RestartFood();
		m_pTimer->Restart();
		m_Score = 0;
		m_GameOver = false;
		break;
	case SDLK_s:
		m_StartGame = true;
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


bool Game::IsOverlapping(const Rectf& r1, const Rectf& r2)
{
	if ((r1.left + r1.width) < r2.left || (r2.left + r2.width) < r1.left)
	{
		return false;
	}
	if (r1.bottom > (r2.bottom + r2.height) || r2.bottom > (r1.bottom + r1.height))
	{
		return false;
	}

	return true;
}

void Game::RestartAvatar()
{
	g_ShapeOfAvatar = Point2f{ 225.f , 0.f };
	g_Width = 50.f;
	g_Height = 50.f;
}

void Game::RestartFood()
{
	m_pFood.clear();
	LoadFood();
	m_pRottenFood.clear();
	LoadRottenFood();
	m_pPowerUps.clear();
	LoadPowerUps();
}

void Game::Instructions()
{
	std::cout << "Instructions:" << std::endl;
	std::cout << "You are playing as the white cube." << std::endl;
	std::cout << "The goal is to collect as much as yellow cubes you can." << std::endl;
	std::cout << "Avoid the red cubes, they're rotten food, and they will kill you." << std::endl;
	std::cout << "Green cubes are speacial cubes, eating them will make your avatar its default size, without loosing your score,making it easier to dodge red cubes." << std::endl;
	std::cout << "Magenta cubes are timer cubes, eating them will result in extra 3 seconds!" << std::endl;
	std::cout << "Press S to start the game" << std::endl;
	std::cout << "Move with LEFT and RIGHT arrows." << std::endl;
	std::cout << "Press R to restart the game." << std::endl;
}

void Game::LoadFood()
{
	const int numFood = 60;

	float minX = 10.f;
	float maxX = 490.f;
	float minY = 500.f;
	float maxY = 7000.f;

	// Create a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distributionX(minX, maxX);
	std::uniform_real_distribution<float> distributionY(minY, maxY);

	// Loop to create multiple food objects
	for (int i = 0; i < numFood; ++i)
	{
		// Generate random position within the defined range
		float randomX = distributionX(gen);
		float randomY = distributionY(gen);

		// Create a new Food object with the random position
		m_pFood.push_back(new Food(Point2f{ randomX, randomY }, 5.f, 5.f));
	}
}

void Game::LoadRottenFood()
{
	const int numRottenFood = 15;

	float minX1 = 10.f;
	float maxX1 = 490.f;
	float minY1 = 500.f;
	float maxY1 = 7000.f; // it was 200.f and i fixed it to 5000.f, because of a feedback stating there was no more red enemies;

	// Create a random number generator
	std::random_device rd1;
	std::mt19937 gen1(rd1());
	std::uniform_real_distribution<float> distributionX1(minX1, maxX1);
	std::uniform_real_distribution<float> distributionY1(minY1, maxY1);

	// Loop to create multiple food objects
	for (int i = 0; i < numRottenFood; ++i)
	{
		// Generate random position within the defined range
		float randomX1 = distributionX1(gen1);
		float randomY1 = distributionY1(gen1);

		// Create a new Food object with the random position
		m_pRottenFood.push_back(new RottenFood(Point2f{ randomX1, randomY1 }, 5.f, 5.f));
	}
}

void Game::LoadPowerUps()
{
	const int numPowerUps = 5;

	float minX2 = 10.f;
	float maxX2 = 490.f;
	float minY2 = 500.f;
	float maxY2 = 7000.f; // it was 200.f and i fixed it to 5000.f, because of a feedback stating there was no more red enemies;

	// Create a random number generator
	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_real_distribution<float> distributionX2(minX2, maxX2);
	std::uniform_real_distribution<float> distributionY2(minY2, maxY2);

	// Loop to create multiple food objects
	for (int i = 0; i < numPowerUps; ++i)
	{
		// Generate random position within the defined range
		float randomX2 = distributionX2(gen2);
		float randomY2 = distributionY2(gen2);

		// Create a new Food object with the random position
		m_pPowerUps.push_back(new PowerUps(Point2f{ randomX2, randomY2 }, 5.f, 5.f));
	}
}

void Game::LoadTimerCubes()
{
	const int numTimerCubes = 5;

	float minX3 = 10.f;
	float maxX3 = 490.f;
	float minY3 = 500.f;
	float maxY3 = 7000.f; // it was 200.f and i fixed it to 5000.f, because of a feedback stating there was no more red enemies;

	// Create a random number generator
	std::random_device rd3;
	std::mt19937 gen3(rd3());
	std::uniform_real_distribution<float> distributionX3(minX3, maxX3);
	std::uniform_real_distribution<float> distributionY3(minY3, maxY3);

	// Loop to create multiple food objects
	for (int i = 0; i < numTimerCubes; ++i)
	{
		// Generate random position within the defined range
		float randomX3 = distributionX3(gen3);
		float randomY3 = distributionY3(gen3);

		// Create a new Food object with the random position
		m_pTimerCubes.push_back(new TimerCubes(Point2f{ randomX3, randomY3 }, 5.f, 5.f));
	}
}