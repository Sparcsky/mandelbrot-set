#include <SFML\Graphics.hpp>

using namespace sf;

int mandelSet(double dx, double dy, double c_Re, double c_Im, int maxIterator);
Color  setPixelColor(int z, int maxIterator);

int main()
{
	unsigned int width = 700;
	unsigned int height = 700;

	double minRe = -1.2;
	double minIm = -2.0;
	double maxRe = 1.2;
	double maxIm = 2.0;
	float zoom = 1;
	float offsetX = 0;
	float offsetY = 0;

	double re = (maxRe - minRe) / (width);
	double im = (maxIm - minIm) / (height);

	const int maxIterator = 1000;

	sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot set");

	Image image;
	image.create(width, height, sf::Color(0, 0, 0.0, 0));

	Texture texture;
	texture.loadFromImage(image);
	Sprite sprite(texture);
	sf::Event event; Keyboard keyboard;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (keyboard.isKeyPressed(keyboard.E))
		{
			zoom *= .9;
		}
		if (keyboard.isKeyPressed(keyboard.A))
		{
			offsetX -= .1;
		}
		if (keyboard.isKeyPressed(keyboard.D))
		{
			offsetX += .1;
		}
		if (keyboard.isKeyPressed(keyboard.W))
		{
			offsetY -= .1;
		}
		if (keyboard.isKeyPressed(keyboard.S))
		{
			offsetY += .1;
		}

		for (size_t y = 0; y < height; y++)
		{
			double c_Im = ((y * im) + minIm) * zoom + offsetY;

		 	for (size_t x = 0; x < width; x++)
			{
				double c_Re = ((x * re) + minRe) * zoom + offsetX;
				double dy = 0, dx = 0;

				int z = mandelSet(dx, dy, c_Re, c_Im, maxIterator);
				Color color = setPixelColor(z, maxIterator);

				image.setPixel(x, y, color);
			}
		}
		texture.update(image);

		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}

int mandelSet(double dx, double dy, double c_Re, double c_Im, int maxIterator)
{
	int z = 0;
	while (dx * dx + dy * dy < 4 && z < maxIterator)
	{
		double temp = ((dx * dx - dy * dy) + c_Re);
		dy = 2 * dx * dy + c_Im;
		dx = temp;
		z++;
	}
	return z;
}

Color setPixelColor(int z, int maxIterator)
{
	Color color;
	if (z == maxIterator)
	{
		color = Color::Black;
	}
	else
	{
		color.r = z;
		color.g = z;
		color.b = z % 255;
	}
	 return color;
}
