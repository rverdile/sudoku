#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

void createBoard(int grid[9][9]);
bool generateSolvedBoard(int grid[9][9], int possible_nums[]);
bool isValid(int grid[9][9], int row_num, int col_num, int num);
bool foundInRow(int grid[9][9], int row_num, int num);
bool foundInColumn(int grid[9][9], int col_num, int num);
bool foundinBlock(int grid[9][9], int row_num, int col_num, int num);
void removeTiles(int grid[9][9]);
void shuffleArray(int array[], int size);
void swap(int &num1, int &num2);
vector <int> gridToVector(int grid[9][9]);
vector <sf::Text> displayBoard(vector <int> vectorized_grid, vector <int> vectorized_copy, sf::RenderWindow &window, vector <sf::RectangleShape> tile_grid, sf::Color color);
string numToString(int num);
void copyGrid(int grid[9][9], int copy[9][9]);
bool nextRowCol(int grid[9][9], int& row_num, int& col_num);
void vectorToGrid(vector <int> &vector, int grid[9][9]);
bool checkGrid(int grid[9][9]);
bool isValidCheck(int grid[9][9], int row_num, int col_num, int num);
bool foundInRowCheck(int grid[9][9], int row_num, int num);
bool foundInColumnCheck(int grid[9][9], int col_num, int num);
bool foundinBlockCheck(int grid[9][9], int row_num, int col_num, int num);

