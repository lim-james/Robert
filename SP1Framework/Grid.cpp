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
		State onState, offState;
		onState = offState = State();
		bool isBlocked, seen, toggled, isPickable;
		int onForegroundColour;
		int onBackgroundColour;
		int offForegroundColour;
		int offBackgroundColour;
		
		ifs >> item
			>> onState.icon >> onState.isBlocked >> onForegroundColour >> onBackgroundColour
			>> offState.icon >> offState.isBlocked >> offForegroundColour >> offBackgroundColour
			>> seen >> toggled >> isPickable;

		onState.foregroundColour = (Colour)onForegroundColour;
		onState.backgroundColour = (Colour)onBackgroundColour;
		offState.foregroundColour = (Colour)offForegroundColour;
		offState.backgroundColour = (Colour)offBackgroundColour;

		attrs[item] = Node(onState, offState, seen, toggled, isPickable);

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
		}
	}

	ifs.close();
}

Grid::~Grid()
{
	delete[] this->nodes;
}