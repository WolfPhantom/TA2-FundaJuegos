#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"


using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Ella se fue :'v", _witdh, _height, 0);
	initLevel();
	initShaders();
}

void MainGame::initLevel(){
	currentLevel = 0;
	levels.push_back(new Level("Levels/level.txt"));
	zombies.push_back(new Zombie("Textures/zonbie.png"));
	player = new Player();
	player->init(1.0f,
		levels[currentLevel]->getPlayerPosition(),
		&_inputManager);
	_spriteBacth.init();
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1,GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	levels[currentLevel]->draw();
	//humans[currentLevel]->draw(_spriteBacth);
	player->draw(_spriteBacth);
	
	for (int i = 0; i < humans.size(); i++)
	{
		humans[i]->draw(_spriteBacth);
	}
	for (int i = 0; i < zombies.size(); i++)
	{
		zombies[i]->draw(_spriteBacth);
	}
	_spriteBacth.end();
	_spriteBacth.renderBatch();
	
	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x,event.motion.y);
			break;
			case  SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}

		if (_inputManager.isKeyPressed(SDLK_p)) {
			humans.push_back(new Human("Textures/red_bricks.png"));
			
		}
		if (_inputManager.isKeyPressed(SDLK_2)) {
			humans.push_back(new Human("Textures/Paper_Mario_.png"));
			
		}
		if (_inputManager.isKeyPressed(SDLK_3)) {
			for (int i = 0; i < humans.size(); i++)
			{
				cout<<humans[i]->gettextPath()<<endl;
			}
			cout << humans.size()<<endl;

		}
		
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		_camera.setPosition(player->getPosition());
		player->update();
	}
}


MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
