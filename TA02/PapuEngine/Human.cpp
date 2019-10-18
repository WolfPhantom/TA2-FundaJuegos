#include "Human.h"



Human::Human(std::string textPath)
{
	srand(time(NULL));
	this->textPath = textPath;
	this->position.x= rand() % 1000;
	this->position.y = rand() % 1000;
}




Human::~Human()
{
}

void Human::draw(SpriteBacth& spritebatch)
{
	static int textureID =
		ResourceManager::getTexture(textPath).id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, HUMAN_WIDTH, HUMAN_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}
