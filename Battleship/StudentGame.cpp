#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>
#include <time.h>
/**
 * Constructor will create the ships vector and add ships to it.
 */
Game::Game(){
	//Creating the ships that will be placed on the board
	Ship Carrier = Ship(4, "Carrier", CARRIER);
	Ship Battleship = Ship(5, "Battleship", BATTLESHIP);
	Ship Destroyer = Ship(3, "Destroyer", DESTROYER);
	Ship Submarine = Ship(3, "Submarine", SUBMARINE);
	Ship PatrolBoat = Ship(2, "PatrolBoat", PATROLBOAT);


	
	//Add the Ships to the Vector
	ships.push_back(Carrier);
	ships.push_back(Battleship);
	ships.push_back(Destroyer);
	ships.push_back(Submarine);
	ships.push_back(PatrolBoat);
}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame(){
	
	std::cout<<"\nWelcome To Battleship!\n";
	
	//Set up Boards
	Board p = Board();
	Board c = Board();
	player = p;
	computer = c;
	
	//Players Board is always visible
	player.setVisible(true);
	
	//Computer Board is not visible until game over
	computer.setVisible(false);

	//Player places Ships
	placeShips();

	//PC places Ships
   	placeShipsPC();
	
	//Print out the boards
	std::cout<<"\n\nYour Board\n"<<player;
	std::cout<<"\n\nPC Board:\n" <<computer;
	
	//Run the game
	run();	
}

/**
 * Handle the human placing ships.
 */
void Game::placeShips(){
	
	int locx;
	int locy;
	int rotation;
	bool placeOk = false;

	//Loop through for all ships
	for(int i = 0; i< ships.size(); i++){
		placeOk = false;
		//Until it is a valid spot to place the ship ask for locations
		while(!placeOk){
			std::cout<<"Choose Ship placement for " 
			<< ships.at(i).getName() 
				<< " (" <<ships.at(i).getSpaces() 
				<< " spaces)\n";

			std::cout<<"Choose X Coordinate: ";
			std::cin>>locx;
			std::cout<<"Choose Y Coordinate: ";
			std::cin>>locy;
			std::cout<<"Horizontal or Vertical(0/1): ";
			std::cin>>rotation;
			
			//Player chose Horizontal Rotation, check if valid location			
			if(rotation == 0 && place(locx, locy, HORIZONTAL, ships.at(i), player))
				placeOk = true;
			//Player Chose Vertical Rotation, check if valid location
			else if(rotation == 1 && place(locx, locy, VERTICAL, ships.at(i), player))
				placeOk = true;
			//Unable to place ship in entered spot
			else
				std::cout<<"\nUnable to place Ship in that location...Please try again.\n";
		}
		//Horizontal Ship Placement
		if(rotation == 0){
			if(place(locx, locy, HORIZONTAL, ships.at(i), player)){
				for(int t = locx; t<locx+ships.at(i).getSpaces(); t++){
					player[t][locy] = ships.at(i).getChr();
				}
			}	
		}
		//Vertical Ship Placement
		else{
			if(place(locx, locy, VERTICAL, ships.at(i), player)){
				for(int t=locy; t<locy+ships.at(i).getSpaces();t++){
					player[locx][t]=ships.at(i).getChr();
				}
			}
		}
	}		
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC(){

	int locx;
	int locy;
	int num = clock();
	locx = num%(WIDTH-1);
	locy = num*2%(HEIGHT-1);
	Direction direction;
	for(int i=0; i< ships.size(); i++){

		//Odd Numbers are Horizontally placed
		if(num%2 == 1)
			direction = HORIZONTAL;
		else
			direction = VERTICAL;

		//Attempt to Place ship until sucessful
		while(!place(locx,locy,direction,ships.at(i),computer)){ 
		
		//Change the positions
		num = clock();
		locx = num%WIDTH;
		locy = num*2%HEIGHT;
		}

		//Place ship horizontally
		if(direction == HORIZONTAL){
			for(int t = locx; t<locx+ships.at(i).getSpaces(); t++){
				computer[t][locy] = ships.at(i).getChr();
			}
		}
		//Place the ship vertically
		else{
			for(int t = locy; t<locy+ships[i].getSpaces(); t++){
				computer[locx][t] = ships.at(i).getChr();
			}
		}
	}
}

/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 * @param x is the x coordinate to place the ship
 * @param y is the y coordinate to place the ship 
 * @param d is the direction (Horizontal or Vertical) in which to place the ship
 * @param s is the ship that we are trying to place
 * @param b is the board that we are trying to place the ship on
 * @return True if you can place the ship at (x,y) and false if you cannot
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){
	
	//Check that there is enough room on the board to even place the ship at (x,y)
	if(d == HORIZONTAL){
		if(x > WIDTH-s.getSpaces())
			return false;
	}
	else{
		if(y > HEIGHT-s.getSpaces())
			return false;
	}
	
	//Check that the spot attemtping to place in is empty
	if(b[x][y] == EMPTY){

		//Handle Horiztonally Placed Ships
		if(d == HORIZONTAL){
			for(int i = x; i<x+s.getSpaces(); i++){
				if(b[i][y] != EMPTY)
					return false;
			}
		}
		//Handle Vertically Placed Ships
		else{
			for(int i = y; i<y+s.getSpaces(); i++){
				if(b[x][i] != EMPTY)
					return false;
			}
		}
	}
	//There is a piece in this position already
	else{
		return false;
	}
	//All is good
	return true;
}

