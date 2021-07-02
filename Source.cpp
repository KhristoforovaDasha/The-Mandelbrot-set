#include <SFML/Graphics.hpp>
#include "complex.h"
#include <vector>
#include <cmath>
using namespace sf;
struct node {
	double x0, y0, x_step, y_step;
};
int main()
{
	double x0 = -2.5, y0 = -1.5, x_step = 1 / 200.0, y_step = 1 / 200.0, x1, y1,x_old = x0,y_old = y0,x_start = 0,y_start=0;
	bool is_pressed= 0;
	std::vector <node> cond;
	RenderWindow window(VideoMode(800, 600), "SFML Works!");
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	while (window.isOpen())
	{
		Event event;
		RectangleShape rect;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				cond.push_back({ x0,y0,x_step,y_step });
				is_pressed = 1;
				x_old = x0;
				y_old = y0;
				x_start = event.mouseButton.x;
				y_start = event.mouseButton.y;
			}
			if (event.type == Event::MouseButtonReleased) {
				if (x_start != double(event.mouseButton.x) && y_start != double(event.mouseButton.y)) {
					x0 += std::min(double(event.mouseButton.x), x_start) * x_step;
					y0 += std::min(double(event.mouseButton.y), y_start) * y_step;
					x1 = std::max(double(event.mouseButton.x), x_start) * x_step + x_old;
					y1 = std::max(double(event.mouseButton.y), y_start) * y_step + y_old;
					x_step = std::abs(x1 - x0) / width;
					y_step = std::abs(y1 - y0) / height;
				}
				is_pressed = 0;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				if (cond.size()) {
					node cnt = cond.back();
					x0 = cnt.x0, y0 = cnt.y0, x_step = cnt.x_step, y_step = cnt.y_step;
					cond.pop_back();
				}
			}
		}
		window.clear(Color(255, 255, 255, 0));
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				complex val1(i*x_step + x0, j*y_step + y0);
				complex val2(0, 0);
				int flag = 0;
				for (int g = 0; g < 150; g++) {
					val2 = val2 * val2 + val1;
					if (val2.len() >= 2) {
						flag = 1;
						break;
					}
				}
				double sz = val2.len();
				if (!flag) {
					sf::Vertex point(sf::Vector2f(i, j), sf::Color::Black);
					window.draw(&point, 1, sf::Points);
				}
				else {
					std::vector <int> num = { 130,1,52,45,120,89,209,156,100 };
					int r = num[0] * (sin(sz + num[1])) + num[2];
					int g = num[3] * (sin(sz + num[4])) + num[5];
					int b = num[6] * (sin(sz + num[7])) + num[8];
					sf::Vertex point(sf::Vector2f(i, j), sf::Color(r,g,b));
					window.draw(&point, 1, sf::Points);
				}
			}
		}
		if (is_pressed) {
			rect.setSize(sf::Vector2f(Mouse::getPosition(window)) - sf::Vector2f(x_start, y_start));
			rect.setPosition(x_start, y_start);
			rect.setFillColor(sf::Color(0,0,0,0));
			rect.setOutlineColor(sf::Color::White);
			rect.setOutlineThickness(1);
			window.draw(rect);
		}
		window.display();
	}
	return 0;
}