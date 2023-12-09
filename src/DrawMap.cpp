#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Headers/Global.hpp"
#include "Headers/DrawMap.hpp"

void draw_map(unsigned i_view_x, const sf::Image& i_map_sketch, sf::RenderWindow& i_window, const sf::Texture& i_map_texture, const Map& i_map)
{
	unsigned short map_end = ceil((i_view_x + SCREEN_WIDTH) / static_cast<float>(CELL_SIZE));
	unsigned short map_height = floor(i_map_sketch.getSize().y / 3.f);
	unsigned short map_start = floor(i_view_x / static_cast<float>(CELL_SIZE));

	sf::Sprite cell_sprite(i_map_texture);

	for (unsigned short a = map_start; a < map_end; a++)
	{
		for (unsigned short b = 0; b < map_height; b++)
		{
			unsigned short sprite_x = 0;
			unsigned short sprite_y = 0;

			sf::Color pixel = i_map_sketch.getPixel(a, b + 2 * map_height);
			sf::Color pixel_down = sf::Color(0, 0, 0, 0);
			sf::Color pixel_left = sf::Color(0, 0, 0, 0);
			sf::Color pixel_right = sf::Color(0, 0, 0, 0);
			sf::Color pixel_up = sf::Color(0, 0, 0, 0);

			cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);

			if (255 != pixel.a)
			{
				continue;
			}

			if (sf::Color(255, 255, 255) == pixel)
			{
				sprite_x = 8;

				if (sf::Color(255, 255, 255) == pixel_up)
				{
					sprite_y = 1;
				}

				if (sf::Color(255, 255, 255) == pixel_left)
				{
					if (sf::Color(255, 255, 255) != pixel_right)
					{
						sprite_x = 9;
					}
				}
				else if (sf::Color(255, 255, 255) == pixel_right)
				{
					sprite_x = 7;
				}
			}
			else if (sf::Color(146, 219, 0) == pixel)
			{
				sprite_x = 5;

				if (sf::Color(146, 219, 0) == pixel_left)
				{
					if (sf::Color(146, 219, 0) != pixel_right)
					{
						sprite_x = 6;
					}
				}
				else if (sf::Color(146, 219, 0) == pixel_right)
				{
					sprite_x = 4;
				}
			}
			else if (sf::Color(0, 73, 0) == pixel)
			{
				sprite_y = 1;

				if (sf::Color(0, 109, 0) == pixel_left)
				{
					if (sf::Color(0, 109, 0) != pixel_right)
					{
						sprite_x = 2;
					}
				}
				else if (sf::Color(0, 109, 0) == pixel_right)
				{
					sprite_x = 1;
				}
			}
			else if (sf::Color(0, 109, 0) == pixel)
			{
				sprite_x = 4;
				sprite_y = 1;

				if (sf::Color(0, 73, 0) == pixel_left)
				{
					sprite_x = 3;
				}
				else if (sf::Color(0, 73, 0) == pixel_right)
				{
					sprite_x = 5;
				}
			}
			else if (sf::Color(109, 255, 85) == pixel)
			{
				sprite_x = 12;

				if (sf::Color(109, 255, 85) == pixel_up)
				{
					sprite_y = 1;
				}
			}

			cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));

			i_window.draw(cell_sprite);
		}
	}
}
