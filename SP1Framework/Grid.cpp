#include "Grid.h"

Grid::Grid()
	: size(COORD())
{
	this->nodes = new Node*[this->size.Y];
	for (int r = 0; r < this->size.Y; ++r)
		this->nodes[r] = new Node[this->size.X];
}

//--------------------------------------------------------------
// Purpose  : Get X and Y from specified file
//            Initialise the contents and get the data from the file
// Input    : File path 
// Output   : N.A.
//--------------------------------------------------------------
Grid::Grid(std::string attr, std::string file) 
{
	std::ifstream ifs(attr);
	std::map<char, Node> attrs;
	int count;
	ifs >> count;
	for (int i = 0; i < count; ++i)
	{
		char item;
		int icon;
		bool isBlocked;
		int fc, bc;
		ifs >> item >> icon >> isBlocked >> fc >> bc;
		attrs[item] = Node(icon, isBlocked, (Colour)fc, (Colour)bc);
	}

	ifs.close();
	ifs.open(file);
	ifs >> size.X >> size.Y;
	ifs.get(); // ignore buffer
	
	this->nodes = new Node*[this->size.Y];
	for (int r = 0; r < this->size.Y; ++r) 
	{
		this->nodes[r] = new Node[this->size.X];
		for (int c = 0; c < this->size.X; ++c) 
		{
			char item = ' ';
			ifs >> item;
			this->nodes[r][c] = attrs[item];
			switch (item) {
			case 'w':
				//this->nodes[r][c] = Node(' ', true, black, black);
				break;
			case 'D':
				//this->nodes[r][c] = Door(178, 176, grey, white);
				break;
			default:
				//this->nodes[r][c] = Node(' ', false, white, white);
				break;
			}
		}
	}

	ifs.close();
}

Grid::~Grid()
{
	delete[] this->nodes;
}