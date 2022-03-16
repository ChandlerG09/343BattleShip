#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

//using namespace std;
//Create generic board
Board::Board(){
	
	Board b[WIDTH][HEIGHT];

	grid = new int[WIDTH*HEIGHT];	
	
	//Fill grid with 0s
	for(int i = 0; i<HEIGHT*WIDTH; i++){
		grid[i] = 0;
		std::cout << grid[i];
		if(i%WIDTH == 0)
			std::cout << "\n";
		else
			std::cout <<" ";
	}

//	grid = b;

	visible = false;
	
}

//Create a copy of the board passed in NOT WORKING
Board::Board(const Board& other){

	this->grid=new int;

/*	for(int i =0; i<WIDTH; i++){
		for(int j = 0; j<HEIGHT; j++){
			this->grid[i][j] = other.grid[i][j];
		}
	}
	this->grid = other.grid;
*/	
//	this = other
	this->visible = other.visible;

}

//Copy Operator  NOT WORKING
Board& Board::operator=(const Board& other){
	
	//Board B;
	//B.grid = *(new int[WIDTH][HEIGHT]);
	this->grid = new int[WIDTH*HEIGHT];
	this->grid = other.grid;
	this->visible = other.visible;
	//std::swap(other.grid, this->grid);
	//std::swap(other.visible, this->visible);
	
	//Copy the grid over
	/*for(int i = 0; i<HEIGHT; i++){
		for (int j=0; j<WIDTH; j++){
			other[i][j] = B[i][j];
		}
	}
	*/
	//B.visible = other.visible;
	//B(other);
	return *this;
}

//Deconstructor NOT WORKING
Board::~Board(){
	delete[] this->grid;
}

//Set Visibility of Board PROBABLY WORKING
void Board::setVisible(bool v){
	visible = v;
}

//GOOD
int& Board::Internal::operator[](int index){

	if(index >= WIDTH){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
        	}
        return grid[index];
}

//GOOD
Board::Internal Board::operator[](int index){

	if(index >= HEIGHT){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
        }
        return Board::Internal(grid+(index * WIDTH));
}

//Print
std::ostream& operator<<(std::ostream& os, Board const& b){
	std::cout<< "Test";
	return os;
}

//Count of something
int Board::count() const{

	return 0;
}

bool Board::operator< (const Board& other){

	return true;
}