int main()
{
 	//-----Colors--------//
 	sf::Color purple(82,43,71);
 	sf::Color dark_purple(58,32,51);
 	sf::Color gray(141,170,157);
 	sf::Color light_gray(183,205,195);
 	sf::Color maroon(129,52,73);
 	sf::Color light_purple(113,81,104);
 	sf::Color red(115,29,53);

 	//---Grid Initializations-----------------------------------------------------------------------------//

 	int grid[9][9]; // game board
 	int empty_grid[9][9]; //empty board
 	int old_grid[9][9]; // holds values of grid prior to next new value being 
 	int grid_copy[9][9]; // original state of generated grid

 	for(int i = 0; i < 9; i++){		//create empty grid 
 		for(int j = 0; j < 9; j++){
 			grid[i][j] = 0;
 			empty_grid[i][j] = 0;
 		}
 	}

 	int possible_nums[9] = {1,2,3,4,5,6,7,8,9};
 	generateSolvedBoard(grid,possible_nums); //create new Sudoku board
 	copyGrid(grid, grid_copy);
 	vector <int> vectorized_grid = gridToVector(grid);
 	vector <int> vectorized_grid_copy = gridToVector(grid_copy);
 	//----------------------------------------------------------------------------------------------------//

	sf::RenderWindow window(sf::VideoMode(950,1050), "Sudoku"); //Create game window

	vector <sf::RectangleShape> tile_grid(81); //board container. each tile on Sudoku board is RectangleShape

	sf::Font font; //font object for numbers
	font.loadFromFile("LikhanNormal.ttf"); //load font being used
	vector <sf::Text> text(81); //container for all the numbers on board

	vector <sf::RectangleShape> buttons(4);
	vector <sf::Text> text_buttons(4);
	int buttons_column;

	vector <sf::RectangleShape> lines(4);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		sf::RectangleShape pop_up;
		pop_up.setSize(sf::Vector2f(300,300));
		pop_up.setOutlineColor(dark_purple);
		pop_up.setOutlineThickness(9);
		pop_up.setPosition(326,326);
		pop_up.setFillColor(gray);

		sf::Text lose_text;
		lose_text.setFont(font);
		lose_text.setString("     Sorry \nthat's incorrect.");
		lose_text.setPosition(355,415);
		lose_text.setCharacterSize(40);
		lose_text.setFillColor(sf::Color::Black);

		sf::Text win_text;
		win_text.setFont(font);
		win_text.setString("You win!");
		win_text.setPosition(400,435);
		win_text.setCharacterSize(44);
		win_text.setFillColor(sf::Color::Black);

		bool flag = false;
		bool flag2 = false;

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

		//------------------LINES SEPARTING GRIDS------------------------------------------------------------------//
		// lines[0]: vertical left, lines[1]: vertical right, lines[2]: horizontal top, lines[3]: horitzontal bottom
		lines[0].setSize(sf::Vector2f(5,1050));
		lines[0].setFillColor(red);
		lines[0].setPosition(316,0);
		window.draw(lines[0]);

		lines[1].setSize(sf::Vector2f(5,1050));
		lines[1].setFillColor(red);
		lines[1].setPosition(631,0);
		window.draw(lines[1]);

		lines[2].setSize(sf::Vector2f(900,5));
		lines[2].setFillColor(red);
		lines[2].setPosition(0,316);
		window.draw(lines[2]);

		lines[3].setSize(sf::Vector2f(900,5));
		lines[3].setFillColor(red);
		lines[3].setPosition(0,631);
		window.draw(lines[3]);


		
//---------------------------------------MOUSE POSITION STUFF FOR TILES----------------------------------------------------------------------------------------------------//
		for(int i = 0; i < tile_grid.size(); i++)
		{

			if((tile_grid[i].getGlobalBounds()).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //If tile is hovered over, light up tile
			{
				tile_grid[i].setFillColor(light_gray);

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) //if num1 key is pressed while tile is hovered over, place '1' text on tile. Same for numbers below.
				{
					vectorized_grid[i] = 1;
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					vectorized_grid[i] = 2;
				}				

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					vectorized_grid[i] = 3;
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					vectorized_grid[i] = 4;
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				{
					vectorized_grid[i] = 5;
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
				{
					vectorized_grid[i] = 6;
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
				{
					vectorized_grid[i] = 7;
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
				{
					vectorized_grid[i] = 8;
				}

				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
				{
					vectorized_grid[i] = 9;
				}
			}
		

			else{
				tile_grid[i].setFillColor(gray);
			}

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
				buttons[i].setFillColor(light_gray);
			}

			else
				buttons[i].setFillColor(gray);

			window.draw(buttons[i]);
		}
		//---------------------------------------------------------//

		//-----------BUTTONS MOUSE STUFF------------------------------//
		for(int i = 0; i < 4; i++)
		{
			if((buttons[i].getGlobalBounds()).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				buttons[i].setFillColor(light_gray);

				if(i==0)
				{
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						cout << "Starting New Game..." << endl;
						copyGrid(empty_grid, grid);
						createBoard(grid);
						copyGrid(grid, grid_copy);
						vectorized_grid = gridToVector(grid);
 						vectorized_grid_copy = gridToVector(grid_copy);

					}
				}

				else if(i==1)
				{
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						flag = true;

						cout << "Checking Your Answer..." << endl;
						for(int i = 0; i < vectorized_grid.size(); i++){ 		//This for loop removes any changes made to the pre-placed values done by the user.
							if(vectorized_grid_copy[i] != 0)						//The game cannot differentiate pre-placed tiles from user-placed tiles other than
								vectorized_grid[i] = vectorized_grid_copy[i];	//in the display.
						}

						vectorToGrid(vectorized_grid, grid);
						if(checkGrid(grid)){
							flag2 = true;
							cout << "correct" << endl;
						}
						else
							cout << "not correct" << endl;

					}
				}

				else if(i==2)
				{
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						cout << "Solving the puzzle..." << endl;
						

						vectorToGrid(vectorized_grid_copy, grid);
						generateSolvedBoard(grid, possible_nums);
						vectorized_grid = gridToVector(grid);
					}
				}

				else if(i==3)
				{
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						cout << "Closing Game..." << endl;
						window.close();
					}
					
				}
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
		text_buttons[1].setString("Check");
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



		displayBoard(vectorized_grid, vectorized_grid_copy, window, tile_grid, red);

		if(flag){

			sf::Clock clock; //starts clock
			sf::Time elapsed = clock.getElapsedTime();
			
			while(elapsed.asSeconds() < 3){
				if(flag2){
					window.draw(pop_up);
					window.draw(win_text);
					window.display();
				}
				else{
					window.draw(pop_up);
					window.draw(lose_text);
					window.display();
				}

				elapsed = clock.getElapsedTime();
			}

			flag = false;
			flag2 = false;
		}

		

		window.display();
 
	}

	return 0;
}

