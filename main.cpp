#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;


int main()
{
 	//-----Colors--------//
 	sf::Color purple(82,43,71);
 	sf::Color dark_purple(58,32,51);
 	sf::Color gray(141,170,157);
 	sf::Color white(251,245,243);



	sf::RenderWindow window(sf::VideoMode(950,1050), "Sudoku"); //Create game window

	vector <sf::RectangleShape> tile_grid(81); //board container. each tile on Sudoku board is RectangleShape

	sf::Font font; //font object for numbers
	font.loadFromFile("LikhanNormal.ttf"); //load font being used
	vector <sf::Text> text(81); //container for all the numbers on board

	vector <sf::RectangleShape> buttons(4);
	vector <sf::Text> text_buttons(4);
	int buttons_column;

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
				tile_grid[index].setOutlineColor(dark_purple);			/* by offsetting the x (row) and/or y (column) positions a fixed amount for  */
				tile_grid[index].setOutlineThickness(5);					/*  each "tile" that is placed. An entire row is placed, then the column is shifted down 1*/
				tile_grid[index].setPosition(5+column_offset,5+row_offset); /*  and the next row is placed.*/

				column_offset += 105;

				window.draw(tile_grid[index]);
				index++;
			}

			column_offset = 0;
			row_offset += 105;
		}
		
//---------------------------------------MOUSE POSITION STUFF FOR TILES----------------------------------------------------------------------------------------------------//
		for(int i = 0; i < tile_grid.size(); i++)
		{

			if((tile_grid[i].getGlobalBounds()).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //If tile is hovered over, light up tile
			{
				tile_grid[i].setFillColor(sf::Color::White);

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) //if num1 key is pressed while tile is hovered over, place '1' text on tile. Same for numbers below.
				{
					text[i].setFont(font);
					text[i].setString(" 1");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					text[i].setFont(font);
					text[i].setString(" 2");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);					
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					text[i].setFont(font);
					text[i].setString(" 3");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					text[i].setFont(font);
					text[i].setString(" 4");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				{
					text[i].setFont(font);
					text[i].setString(" 5");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);					
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
				{
					text[i].setFont(font);
					text[i].setString(" 6");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
				{
					text[i].setFont(font);
					text[i].setString(" 7");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
				{
					text[i].setFont(font);
					text[i].setString(" 8");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
				{
					text[i].setFont(font);
					text[i].setString(" 9");
					text[i].setPosition(tile_grid[i].getPosition());
					text[i].setCharacterSize(80);
					text[i].setFillColor(sf::Color::Blue);
				}
			}

			else
				tile_grid[i].setFillColor(gray);


			window.draw(text[i]);


		}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

		//---Background Behind Buttons-----------------------------//
		sf::RectangleShape buttons_background;
		buttons_background.setSize(sf::Vector2f(1000,1000));
		buttons_background.setFillColor(purple);
		buttons_background.setPosition(0,950);
		buttons_column = 0;
		window.draw(buttons_background);
		//--------------------------------------------------------//

		//-----------Buttons--------------------------------------//
		for(int i = 0; i < 4; i++)
		{

			buttons[i].setSize(sf::Vector2f(175,50));
			buttons[i].setOutlineColor(dark_purple);
			buttons[i].setOutlineThickness(9);
			buttons[i].setPosition(40+buttons_column,955);

			buttons_column += 230;

			window.draw(buttons[i]);

		

			if((buttons[i].getGlobalBounds()).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) 
			{
				buttons[i].setFillColor(white);
			}

			else
				buttons[i].setFillColor(gray);

			window.draw(buttons[i]);
		}
		//---------------------------------------------------------//

		//-----------BUTTONS MOUSE STUFF------------------------------//
		for(int i = 0; i < 4; i++)
		{
			if((text_buttons[i].getGlobalBounds()).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				buttons[i].setFillColor(white);
			}

			else
				buttons[i].setFillColor(gray);

			window.draw(buttons[i]);
		}


		//----------BUTTONS TEXT-----------------------------------//
		text_buttons[0].setFont(font);
		text_buttons[0].setString("New Game");
		text_buttons[0].setPosition(44,955);
		text_buttons[0].setCharacterSize(36);
		text_buttons[0].setFillColor(sf::Color::Black);
		window.draw(text_buttons[0]);

		text_buttons[1].setFont(font);
		text_buttons[1].setString("Reset");
		text_buttons[1].setPosition(310,955);
		text_buttons[1].setCharacterSize(37);
		text_buttons[1].setFillColor(sf::Color::Black);
		window.draw(text_buttons[1]);

		text_buttons[2].setFont(font);
		text_buttons[2].setString("Solve");
		text_buttons[2].setPosition(545,955);
		text_buttons[2].setCharacterSize(37);
		text_buttons[2].setFillColor(sf::Color::Black);
		window.draw(text_buttons[2]);

		text_buttons[3].setFont(font);
		text_buttons[3].setString("Close");
		text_buttons[3].setPosition(770,955);
		text_buttons[3].setCharacterSize(37);
		text_buttons[3].setFillColor(sf::Color::Black);
		window.draw(text_buttons[3]);
		//-----------------------------------------------------------//

		window.display();
 
	}


}
