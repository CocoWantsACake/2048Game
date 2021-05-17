#include "Board.h"

//Out of class but useful function
void switchInt(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

const int Board::getSize() const
{
	return this->gameSize;
}

const vector<vector<int>> Board::getState() const
{
    return state;
}

const bool Board::isGameLost() const
{
    bool onePlayable = false;
    for (int i = 0; i < this->state.size(); i++)
    {
        for (int j = 0; j < this->state[i].size(); j++)
        {
            if (this->state[i][j] == 0)
            {
                return false;
            }
        }
    }
    for (int i = 0; i < this->state.size(); i++)
    {
        for (int j = 0; j < this->state[i].size(); j++)
        {
            if (j < gameSize-1) {
                if (this->state[i][j] == this->state[i][j + 1]) {
                    return false;
                }
            }
            if (i < gameSize-1) {
                if (this->state[j][i] == this->state[j][i + 1]) {
                    return false;
                }
            }
            
        }
    }
}

Board::Board(int size)
{
	this->initVariables(size);
    this->addPoints();
}

Board::~Board()
{
}

void Board::robotMove()
{
    switch (rob.returnMove()) {
    case 1:
        this->moveUp();
        this->addPoints();
        break;
    case -1:
        this->moveDown();
        this->addPoints();
        break;
    case 2:
        this->moveRight();
        this->addPoints();
        break;
    case -2:
        this->moveLeft();
        this->addPoints();
        break;
    }
}

void Board::moveLeft()
{
    vector <int> temp;
    for (int i = 0; i < this->gameSize; i++)
    {
        temp.clear();
        for (int j = 0; j < this->gameSize; j++)
        {
            if (this->state[i][j] != 0)
            {
                temp.push_back(state[i][j]);
            }
        }
        this->state[i] = fusion(temp);
    }
}

void Board::moveRight()
{
    vector <int> temp;
    vector <int> temp2;
    for (int i = 0; i < this->gameSize; i++)
    {
        temp.clear();
        for (int j = this->gameSize - 1; j >= 0; j--)
        {
            if (this->state[i][j] != 0)
            {
                temp.push_back(this->state[i][j]);
            }
        }
        temp = fusion(temp);
        for (int i = temp.size() - 1; i >= 0; i--)
        {
            temp2.push_back(temp[i]);
        }
        this->state[i] = temp2;
        temp2.clear();
    }
}

void Board::moveUp()
{
    vector <int> temp;
    for (int i = 0; i < this->gameSize; i++)
    {
        temp.clear();
        for (int j = 0; j < this->gameSize; j++)
        {
            if (this->state[j][i] != 0)
            {
                temp.push_back(this->state[j][i]);
            }
        }
        temp = fusion(temp);
        for (int j = 0; j < this->gameSize; j++)
        {
            this->state[j][i] = temp[j];
        }
    }
}

void Board::moveDown()
{
    vector <int> temp;
    vector <int> temp2;
    for (int i = 0; i < this->gameSize; i++)
    {
        temp.clear();
        for (int j = this->gameSize - 1; j >= 0; j--)
        {
            if (this->state[j][i] != 0)
            {
                temp.push_back(this->state[j][i]);
            }
        }
        temp = fusion(temp);
        for (int y = temp.size() - 1; y >= 0; y--)
        {
            temp2.push_back(temp[y]);
        }
        for (int j = 0; j < this->gameSize; j++)
        {
            this->state[j][i] = temp2[j];
        }
        temp2.clear();

    }
}

void Board::initVariables(int size)
{
    this->gameSize = size;
    this->rob = Robot(2);
    vector <int> temp;
    if (size < 4)
        throw invalid_argument("Error: Size can't be under 4");
    this->gameSize = size;
    for (int i = 0; i < size; i++)
    {
        temp.push_back(0);
    }
    for (int j = 0; j < size; j++)
    {
        this->state.push_back(temp);
    }
}

void Board::displayGame() const
{
    for (int i = 0; i < this->gameSize; i++)
    {
        for (int j = 0; j < this->gameSize; j++)
        {
            cout << this->state[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::robotSwitch()
{
    if (rob.playing()) {
        rob.stop();
    }
    else {
        rob.run();
    }
}

vector<int> Board::fusion(const vector<int>& vec)
{
    int cpt = 0;
    vector <int> temp;
    vector <int> temp2;
    for (int i = 0; i < this->gameSize; i++)
    {
        temp.push_back(0);
    }
    if (vec.size() == 1)
    {
        temp[0] = vec[0];
        return temp;
    }
    else if (vec.size() == 0)
        return temp;
    else
    {
        temp = vec;
        while (cpt < vec.size() - 1)
        {
            if (temp[cpt] == temp[cpt + 1])
            {
                temp[cpt] *= 2;
                temp[cpt + 1] = 0;
                cpt += 2;
            }
            else
            {
                cpt++;
            }
        }
        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i] != 0)
            {
                temp2.push_back(temp[i]);
            }
        }
        while (temp2.size() < this->gameSize)
            temp2.push_back(0);

        return temp2;
    }
}

void Board::addPoints()
{
    vector <Vector2i> coordinates;
    for (int i = 0; i < this->gameSize; i++)
    {
        for (int y = 0; y < this->gameSize; y++)
        {
            if (this->state[i][y] == 0)
            {
                coordinates.push_back(Vector2i(i, y));
            }
        }
    }
    if (coordinates.size() == 0) {
        return;
    }
    int ind = rand() % coordinates.size();
    int twoOrFour = rand() % 2;
    if (twoOrFour == 1)
    {
        this->state[coordinates[ind].x][coordinates[ind].y] = 2;
    }
    else
    {
        this->state[coordinates[ind].x][coordinates[ind].y] = 4;
    }
}
