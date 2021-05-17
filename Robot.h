#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Robot
{
private:
	//Inits
	void initVariables(int stratNumber);
	void initStrategy();

	

	//Speed things
	Clock lastMove;
	int timeMove;


	//Variables
	vector <int> strategy;
	bool isPlaying;
	int currentIndex;
	int activeStrat=0;
public:
	Robot(int stratNumber=0);


	//Functions
	void run();
	void stop();
	bool playing();
	int returnMove();


};

