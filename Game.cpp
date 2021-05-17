#include "Game.h"

void Game::initWindow()
{
	ifstream ifs("r_config/window.ini");
	string title_name = "None";
	VideoMode window_res(1280, 720);
	unsigned int framerate_limit = 144;
	bool vsyncEnabled = false;
	if (ifs.is_open()) {
		getline(ifs, title_name);
		ifs >> window_res.width >> window_res.height;
		ifs >> framerate_limit;
		ifs >> vsyncEnabled;
	}
	ifs.close();
	this->window = new RenderWindow(window_res, title_name);// , Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vsyncEnabled);
	//this->window->setKeyRepeatEnabled(false);
}

void Game::initVariables(int size)
{
	this->gameSize = size;
	this->board = Board(size);
	this->window = nullptr;
}

void Game::initSounds()
{
	this->bg_music.openFromFile("r_sounds/bg_music.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(60);
}

void Game::initDrawables()
{
	this->bg_square = RectangleShape(Vector2f(0.85 * this->window->getSize().y, 0.85 * this->window->getSize().y));
	this->bg_square.setFillColor(*c_tileBgColor);
	float tileSizeSide = this->bg_square.getSize().x / this->gameSize * 0.84;
	this->tile_square = RectangleShape(Vector2f(tileSizeSide, tileSizeSide));
	this->tile_square.setFillColor(*c_tileColor);
	this->font_nums.loadFromFile("r_fonts/ClearSans-Bold.ttf");
	this->tx_nums = Text("2", this->font_nums);
	this->tx_nums.setCharacterSize(30);
	this->tx_nums.setLetterSpacing(1);
}

Game::Game(int size)
{
	this->initVariables(size);
	this->initSounds();
	this->initWindow();
	this->initDrawables();
}

Game::~Game()
{
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::render()
{
	//

	this->window->display();
	this->window->clear(*c_bgColor);
}

void Game::update()
{
	this->pollEvents();
	this->updateShapes();
	this->board.robotMove();
	//this->updateMusic();
}

void Game::updateMusic()
{
	if (this->bg_music.getStatus() != Music::Status::Playing) {
		this->bg_music.play();
	}
}

void Game::updateShapes()
{
	this->bg_square.setPosition((this->window->getSize().x / 2.f) - (this->bg_square.getSize().x/2), (this->window->getSize().y / 2.f)- (this->bg_square.getSize().y / 2));
	this->window->draw(this->bg_square);
	for (float i =0; i < this->gameSize; i++){
		for (float y = 0; y < this->gameSize; y++) {
			switch (this->board.getState()[y][i]) {
			case 0:
				this->tile_square.setFillColor(*c_tileColor);
				this->tx_nums.setString("");
				break;
			case 2:
				this->tile_square.setFillColor(*c_oneTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 4:
				this->tile_square.setFillColor(*c_twoTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 8:
				this->tile_square.setFillColor(*c_threeTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 16:
				this->tile_square.setFillColor(*c_fourTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 32:
				this->tile_square.setFillColor(*c_fiveTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 64:
				this->tile_square.setFillColor(*c_sixTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 128:
				this->tile_square.setFillColor(*c_sevenTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 256:
				this->tile_square.setFillColor(*c_eightTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 512:
				this->tile_square.setFillColor(*c_moreTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 1024:
				this->tile_square.setFillColor(*c_moreTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			case 2048:
				this->tile_square.setFillColor(*c_moreTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			default:
				this->tile_square.setFillColor(*c_moreTile);
				this->tx_nums.setString(to_string(this->board.getState()[y][i]));
				break;
			}
			switch (static_cast<string>(tx_nums.getString()).length()) {
			case 1:
				this->tx_nums.setCharacterSize(static_cast<int>(this->tile_square.getSize().x / 2.));
				break;
			case 2:
				this->tx_nums.setCharacterSize(static_cast<int>(this->tile_square.getSize().x / 2.20));
				break;
			case 3:
				this->tx_nums.setCharacterSize(static_cast<int>(this->tile_square.getSize().x / 2.40));
				break;
			case 4:
				this->tx_nums.setCharacterSize(static_cast<int>(this->tile_square.getSize().x / 2.75));
				break;
			case 5:
				this->tx_nums.setCharacterSize(static_cast<int>(this->tile_square.getSize().x / 3));
				break;                                        
			case 6:
				this->tx_nums.setCharacterSize(static_cast<int>(this->tile_square.getSize().x / 3.40));
				break;
			default:
				this->tx_nums.setCharacterSize(static_cast<int>(this->tile_square.getSize().x / 4.0));
				break;
			}
			float bordSize = this->bg_square.getSize().x / (this->gameSize + 1) *0.16;
			this->tx_nums.setOrigin(this->tx_nums.getLocalBounds().left + this->tx_nums.getLocalBounds().width/2.f, this->tx_nums.getLocalBounds().top + this->tx_nums.getLocalBounds().height / 2.f);
			float xTileCor = this->bg_square.getPosition().x + this->tile_square.getSize().x * i + bordSize * (i+1);
			float yTileCor = this->bg_square.getPosition().y + this->tile_square.getSize().y * y + bordSize * (y+1);
			this->tile_square.setPosition( xTileCor, yTileCor);
			this->tx_nums.setPosition((xTileCor + this->tile_square.getSize().x/2), yTileCor + this->tile_square.getSize().y / 2);
			this->window->draw(this->tile_square);
			this->window->draw(this->tx_nums);
		}
	}

}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				this->window->close();
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				this->resetBoard();
			}
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Z)) {
				this->board.moveUp();
				this->board.addPoints();
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
				this->board.moveDown();
				this->board.addPoints();
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Q)) {
				this->board.moveLeft();
				this->board.addPoints();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
				this->board.moveRight();
				this->board.addPoints();
			}
			if (Keyboard::isKeyPressed(Keyboard::F)) {
				this->board.robotSwitch();
			}
		}
	}
}

void Game::resetBoard()
{
	this->board = Board(gameSize);
}

void Game::run()
{
	while (this->running()) {
		this->update();
		this->render();
	}
}
