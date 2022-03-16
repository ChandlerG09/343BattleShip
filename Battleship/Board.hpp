#ifndef			__HPP_BOARD__
#define			__HPP_BOARD__

#include "BoardValues.hpp"
#include <iostream>
#include <vector>

#define HEIGHT 10
#define WIDTH 10

class Board {

	public:
		Board();
		Board(const Board &other);
		Board& operator=(const Board& other);
		int count() const;
		bool operator< (const Board& other);
		~Board();
		void setVisible(bool v);

		class Internal {
			public:
			Internal(int* _g) {
				grid = _g;
			}
			int& operator[](int index);

			private:
				int* grid;
		};
		Internal operator[](int index);

	private:
		int* grid;
		bool visible;
	
	friend std::ostream& operator<<(std::ostream& os, Board const& b);

};


#endif
