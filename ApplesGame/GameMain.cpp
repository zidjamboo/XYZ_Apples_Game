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
typedef Vector2D Size2D;

struct GameState
{
	// Player data
	Position2D playerPosition;
	Size2D playerSize;
	float playerSpeed = 0.f;
	PlayerDirection playerDirection = PlayerDirection::Right;
	sf::RectangleShape playerShape;

	//Apples data
	Position2D applesPositions[NUM_APPLES];
	sf::CircleShape applesShapes[NUM_APPLES];

	int numEatenApples = 0;
	
	//Rocks data
	Position2D rocksPositions[NUM_ROCKS];
	Size2D rocksSize[NUM_ROCKS];
	sf::RectangleShape rocksShapes[NUM_ROCKS];

	//Global game data
	bool isGameOver = false;
	float pauseTimeLeft = 0.f;
};

static bool IsRectanglesCollide(
	Position2D rect1Position, Size2D rect1Size, Position2D rect2Position, Size2D rect2Size
)
{
	float dx = fabs(rect1Position.x - rect2Position.x);
	float dy = fabs(rect1Position.y - rect2Position.y);
	
	return dx <= (rect1Size.x + rect2Size.x) / 2 && dy <= (rect1Size.y + rect2Size.y) / 2;
}

static float GetRandomAxeInScreen(float axeLength)
{
	return rand() / (float)RAND_MAX * axeLength;
}

static Position2D GetRandomPositionInScreen()
{
	Position2D result;

	result.x = GetRandomAxeInScreen(SCREEN_WIDTH);
	result.y = GetRandomAxeInScreen(SCREEN_HEIGHT);

	return result;
}

static void MoveObject(sf::Shape& objectShape, Position2D& objectPosition)
{
	objectPosition = GetRandomPositionInScreen();
	objectShape.setPosition(objectPosition.x, objectPosition.y);
}

static void InitGame(GameState& gameState)
{
	gameState.playerPosition = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f};
	gameState.playerSize = {PLAYER_SIZE, PLAYER_SIZE};
	gameState.playerDirection = PlayerDirection::Right;

	gameState.playerShape.setSize(sf::Vector2f(gameState.playerSize.x, gameState.playerSize.y));
	gameState.playerShape.setFillColor(sf::Color::Red);
	gameState.playerShape.setOrigin(gameState.playerSize.x / 2.f, gameState.playerSize.y / 2.f);

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		sf::CircleShape& appleShape = gameState.applesShapes[i];
		appleShape.setRadius(APPLE_SIZE / 2.f);
		appleShape.setFillColor(sf::Color::Green);
		appleShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		gameState.rocksSize[i] = {ROCK_SIZE, ROCK_SIZE};
		sf::RectangleShape& rockShape = gameState.rocksShapes[i];
		rockShape.setSize(sf::Vector2f(gameState.rocksSize[i].x, gameState.rocksSize[i].y));
		rockShape.setFillColor(sf::Color::Cyan);
		rockShape.setOrigin(gameState.rocksSize[i].x / 2.f, gameState.rocksSize[i].y / 2.f);
	}	
}

static void RestartGame(GameState& gameState)
{
	gameState.playerPosition.x = SCREEN_WIDTH / 2.f;
	gameState.playerPosition.y = SCREEN_HEIGHT / 2.f;
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);
	gameState.playerSpeed = INITIAL_SPEED;
	gameState.playerDirection = PlayerDirection::Right;

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		MoveObject(gameState.applesShapes[i], gameState.applesPositions[i]);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		MoveObject(gameState.rocksShapes[i], gameState.rocksPositions[i]);
	}
}

static void UpdateGame(GameState& gameState, float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		gameState.playerDirection = PlayerDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		gameState.playerDirection = PlayerDirection::UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		gameState.playerDirection = PlayerDirection::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		gameState.playerDirection = PlayerDirection::Down;
	}


	switch (gameState.playerDirection)
	{
	case PlayerDirection::Right:
		{
			gameState.playerPosition.x += gameState.playerSpeed * deltaTime;
			break;
		}
	case PlayerDirection::UP:
		{
			gameState.playerPosition.y -= gameState.playerSpeed * deltaTime;
			break;
		}
	case PlayerDirection::Left:
		{
			gameState.playerPosition.x -= gameState.playerSpeed * deltaTime;
			break;
		}
	case PlayerDirection::Down:
		{
			gameState.playerPosition.y += gameState.playerSpeed * deltaTime;
			break;
		}
	}	
}


static void Draw(GameState& gameState, sf::RenderWindow& window)
{
	window.clear();
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		window.draw(gameState.applesShapes[i]);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		window.draw(gameState.rocksShapes[i]);
	}
		
	window.draw(gameState.playerShape);
	window.display();	
}

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

	GameState gameState;
	InitGame(gameState);
	RestartGame(gameState);

	int numEatenApples = 0;

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		if (gameState.isGameOver)
		{
			RestartGame(gameState);
			
			gameState.pauseTimeLeft = INITIAL_PAUSE_TIME;

			gameState.isGameOver = false;
		}

		if (gameState.pauseTimeLeft > 0.f)
		{
			gameState.pauseTimeLeft -= deltaTime;
			continue;
		}

		UpdateGame(gameState, deltaTime);

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			float squareDistance =
				(gameState.playerPosition.x - gameState.applesPositions[i].x) *
				(gameState.playerPosition.x - gameState.applesPositions[i].x) +
				(gameState.playerPosition.y - gameState.applesPositions[i].y) *
				(gameState.playerPosition.y - gameState.applesPositions[i].y);
			float squareRadiusSum = (PLAYER_SIZE + APPLE_SIZE) * (PLAYER_SIZE + APPLE_SIZE) / 4;
			if (squareDistance <= squareRadiusSum)
			{
				MoveObject(gameState.applesShapes[i], gameState.applesPositions[i]);
				++numEatenApples;
				gameState.playerSpeed += ACCELERATION;
			}
		}

		bool isCollapsedWithRock = false;
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (IsRectanglesCollide(
					gameState.playerPosition,
					gameState.playerSize,
					gameState.rocksPositions[i],
					gameState.rocksSize[i])
			)
			{
				isCollapsedWithRock = true;
				break;
			}
		}
		
		if (
			isCollapsedWithRock ||
			gameState.playerPosition.x - gameState.playerSize.x / 2.f < 0 || gameState.playerPosition.x + gameState.playerSize.x / 2.f > SCREEN_WIDTH ||
			gameState.playerPosition.y - gameState.playerSize.y / 2.f < 0 || gameState.playerPosition.y + gameState.playerSize.y / 2.f > SCREEN_HEIGHT
		)
		{
			gameState.isGameOver = true;
		}
		
		Draw(gameState, window);
	}

	return 0;
}
