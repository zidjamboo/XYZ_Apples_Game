// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr float INITIAL_SPEED = 100.f;
constexpr float ACCELERATION = 20.f;

constexpr float PLAYER_SIZE = 20.f;

constexpr int NUM_APPLES = 20;
constexpr float APPLE_SIZE = 20.f;

constexpr int NUM_ROCKS = 3.f;
constexpr float ROCK_SIZE = 40.f;

constexpr float INITIAL_PAUSE_TIME = 3.f;

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

struct CircleSize
{
	float diameter = 0.f;
};

typedef Vector2D Position2D;
typedef Vector2D Size2D;

struct Player
{
	Position2D playerPosition;
	Size2D playerSize;
	float playerSpeed = 0.f;
	PlayerDirection playerDirection = PlayerDirection::Right;
	sf::RectangleShape playerShape;	
};

struct Apple
{
	Position2D applePosition;
	CircleSize appleSize;
	sf::CircleShape appleShape;	
};

struct Rock
{
	Position2D rockPosition;
	Size2D rocksSize;
	sf::RectangleShape rockShape;	
};

struct GameState
{
	// Player data
	Player player;

	//Apples data
	Apple apples[NUM_APPLES];

	//Rocks data
	Rock rocks[NUM_ROCKS];
	
	//Global game data
	int numEatenApples = 0;
	bool isGameOver = false;
	float pauseTimeLeft = 0.f;
};

static bool IsRectanglesCollide(
	Position2D rect1Position, Size2D rect1Size, Position2D rect2Position, Size2D rect2Size)
{
	float dx = fabs(rect1Position.x - rect2Position.x);
	float dy = fabs(rect1Position.y - rect2Position.y);
	
	return dx <= (rect1Size.x + rect2Size.x) / 2 && dy <= (rect1Size.y + rect2Size.y) / 2;
}

static bool isCirclesCollide(
	Position2D circle1Position, CircleSize circle1Size, Position2D circle2Position, CircleSize circle2Size)
{
	float dx = circle1Position.x - circle2Position.x;
	float dy = circle1Position.y - circle2Position.y;
	float squareDistance = dx * dx + dy *dy;

	float diameterSum = circle1Size.diameter + circle2Size.diameter;
	float squareRadiusSum = diameterSum * diameterSum / 4;

	return squareDistance <= squareRadiusSum;
}

static float GetRandomFloat(float min, float max)
{
	return min + rand() / (float)RAND_MAX * max;
}

static Position2D GetRandomPositionInScreen()
{
	Position2D result;

	result.x = GetRandomFloat(0, SCREEN_WIDTH);
	result.y = GetRandomFloat(0, SCREEN_HEIGHT);

	return result;
}

static void MoveObject(sf::Shape& objectShape, Position2D& objectPosition)
{
	objectPosition = GetRandomPositionInScreen();
	objectShape.setPosition(objectPosition.x, objectPosition.y);
}

static void InitPlayer(Player& player)
{
	player.playerPosition = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f};
	player.playerSize = {PLAYER_SIZE, PLAYER_SIZE};
	player.playerDirection = PlayerDirection::Right;

	player.playerShape.setSize(sf::Vector2f(player.playerSize.x, player.playerSize.y));
	player.playerShape.setFillColor(sf::Color::Red);
	player.playerShape.setOrigin(player.playerSize.x / 2.f, player.playerSize.y / 2.f);	
}

static void InitApples(Apple (&apples)[NUM_APPLES])
{
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		Apple& apple = apples[i];
		apple.appleSize.diameter = APPLE_SIZE;
		sf::CircleShape& appleShape = apple.appleShape;
		appleShape.setRadius(apple.appleSize.diameter / 2.f);
		appleShape.setFillColor(sf::Color::Green);
		appleShape.setOrigin(apple.appleSize.diameter / 2.f, apple.appleSize.diameter / 2.f);
	}	
}

static void InitRocks(Rock (&rocks)[NUM_ROCKS])
{
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		Rock& rock = rocks[i];
		rock.rocksSize = {ROCK_SIZE, ROCK_SIZE};
		sf::RectangleShape& rockShape = rock.rockShape;
		rockShape.setSize(sf::Vector2f(rock.rocksSize.x, rock.rocksSize.y));
		rockShape.setFillColor(sf::Color::Cyan);
		rockShape.setOrigin(rock.rocksSize.x / 2.f, rock.rocksSize.y / 2.f);
	}		
}

