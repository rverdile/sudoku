#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
 
	//Create Game Window
	sf::RenderWindow window(sf::VideoMode(950,950), "Sudoku");

	//board container. each tile on the Sudoku board is a RectangleShape.
	vector <sf::RectangleShape> tile_grid(81);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();

		}

		int index = 0; //index into tile_grid, goes up to 80.
		int column_offset = 0;
		int row_offset = 0;
		for(int i=0; i < 9; i++) //i rows, j columns
		{
			for(int j=0; j < 9; j++)
			{
				tile_grid[index].setSize(sf::Vector2f(100,100));			/* this loop places the 80 RectagleShape objects into a tile floor-like pattern by   */
				tile_grid[index].setFillColor(sf::Color::Red);				/* by offsetting the x (row) and/or y (column) positions a fixed amount for  */
				tile_grid[index].setOutlineThickness(5);					/*  each "tile" that is placed. An entire row is placed, then the column is shifted down 1*/
				tile_grid[index].setPosition(5+column_offset,5+row_offset); /*  and the next row is placed.*/

				column_offset += 105;

				window.draw(tile_grid[index]);
				index++;
			}

			column_offset = 0;
			row_offset += 105;
		}

		window.display();

	}


}