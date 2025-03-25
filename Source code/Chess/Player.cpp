#include "Player.h"

Player::Player() : isWhite(true)
{}

Player::Player(bool isWhite) : isWhite(isWhite)
{}

Player::~Player()
{}

bool Player::getIsWhite() const
{
	return this->isWhite;
}

void Player::setIsWhite(bool isWhite)
{
	this->isWhite = isWhite;
}
