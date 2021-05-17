#pragma once
#include "Board.h"
using namespace std;
using namespace sf;
class Game
{
private:

    //////
    //Variables
    //////

    //Window
	RenderWindow* window;

    //User events
	Event ev;

    //Music
    Music bg_music;

    //Fonts
    Font font_nums;

    //Text
    Text tx_nums;

    //Shapes and drawables
    RectangleShape bg_square;
    RectangleShape tile_square;

    //Game variables
    int gameSize;

    //Board
    Board board;

    //////
    //Colors
    /////

    //Basic colors
    Color* c_bgColor = new Color(250, 248, 239);
    Color* c_tileBgColor = new Color(187, 173, 160);
    Color* c_tileColor = new Color(205, 192, 180);
    //2 and 4 numbers
    Color* c_twoAndFourNumbers = new Color(119, 110, 101);
    //All other numbers
    Color* c_numbers = new Color(249, 246, 242);
    //2 Tiles (2^1)
    Color* c_oneTile = new Color(238, 228, 218);
    //4 Tiles (2^2)
    Color* c_twoTile = new Color(237, 224, 200);
    //8 Tiles...
    Color* c_threeTile = new Color(242, 177, 121);
    //16 Tiles
    Color* c_fourTile = new Color(245, 149, 99);
    //32 Tiles
    Color* c_fiveTile = new Color(246, 124, 95);
    //64 Tiles
    Color* c_sixTile = new Color(227, 110, 77);
    //128 Tiles
    Color* c_sevenTile = new Color(234, 204, 121);
    //256 Tiles
    Color* c_eightTile = new Color(233, 197, 91);
    //More than 256 Tiles 
    Color* c_moreTile = new Color(233, 197, 91);

    //////
    //Inits
    //////

    void initWindow();
    void initVariables(int size);
    void initSounds();
    void initDrawables();
    
public:

    //////
    //Constructor
    //////

    Game(int size);
    ~Game();

    //////
    //Getter
    //////

    const bool running() const;

    //////
    //Functions
    //////

    void render();
    void update();
    void updateMusic();
    void updateShapes();
    void resetBoard();
    void pollEvents();
    void run();
};