/**
 * Call human turn/computer turn until someone wins.
 */
void Game::run(){
	//Run until count of either board is equal to the amount needed to win
	while(player.count() != 17 || computer.count() !=17){

		humanTurn();
		computerTurn();
		
		std::cout<<"\nYour Board:\n"<<player;
		std::cout<<"\nPC Board:\n"<<computer;
	}

	//Show the Computers ship location
	computer.setVisible(true);

	//Print the boards
	std::cout<<"\nYour Board\n"<<player;
	std::cout<<"\n\nComputer Board\n"<<computer;

	//Let the user know who won	
	if(player.count() == 17)
		std::cout<<"You Win!!";
	else
		std::cout<<"You Lost.";
}

void Game::humanTurn(){
	
	int locx;
	int locy;
	bool valid = false;
	//Ask player for a location to fire at until valid location given
	while(!valid){
		std::cout<<"\nPlease Pick a Location to Fire Upon: \n";
		std::cout<<"Pick X location ";
		std::cin>>locx;
		std::cout<<"Pick Y location: ";
		std::cin>>locy;

		if(locx < WIDTH && locy < HEIGHT)
			valid = true;
	}

	//Check what is located at the spot and update the board accordingly
	if(computer[locx][locy] != EMPTY){
		if(computer[locx][locy]==ships.at(0).getChr()){
			ships.at(0).addHit();
			computer[locx][locy] = HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(computer[locx][locy]==ships.at(1).getChr()){
		        ships.at(1).addHit();
			computer[locx][locy]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(computer[locx][locy]==ships.at(2).getChr()){
		        ships.at(2).addHit();
			computer[locx][locy]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(computer[locx][locy]==ships.at(3).getChr()){
		        ships.at(3).addHit();
			computer[locx][locy]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(computer[locx][locy]==ships.at(4).getChr()){
		        ships.at(4).addHit();
			computer[locx][locy]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
	}
	else{
		std::cout<<"\nYou missed!\n";
		computer[locx][locy] = MISS;
	}
}

void Game::computerTurn(){
	
	int num = clock();

	int xval = num%WIDTH;
	int yval = num*2%HEIGHT;
	//Randomly selects a spot to fire on and checks whats there and updates board
	if(player[xval][yval] != EMPTY && player[xval][yval] != HIT && player[xval][yval] != MISS){
		
		if(player[xval][yval]==ships.at(0).getChr()){
			ships.at(0).addHit();
			player[xval][yval]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(player[xval][yval]==ships.at(1).getChr()){
			ships.at(1).addHit();
			player[xval][yval]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(player[xval][yval]==ships.at(2).getChr()){
			ships.at(2).addHit();
			player[xval][yval]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(player[xval][yval]==ships.at(3).getChr()){
			ships.at(3).addHit();
			player[xval][yval]=HIT;
			std::cout<<"\nIt's a hit!\n";
		}
		if(player[xval][yval]==ships.at(4).getChr()){
			ships.at(4).addHit();
			player[xval][yval] = HIT;
			std::cout<<"\nIt's a hit!\n";
		}
	}
	else{
		player[xval][yval]=MISS;
		std::cout<<"\nIt's a miss\n";
	}
}

/**
 * Create a game instance and start.
 */
int main(int argc, char** argv){
	
	(void)argc;
	(void)argv;

	Game g;
	g.beginGame();
	return 0;
}
