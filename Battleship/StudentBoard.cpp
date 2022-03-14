#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//Create generic board
Board::Board(){

	Board B;
	int gameBoard[WIDTH][HEIGHT];

	std::vector<std::vector<int*>> vect = { } ;

	//vect = new int[WIDTH][HEIGHT];
	
//	B.grid = new int[WIDTH];
	
	//Fill grid with 0s
	for(int i = 0; i<HEIGHT; i++){
		for (int j=0; j<WIDTH; j++){
			vect[i][j] = 0;
		}
	}

	*B.grid = &gameBoard;


	B.visible = false;
	
}

//Create a copy of the board passed in PROB WORKING
Board::Board(const Board& other){
	Board B(other);
}

//Copy NOT WORKING
Board& Board::operator=(const Board& other){
	
	Board B;
	B.grid = *(new int[WIDTH][HEIGHT]);

	//Copy the grid over
	for(int i = 0; i<HEIGHT; i++){
		for (int j=0; j<WIDTH; j++){
			other[i][j] = B[i][j];
		}
	}
	B.visible = other.visible;
	B(other);
	return B;
}

//Deconstructor NOT WORKING
Board::~Board(){
	delete[] Board;
}

//Set Visibility of Board PROBABLY WORKING
void Board::setVisible(bool v){
	Board B;
	B.visible = v;
}

//GOOD
int& Board::Internal::operator[](int index){

	if(index >= WIDTH){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
        	}
        return _grid[index];
}

//GOOD
Board::Internal Board::operator[](int index){

	if(index >= HEIGHT){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
        }
        return Board::Internal(grid+(index * WIDTH));
}

//Idk what this does
std::ostream& operator<<(std::ostream& os, Board const& b){
//	return os;
}

//Count of something
int Board::count() const{

	return 0;
}

bool Board::operator< (const Board& other){

	return true;
}
