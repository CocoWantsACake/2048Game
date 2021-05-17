#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Robot.h"
using namespace std;
using namespace sf;
class Board
{
private:
	//Variables
	int gameSize;
	vector<vector<int>> state;
	Robot rob;

public:

	//Getter
	const int getSize() const;
	const vector<vector<int>> getState() const;
	const bool isGameLost() const;

	//Constructor
	Board(int size = 4);
	~Board();

	//Functions
	void robotMove();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void initVariables(int size);
	void displayGame() const;
	void robotSwitch();
	vector <int> fusion(const vector <int>& vec);
	void addPoints();

};

