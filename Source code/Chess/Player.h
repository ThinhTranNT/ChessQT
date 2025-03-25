#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
private:
	bool isWhite;
public:
	Player();
	Player(bool isWhite);
	~Player();

	bool getIsWhite() const;
	void setIsWhite(bool isWhite);
};



#endif // !PLAYER_H_
