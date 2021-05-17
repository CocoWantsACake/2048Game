#include "Robot.h"


void Robot::initVariables(int stratNumber){
    this->activeStrat = stratNumber;
    this->isPlaying = false;
    this->currentIndex = 0;
    this->timeMove = 10;
}

void Robot::initStrategy() {
    switch (this->activeStrat) {
    case 1:
        this->strategy = { 1, 1, 2, -2, 1, 2, -2, 1 };
        break;
    case 2:
        this->strategy = { 2, 1, -2, -1};
        break;
    case 3:
        this->strategy = { 1, -1 };
        break;
    case 4:
        this->strategy.clear();
        for (int i = 0; i < static_cast<int>(rand() % 10); i++) {
            switch (static_cast<int>(rand() % 4)) {
            case 0: 
                this->strategy.push_back(-1); 
                break;
            case 1: 
                this->strategy.push_back(1); 
                break;
            case 2: 
                this->strategy.push_back(2); 
                break;
            case 3: 
                this->strategy.push_back(-2); 
                break;
            }
        }
    }
}

Robot::Robot(int stratNumber) {
    this->initVariables(stratNumber);
    this->initStrategy();
}

void Robot::run() {
    this->isPlaying = true;
}

void Robot::stop() {
    this->isPlaying = false;
}

bool Robot::playing() {
    return this->isPlaying;
}

int Robot::returnMove()
{
    if (this->isPlaying && this->lastMove.getElapsedTime().asMilliseconds() >= this->timeMove) {
        lastMove.restart();
        if (this->currentIndex < this->strategy.size()-1) {
            this->currentIndex++;
        }
        else {
            currentIndex = 0;
        }
        return (this->strategy[this->currentIndex]);
    }
    return 0;
}