void createBoard(int grid[9][9]){

	//Generate board from empty grid
	int possible_nums[] = {1,2,3,4,5,6,7,8,9};
	shuffleArray(possible_nums, 9);
	generateSolvedBoard(grid,possible_nums);

	removeTiles(grid);

	cout << "Board Created." << endl;
}

bool generateSolvedBoard(int grid[9][9], int possible_nums[]){

	/*Recursive function to solve a Sudoku board. Overall, returns true if the board is solved(ie no more zeros),returns false if the board cannot be solved.*/
	/*In the scope of each recursion, returns false when a number cannot be placed in a tile and so backtracking occurs.*/
	int row_num, col_num;

	while(nextRowCol(grid,row_num,col_num)){

		for(int i = 1; i <= 9; i++){

			if(isValid(grid,row_num,col_num,possible_nums[i-1]))
			{
				grid[row_num][col_num] = possible_nums[i-1];

				if(generateSolvedBoard(grid, possible_nums))
					return true;

				grid[row_num][col_num] = 0;
			}

		}

		return false; //1 through 9 cannot be placed, must backtrack.
	}

	cout << "Board Solved." << endl;
	return true;
}

bool isValid(int grid[9][9], int row_num, int col_num, int num){

	/*Returns True if foundInRow, foundInColumn, and foundinBlock all return false, meaning the number to be placed adheres to the rules of Sudoku.*/

	if(!foundInRow(grid, row_num, num) && !foundInColumn(grid, col_num, num) && !foundinBlock(grid, row_num, col_num, num))
		return true;
	else
		return false;
}

bool foundInRow(int grid[9][9], int row_num, int num){
	/*Checks if the number to be placed in the cell is contained with the number's row. If it is, returns True.*/

	for(int i=0; i < 9; i++){
		if(num == grid[row_num][i])
			return true;
	}

	return false;
}

bool foundInColumn(int grid[9][9], int col_num, int num){
	/*Checks if the number to be placed in the cell is contained with the number's column. If it is, returns True.*/

	for(int i=0; i < 9; i++){
		if(num == grid[i][col_num])
			return true;
	}

	return false;
}

bool foundinBlock(int grid[9][9], int row_num, int col_num, int num){
	/*Checks if the number to be placed in the cell is contained with the number's 3x3 block. If it is, return True.*/

	int block_corner_row = row_num - row_num % 3; //row number of top left corner of box
	int block_corner_column = col_num - col_num % 3; //col number of top left corner of box

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(grid[block_corner_row + i][block_corner_column + j] == num)
				return true;
		}
	}

	return false;
}

void removeTiles(int grid[9][9]){

	int row_num, col_num;
	int num = 180; // num / 2 is the number of tiles being removed.

	srand(time(NULL));

	for(int i = 0; i < num; i+=2){
		row_num = rand() % 9;
		col_num = rand() % 9;
		grid[row_num][col_num] = 0;
	}

	cout << " Tiles Removed." << endl;
}

void shuffleArray(int array[], int size){
	int rand_num;
	srand(time(NULL));

	for(int i = 0; i < size; i++){

		rand_num = rand() % 8 + 1;

		swap(array[i], array[rand_num]);
	}

}

void swap(int &num1, int &num2){

	int temp = num1;
	num1 = num2;
	num2 = temp;
}

vector <int> gridToVector(int grid[9][9]){

	vector <int> vectorized_grid;

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			vectorized_grid.push_back(grid[i][j]);
		}
	}

	return vectorized_grid;
}

