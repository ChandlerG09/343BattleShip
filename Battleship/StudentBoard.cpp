#include "Board.hpp"
#include "BoardValues.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

/*
 *This class is used to create a Board for the game Battleship
 *Each Board keeps track of the grid as well as what spots have been fired on
 *
 * @author Chandler Glowicki and Liam Mazure
 * @version Winter 2022
 */
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
	
	
	//Create new space for the grid so they aren't the same
	this->grid=new int[WIDTH*HEIGHT];
	
	//Copy the values of the old Board into the new one	
	for(int i = 0; i < WIDTH*HEIGHT; i++){
		this->grid[i] = other.grid[i];
	}
	
	//Set the visibility
	this->visible = other.visible;
}

/*This Function is uesd to create a copy of a board that
 *is being passed in
 *@param other is the board that we want the data to be copied from
 *@return the reference of the 'this' board
 */
Board& Board::operator=(Board& other){
	
	this->grid=new int[WIDTH*HEIGHT];

	//Copy the values of the old Board into the new one     
	for(int i = 0; i < WIDTH*HEIGHT; i++){
		this->grid[i] = other.grid[i];
	}
	
	//Set the visibility
	this->visible = other.visible;

	//Return Ourself
	return *this;
}

/*This function is used to clear the memory
 *any board objects when we are done
 *using them
 */
Board::~Board(){
	delete[] this->grid;
}

/*This function is used to set the
 * visibility of the board
 * @param v is true for visible or false for not
 */
void Board::setVisible(bool v){
	
	//Set the visibility
	this->visible = v;
}

/*
 *This function is used to allow board objects to be 
 *used as 2d arrays for their grid
 @return the index at which to place the value within the []
*/
int& Board::Internal::operator[](int index){

	if(index >= WIDTH){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
        	}
        return grid[index];
}

/*
 *This function is used to allow board objects to be 
 *used as 2d arrays for their grid
*/
Board::Internal Board::operator[](int index){

	if(index >= HEIGHT){
                throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
        }
        return Board::Internal(grid+(index * WIDTH));
}

/*
 *This Function is used to print out the contents of the board passed in
 @param os is the output stream
 @param b is the board that we want to print
 */
std::ostream& operator<<(std::ostream& os, Board const& b){
	
	//Create a copy of the board so we can print out the grid
	Board printed = b;
	
	//Loop through the grid printing only non empty spots
	for(int i = 0; i<HEIGHT; i++){
		if(printed.visible == true){
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
		}

		//Hide where the ships are
		//Board is not visible
		else{
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
				        os<<"-\t";
			        }
		        }
		}
		os<<"\n";
	}
	//Return the output stream
	return os;
}

/*
 * This function is used to keep track of who is winning
 * @return the number of hits on the board that calls the function
 */
int Board::count() const{
	
	//Variable to keep track of the count	
	int count = 0;

	//Go through the entire Grid and get the total
	for(int i =0; i<WIDTH*HEIGHT; i++){
		if(this->grid[i] == HIT)
			 count++;
	}
	//Return the count
	return count;
}

/*
 * Overloader so we can compare to boards using the
 * count() function
 *@return true if the board passed in is greater than
 *the this board
 */
bool Board::operator< (const Board& other){
	//this board is winning
	if(this->count() < other.count())
		return true;
	//othere board is winning
	return false;
}
