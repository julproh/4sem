#include <chrono>
#include <ctime>
#include <cstdint>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

using namespace sf;

enum class Direction
{
	down,
	left,
	right,
	up
};

struct Snake
{
	int x;
	int y;
};

struct Fruit
{
	int x;
	int y;
};

void step(Direction direction, std::vector < Snake > & snake, Fruit & fruit, const int N, const int M)
{
	static std::default_random_engine dre;
	static std::uniform_int_distribution <> uid_x(0, N - 1);
	static std::uniform_int_distribution <> uid_y(0, M - 1);

	for (std::size_t i = snake.size() - 1; i > 0; --i)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (direction == Direction::down)  snake[0].y++;
	if (direction == Direction::left)  snake[0].x--;
	if (direction == Direction::right) snake[0].x++;
	if (direction == Direction::up)    snake[0].y--;

	if ((snake[0].x == fruit.x) && (snake[0].y == fruit.y))
	{
		snake.push_back(snake.back());

		fruit.x = uid_x(dre);
		fruit.y = uid_y(dre);
	}

	if (snake[0].x <= -1) snake[0].x = N - 1;
	if (snake[0].x >= N) snake[0].x = 0;
	if (snake[0].y <= -1) snake[0].y = M - 1;
	if (snake[0].y >= M) snake[0].y = 0;

	//for (std::size_t i = 1; snake.size() > 2 && i < snake.size(); ++i)
	//{
	//	if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
	//	{
	//		snake.erase(snake.begin() + i, snake.end());
	//		break;
	//	}
	//}
}

int main(int argc, char ** argv)
{
	const int N = 30;
	const int M = 20;

	const std::size_t size = 16;

	RenderWindow application(VideoMode(size * N, size * M), "SNAKE");

	Texture texture_1, texture_2, texture_3;

	texture_1.loadFromFile("images/white.png");
	texture_2.loadFromFile("images/red.png");
	texture_3.loadFromFile("images/green.png");

	Sprite sprite_1(texture_1);
	Sprite sprite_2(texture_2);
	Sprite sprite_3(texture_3);

	Direction direction = Direction::right;

	std::vector < Snake > snake = { {0, 0}, { 1, 0 }, { 2, 0 }, { 3, 0 } };

	Fruit fruit = { 10, 10 };

	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();

	const std::chrono::microseconds delay(80000);

	std::chrono::microseconds timer(0);

	while (application.isOpen())
	{
		timer += std::chrono::duration_cast <std::chrono::microseconds> (
			std::chrono::steady_clock::now() - time_point);

		time_point = std::chrono::steady_clock::now();

		Event event;

		while (application.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				application.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))  direction = Direction::left;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = Direction::right;
		if (Keyboard::isKeyPressed(Keyboard::Up))    direction = Direction::up;
		if (Keyboard::isKeyPressed(Keyboard::Down))  direction = Direction::down;

		if (timer > delay)
		{
			timer = std::chrono::microseconds(0);
			step(direction, snake, fruit, N, M);
		}

		application.clear(Color::White);

		for (std::size_t i = 0; i < N; ++i)
		{
			for (std::size_t j = 0; j < M; ++j)
			{
				sprite_1.setPosition(
					static_cast <float> (i * size),
					static_cast <float> (j * size));

				application.draw(sprite_1);
			}
		}

		for (const auto & part : snake)
		{
			sprite_2.setPosition(
				static_cast <float> (part.x * size),
				static_cast <float> (part.y * size));

			application.draw(sprite_2);
		}

		{
			sprite_3.setPosition(
				static_cast <float> (fruit.x * size),
				static_cast <float> (fruit.y * size));

			application.draw(sprite_3);
		}

		application.display();
	}

	system("pause");

	return EXIT_SUCCESS;
}