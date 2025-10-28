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

enum class PlayerDirection
{
	Right = 0,
	UP,
	Left,
	Down
};

struct Vector2D
{
	float x = 0;
	float y = 0;
};

typedef Vector2D Position2D;

static void MoveObject(sf::Shape& objectShape, Position2D& objectPosition)
{
	objectPosition.x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
	objectPosition.y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
	objectShape.setPosition(objectPosition.x, objectPosition.y);
}

static void RestartGame(
	sf::RectangleShape& playerShape, Position2D& playerPosition, float& playerSpeed, PlayerDirection& playerDirection,
	sf::CircleShape (&applesShape)[NUM_APPLES], Position2D (&applesPositions)[NUM_APPLES],
	sf::RectangleShape (&rocksShape)[NUM_ROCKS], Position2D (&rocksPositions)[NUM_ROCKS]
)
{
	playerPosition.x = SCREEN_WIDTH / 2.f;
	playerPosition.y = SCREEN_HEIGHT / 2.f;
	playerShape.setPosition(playerPosition.x, playerPosition.y);
	playerSpeed = INITIAL_SPEED;
	playerDirection = PlayerDirection::Right;

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		MoveObject(applesShape[i], applesPositions[i]);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		MoveObject(rocksShape[i], rocksPositions[i]);
	}
}

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	bool gameOver = false;
	
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");
	Position2D playerPosition = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f};
	float playerSpeed;
	PlayerDirection playerDirection = PlayerDirection::Right;

	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);

	Position2D applesPositions[NUM_APPLES];
	sf::CircleShape applesShape[NUM_APPLES];

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		sf::CircleShape& appleShape = applesShape[i];
		appleShape.setRadius(APPLE_SIZE / 2.f);
		appleShape.setFillColor(sf::Color::Green);
		appleShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	}

	Position2D rocksPositions[NUM_ROCKS];
	sf::RectangleShape rocksShape[NUM_ROCKS];

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		sf::RectangleShape& rockShape = rocksShape[i];
		rockShape.setSize(sf::Vector2f(ROCK_SIZE, ROCK_SIZE));
		rockShape.setFillColor(sf::Color::Cyan);
		rockShape.setOrigin(ROCK_SIZE / 2.f, ROCK_SIZE / 2.f);
	}

	RestartGame(
		playerShape, playerPosition, playerSpeed, playerDirection,
		applesShape, applesPositions,
		rocksShape, rocksPositions
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
				playerShape, playerPosition, playerSpeed, playerDirection,
				applesShape, applesPositions,
				rocksShape, rocksPositions
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
			playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerDirection = PlayerDirection::UP;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerDirection = PlayerDirection::Down;
		}


		switch (playerDirection)
		{
		case PlayerDirection::Right:
			{
				playerPosition.x += playerSpeed * deltaTime;
				break;
			}
		case PlayerDirection::UP:
			{
				playerPosition.y -= playerSpeed * deltaTime;
				break;
			}
		case PlayerDirection::Left:
			{
				playerPosition.x -= playerSpeed * deltaTime;
				break;
			}
		case PlayerDirection::Down:
			{
				playerPosition.y += playerSpeed * deltaTime;
				break;
			}
		}

		

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			float squareDistance = (playerPosition.x - applesPositions[i].x) * (playerPosition.x - applesPositions[i].x) +
				(playerPosition.y -applesPositions[i].y) * (playerPosition.y -applesPositions[i].y);
			float squareRadiusSum = (PLAYER_SIZE + APPLE_SIZE) * (PLAYER_SIZE + APPLE_SIZE) / 4;
			if (squareDistance <= squareRadiusSum)
			{
				MoveObject(applesShape[i], applesPositions[i]);
				++numEatenApples;
				playerSpeed += ACCELERATION;
			}
		}

		bool isCollapsedWithRock = false;
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			float dx = abs(playerPosition.x - rocksPositions[i].x);
			float dy = abs(playerPosition.y - rocksPositions[i].y);
			float sum = (PLAYER_SIZE + ROCK_SIZE) / 2;
			if (dx <= sum && dy <= sum)
			{
				isCollapsedWithRock = true;
				break;
			}
		}
		
		if (
			isCollapsedWithRock ||
			playerPosition.x - PLAYER_SIZE / 2.f < 0 || playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			playerPosition.y - PLAYER_SIZE / 2.f < 0 || playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT
		)
		{
			gameOver = true;
		}
		
		window.clear();
		playerShape.setPosition(playerPosition.x, playerPosition.y);
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