vector <sf::Text> displayBoard(vector <int> vectorized_grid, vector <int> vectorized_copy, sf::RenderWindow &window, vector <sf::RectangleShape> tile_grid, sf::Color color){

	sf::Font font; //font object for numbers
	font.loadFromFile("LikhanNormal.ttf"); //load font being used
	vector <sf::Text> text(81); //container for all the numbers on board

	int index = 0;
	int col_offset = 0;
	int row_offset = 0;

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){

			if(vectorized_copy[index] == 0){
				if(numToString(vectorized_grid[index]) != ""){
					text[index].setFont(font);
					text[index].setString(numToString(vectorized_grid[index]));
					text[index].setPosition(tile_grid[index].getPosition());
					text[index].setCharacterSize(80);
					text[index].setFillColor(sf::Color::Black);
				}
			}

			else{
				if(numToString(vectorized_copy[index]) != ""){
					text[index].setFont(font);
					text[index].setString(numToString(vectorized_copy[index]));
					text[index].setPosition(tile_grid[index].getPosition());
					text[index].setCharacterSize(80);
					text[index].setFillColor(color);
				}
			}

			col_offset += 105;

			window.draw(text[index]);
			index++;
		}

		col_offset = 0;
		row_offset += 105;

	}

	return text;
}

string numToString(int num){

	switch(num){

		case 1:
			return " 1";
			break;
		case 2:
			return " 2";
			break;
		case 3: 
			return " 3";
			break;
		case 4: 
			return " 4";
			break;
		case 5:
			return " 5";
			break;
		case 6:
			return " 6";
			break;
		case 7:
			return " 7";
			break;
		case 8:
			return " 8";
			break;
		case 9:
			return " 9";
			break;
		default:
			return "";
			break;

	}
}

void copyGrid(int grid[9][9], int copy[9][9]){

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			copy[i][j] = grid[i][j];
		}
	}
}

bool nextRowCol(int grid[9][9], int& row_num, int& col_num){

	/*Finds the next 0 tile in grid. A 0 tile means a number must be placed there, i.e. the board is not completely filled in yet.*/
	/*returns True if a 0 is found. returns False if no 0 is found, i.e., the board is solved. Therefore this used as the stopping*/
	/*condition for the recursive Solve() function.*/

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(grid[i][j] == 0)
			{
				row_num = i;
				col_num = j;
				return true;
			}
		}
	}

	return false; //reached end of board
}

void vectorToGrid(vector <int> &vector, int grid[9][9]){

	int count = 0;
	while(count < 81){

		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){
				grid[i][j] = vector[count];
				count++;
			}
		}
	}
}

bool checkGrid(int grid[9][9]){

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(!isValidCheck(grid, i, j, grid[i][j]))
				return false;
		}

		
	}

	return true;
}

bool isValidCheck(int grid[9][9], int row_num, int col_num, int num){

	/*Returns True if foundInRow, foundInColumn, and foundinBlock all return false, meaning the number to be placed adheres to the rules of Sudoku.*/

	if(!foundInRowCheck(grid, row_num, num) && !foundInColumnCheck(grid, col_num, num) && !foundinBlockCheck(grid, row_num, col_num, num))
		return true;
	else
		return false;
}

bool foundInRowCheck(int grid[9][9], int row_num, int num){
	/*Checks if the number to be placed in the cell is contained with the number's row. If it is, returns True.*/

	int count = 0;
	for(int i=0; i < 9; i++){
		if(num == grid[row_num][i])
			  count++;
	}

	if(count > 1) 
		return true; else return false;
}

bool foundInColumnCheck(int grid[9][9], int col_num, int num){
	/*Checks if the number to be placed in the cell is contained with the number's column. If it is, returns True.*/

	int count = 0;
	for(int i=0; i < 9; i++){
		if(num == grid[i][col_num])
			count++;
	}

	if(count > 1) return true; else return false;
}

bool foundinBlockCheck(int grid[9][9], int row_num, int col_num, int num){
	/*Checks if the number to be placed in the cell is contained with the number's 3x3 block. If it is, return True.*/

	int block_corner_row = row_num - row_num % 3; //row number of top left corner of box
	int block_corner_column = col_num - col_num % 3; //col number of top left corner of box

	int count = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(grid[block_corner_row + i][block_corner_column + j] == num)
				count++;
		}
	}

	if(count > 1) return true; else return false;
}	

