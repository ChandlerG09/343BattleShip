#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>

Board::Board(){
	Board B;
	B.grid = new int[100];
	B.visible = false;
	
}

Board::Board(const Board& other){
	Board B;
	B = other;
}

Board& Board::operator=(const Board& other){
	Board B;
	B = other;
	return B;
}

Board::~Board(){
	Board B;
}

void Board::setVisible(bool v){
	Board B;
	B.visible = v;
}

int& Board::Internal::operator[](int index){

	if(index >= WIDTH){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
        	}
        return _grid[index];
}

Board::Internal Board::operator[](int index){

	if(index >= HEIGHT){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
        }
        return Board::Internal(grid+(index * WIDTH));
}

std::ostream& operator<<(std::ostream& os, Board const& b){
}

int Board::count() const{

	return 0;
}

bool Board::operator< (const Board& other){

	return true;
}
