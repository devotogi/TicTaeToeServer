#pragma once
class GameSession;

class Room
{
private:
	GameSession* _p1;
	GameSession* _p2;
public:
	Room(GameSession* p1, GameSession* p2);
	~Room();
};

