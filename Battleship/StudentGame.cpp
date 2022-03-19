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

	Ship Carrier = Ship(4, "Carrier", CARRIER);
	Ship Battleship = Ship(5, "Battleship", BATTLESHIP);
	Ship Destroyer = Ship(3, "Destroyer", DESTROYER);
	Ship Submarine = Ship(3, "Submarine", SUBMARINE);
	Ship PatrolBoat = Ship(2, "PatrolBoat", PATROLBOAT);

	//Create the Vector	
//	std::vector<Ship> ships;
	
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
	
	//Set up Boards
	
	std::cout<<"\nWelcome To Battleship!\n";

//	player = *(new Board());
//	computer = *(new Board());

	Board p = Board();
	Board c = Board();

	player = p;
	computer = c;

//	player = Board();
//	computer = Board();

	//Player places Ships
	placeShips();

	//PC places Ships
   	placeShipsPC();
	
	std::cout<<player;
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
	for(int i = 0; i< ships.size(); i++){
		placeOk = false;
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

		if(rotation == 0){
			if(place(locx, locy, HORIZONTAL, ships.at(i), player)){
				for(int t = locx; t<locx+ships.at(i).getSpaces(); t++){
					player[t][locy] = ships.at(i).getChr();
				}
			}	
		}
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
	int attempt = 0;
	Direction direction;
	for(int i=0; i< ships.size(); i++){
		
		if(attempt%2 == 1)
			direction = HORIZONTAL;
		else
			direction = VERTICAL;

		//Create way to randomly pick spots and rotations
		while(!place(locx,locy,direction,ships.at(i),computer)){ 
		
		
		locx = attempt%WIDTH;
		locy = attempt*2%HEIGHT;
		attempt++;
		}

		if(direction == HORIZONTAL){
			for(int t = locx; t<locx+ships.at(i).getSpaces(); t++){
				computer[t][locy] = ships.at(i).getChr();
			}
		}
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
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){
	
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
	else{
		return false;
	}

	return true;
}

/**
 * Call human turn/computer turn until someone wins.
 */
void Game::run(){
	while(player.count() != 17 || computer.count() !=17){

		humanTurn();
		computerTurn();
		
		std::cout<<"\nYour Board:\n"<<player;
		std::cout<<"\nPC Board:\n"<<computer;
	}
	
	if(player.count() == 17)
		std::cout<<"You Win!!";
	else
		std::cout<<"You Lost.";
}

void Game::humanTurn(){
	
	int locx;
	int locy;

	std::cout<<"\nPlease Pick a Location to Fire Upon: \n";
	std::cout<<"Pick X location ";
	std::cin>>locx;
	std::cout<<"Pick Y location: ";
	std::cin>>locy;

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

	std::cout<<"\n\nComputer Board:\n\n" << computer << std::endl;
}

void Game::computerTurn(){
	
	int num = clock();

	int xval = num%WIDTH;
	int yval = num*2%HEIGHT;
	
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