static void InitGame(GameState& gameState)
{
	InitPlayer(gameState.player);
	InitApples(gameState.apples);
	InitRocks(gameState.rocks);
}

static void RestartGame(GameState& gameState)
{
	gameState.player.playerPosition.x = SCREEN_WIDTH / 2.f;
	gameState.player.playerPosition.y = SCREEN_HEIGHT / 2.f;
	gameState.player.playerShape.setPosition(gameState.player.playerPosition.x, gameState.player.playerPosition.y);
	gameState.player.playerSpeed = INITIAL_SPEED;
	gameState.player.playerDirection = PlayerDirection::Right;

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		MoveObject(gameState.apples[i].appleShape, gameState.apples[i].applePosition);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		MoveObject(gameState.rocks[i].rockShape, gameState.rocks[i].rockPosition);
	}
}

static void UpdateGame(GameState& gameState, float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		gameState.player.playerDirection = PlayerDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		gameState.player.playerDirection = PlayerDirection::UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		gameState.player.playerDirection = PlayerDirection::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		gameState.player.playerDirection = PlayerDirection::Down;
	}


	switch (gameState.player.playerDirection)
	{
	case PlayerDirection::Right:
		{
			gameState.player.playerPosition.x += gameState.player.playerSpeed * deltaTime;
			break;
		}
	case PlayerDirection::UP:
		{
			gameState.player.playerPosition.y -= gameState.player.playerSpeed * deltaTime;
			break;
		}
	case PlayerDirection::Left:
		{
			gameState.player.playerPosition.x -= gameState.player.playerSpeed * deltaTime;
			break;
		}
	case PlayerDirection::Down:
		{
			gameState.player.playerPosition.y += gameState.player.playerSpeed * deltaTime;
			break;
		}
	}	
}


static void Draw(GameState& gameState, sf::RenderWindow& window)
{
	window.clear();
	gameState.player.playerShape.setPosition(gameState.player.playerPosition.x, gameState.player.playerPosition.y);
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		window.draw(gameState.apples[i].appleShape);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		window.draw(gameState.rocks[i].rockShape);
	}
		
	window.draw(gameState.player.playerShape);
	window.display();	
}

static void StartPause(GameState& gameState)
{
	gameState.pauseTimeLeft = INITIAL_PAUSE_TIME;
	gameState.isGameOver = false;	
}

static bool isNeedPause(GameState& gameState, float deltaTime)
{
	if (gameState.pauseTimeLeft > 0.f)
	{
		gameState.pauseTimeLeft -= deltaTime;
		return true;
	}

	return false;
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
			StartPause(gameState);
		}

		if (isNeedPause(gameState, deltaTime))
		{
			continue;
		}

		UpdateGame(gameState, deltaTime);

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (isCirclesCollide(
					gameState.player.playerPosition,
					{gameState.player.playerSize.x},
					gameState.apples[i].applePosition,
					gameState.apples[i].appleSize)
			)
			{
				MoveObject(gameState.apples[i].appleShape, gameState.apples[i].applePosition);
				++numEatenApples;
				gameState.player.playerSpeed += ACCELERATION;
			}
		}

		bool isCollapsedWithRock = false;
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (IsRectanglesCollide(
					gameState.player.playerPosition,
					gameState.player.playerSize,
					gameState.rocks[i].rockPosition,
					gameState.rocks[i].rocksSize)
			)
			{
				isCollapsedWithRock = true;
				break;
			}
		}
		
		if (
			isCollapsedWithRock ||
			gameState.player.playerPosition.x - gameState.player.playerSize.x / 2.f < 0 || gameState.player.playerPosition.x + gameState.player.playerSize.x / 2.f > SCREEN_WIDTH ||
			gameState.player.playerPosition.y - gameState.player.playerSize.y / 2.f < 0 || gameState.player.playerPosition.y + gameState.player.playerSize.y / 2.f > SCREEN_HEIGHT
		)
		{
			gameState.isGameOver = true;
		}
		
		Draw(gameState, window);
	}

	return 0;
}
