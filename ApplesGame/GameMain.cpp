// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const float INITIAL_SPEED = 100.f;
const float ACCELERATION = 20.f;

const float PLAYER_SIZE = 20.f;

const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.f;

const int NUM_ROCKS = 3.f;
const float ROCK_SIZE = 40.f;

const float INITIAL_PAUSE_TIME = 3.f;

static void MoveObject(sf::Shape& objectShape, float& objectX, float& objectY)
{
	objectX = rand() / (float)RAND_MAX * SCREEN_WIDTH;
	objectY = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
	objectShape.setPosition(objectX, objectY);
}

static void RestartGame(
	sf::RectangleShape& playerShape, float& playerX, float& playerY, float& playerSpeed, int& playerDirection,
	sf::CircleShape (&applesShape)[NUM_APPLES], float (&applesX)[NUM_APPLES], float (&applesY)[NUM_APPLES],
	sf::RectangleShape (&rocksShape)[NUM_ROCKS], float (&rocksX)[NUM_ROCKS], float (&rocksY)[NUM_ROCKS]
)
{
	playerX = SCREEN_WIDTH / 2.f;
	playerY = SCREEN_HEIGHT / 2.f;
	playerShape.setPosition(playerX, playerY);
	playerSpeed = INITIAL_SPEED;
	playerDirection = 0;

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		MoveObject(applesShape[i],applesX[i], applesY[i]);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		MoveObject(rocksShape[i], rocksX[i], rocksY[i]);
	}
}

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	bool gameOver = false;
	
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");
	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGHT / 2.f;
	float playerSpeed;
	int playerDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - Down

	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);

	float applesX[NUM_APPLES];
	float applesY[NUM_APPLES];
	sf::CircleShape applesShape[NUM_APPLES];

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		sf::CircleShape& appleShape = applesShape[i];
		appleShape.setRadius(APPLE_SIZE / 2.f);
		appleShape.setFillColor(sf::Color::Green);
		appleShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	}

	float rocksX[NUM_ROCKS];
	float rocksY[NUM_ROCKS];
	sf::RectangleShape rocksShape[NUM_ROCKS];

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		sf::RectangleShape& rockShape = rocksShape[i];
		rockShape.setSize(sf::Vector2f(ROCK_SIZE, ROCK_SIZE));
		rockShape.setFillColor(sf::Color::Cyan);
		rockShape.setOrigin(ROCK_SIZE / 2.f, ROCK_SIZE / 2.f);
	}

	RestartGame(
		playerShape, playerX, playerY, playerSpeed, playerDirection,
		applesShape, applesX, applesY,
		rocksShape, rocksX, rocksY
	);

	int numEatenApples = 0;

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	float pauseTimeLeft = 0.f;
	while (window.isOpen())
	{
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		if (gameOver)
		{
			RestartGame(
				playerShape, playerX, playerY, playerSpeed, playerDirection,
				applesShape, applesX, applesY,
				rocksShape, rocksX, rocksY
			);
			
			pauseTimeLeft = INITIAL_PAUSE_TIME;

			gameOver = false;
		}

		if (pauseTimeLeft > 0.f)
		{
			pauseTimeLeft -= deltaTime;
			continue;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playerDirection = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerDirection = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerDirection = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerDirection = 3;
		}

		if (playerDirection == 0)
		{
			playerX += playerSpeed * deltaTime;
		}
		else if (playerDirection == 1)
		{
			playerY -= playerSpeed * deltaTime;
		} else if (playerDirection == 2)
		{
			playerX -= playerSpeed * deltaTime;
		}
		else if (playerDirection == 3)
		{
			playerY += playerSpeed * deltaTime;
		}

		

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			float squareDistance = (playerX - applesX[i]) * (playerX - applesX[i]) +
				(playerY - applesY[i]) * (playerY - applesY[i]);
			float squareRadiusSum = (PLAYER_SIZE + APPLE_SIZE) * (PLAYER_SIZE + APPLE_SIZE) / 4;
			if (squareDistance <= squareRadiusSum)
			{
				MoveObject(applesShape[i], applesX[i], applesY[i]);
				++numEatenApples;
				playerSpeed += ACCELERATION;
			}
		}

		bool isCollapsedWithRock = false;
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			float dx = abs(playerX - rocksX[i]);
			float dy = abs(playerY - rocksY[i]);
			float sum = (PLAYER_SIZE + ROCK_SIZE) / 2;
			if (dx <= sum && dy <= sum)
			{
				isCollapsedWithRock = true;
				break;
			}
		}
		
		if (
			isCollapsedWithRock ||
			playerX - PLAYER_SIZE / 2.f < 0 || playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			playerY - PLAYER_SIZE / 2.f < 0 || playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT
		)
		{
			gameOver = true;
		}
		
		window.clear();
		playerShape.setPosition(playerX, playerY);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			window.draw(applesShape[i]);
		}

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			window.draw(rocksShape[i]);
		}
		
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
