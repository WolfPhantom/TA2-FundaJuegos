#pragma once
#include <string>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "ResourceManager.h"
#include<stdlib.h>
#include<time.h>
const int HUMAN_WIDTH = 60;

class Human 
{
	glm::vec2 position;
	
	Color color;
	std::string textPath;

public:
	Human(std::string textPath);
	~Human();
	void draw(SpriteBacth& spritebatch);
	std::string gettextPath() { return textPath; };
};

