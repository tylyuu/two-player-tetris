#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <memory>
using namespace std;

#include "../board/cell.h"

class Cell;

class Block {
	protected:
		char type; 
		vector<std::shared_ptr<Cell>> coordinates;
		int bottomLeft;
		int bottomRight;

	public:
		vector<std::shared_ptr<Cell>> rotate(const string& direction);
		vector<std::shared_ptr<Cell>> move(const string& direction);
		vector<std::shared_ptr<Cell>> getCoordinates() const;
		void updateCoordinates(vector<std::shared_ptr<Cell>> cells);
		std::shared_ptr<Cell> getBottomLeft() const;
		std::shared_ptr<Cell> getBottomRight() const;
		virtual pair<int,int> getTopLeft() const = 0;
		virtual ~Block() = default;
}; 

#endif
