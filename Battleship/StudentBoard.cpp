#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

//using namespace std;
//Create generic board
Board::Board(){
		
	//Allocate Memory
	this->grid = new int[WIDTH*HEIGHT];	
	
	//Fill the grid with Empty Values	
	for(int i = 0; i<WIDTH*HEIGHT; i++){
		this->grid[i] = EMPTY;
	}
}

//Create a copy of the board passed in
Board::Board(const Board& other){
	
	//Create the new Board Object
	Board b;	
	
	//Create new space for the grid so they aren't the same
	b.grid=new int[WIDTH*HEIGHT];
	
	//Copy the values of the old Board into the new one	
	for(int i = 0; i < WIDTH*HEIGHT; i++){
		b.grid[i] = this->grid[i];
	}
}

//Copy Operator  PROB WORKING
Board& Board::operator=(Board& other){
	
	std::swap(this->grid, other.grid);
	std::swap(this->visible,  other.visible);
	
	return *this;
}

//Deconstructor
Board::~Board(){
	delete[] this->grid;
}

//Set Visibility of Board
void Board::setVisible(bool v){

	this->visible = v;
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

	Board printed = Board();
	printed.grid = b.grid;	

	for(int i = 0; i<HEIGHT; i++){
		for(int j = 0; j<WIDTH; j++){
			if(printed[j][i] == EMPTY){
				os<<"-\t";
			}
			else if(printed[j][i] == MISS){
				os<<"M\t";
			}
			else if(printed[j][i] == HIT){
				os<<"H\t";
			}
			else{
				os<<printed[j][i] << "\t";
			}
		}
		os<<"\n";
	}

	return os;
}

//Count of hits on the board
int Board::count() const{
	
	int count = 0;

	//Go through the entire Grid and get the total
	for(int i =0; i<WIDTH*HEIGHT; i++){
		if(this->grid[i] == HIT)
			 count++;
	}
	return count;
}

bool Board::operator< (const Board& other){
	
	if(this->count() < other.count())
		return true;

	return false;
}
