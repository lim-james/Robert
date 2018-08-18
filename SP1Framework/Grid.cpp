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
		bool hasTwoStates;
		State onState, offState;
		onState = offState = State();
		bool isBlocked, seen, toggled, isPickable;
		int onIcon, onForegroundColour, onBackgroundColour;
		int offIcon, offForegroundColour, offBackgroundColour;
		
		ifs >> item >> hasTwoStates
			>> onIcon >> onState.isBlocked >> onForegroundColour >> onBackgroundColour;
		onState.icon = (char)onIcon;
		onState.foregroundColour = (Colour)onForegroundColour;
		onState.backgroundColour = (Colour)onBackgroundColour;
		if (hasTwoStates)
		{
			ifs >> offIcon >> offState.isBlocked >> offForegroundColour >> offBackgroundColour;
			offState.icon = (char)offIcon;
			offState.foregroundColour = (Colour)offForegroundColour;
			offState.backgroundColour = (Colour)offBackgroundColour;
		}
		else
		{
			offState = onState;
		}
			
		ifs >> seen >> toggled >> isPickable;

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