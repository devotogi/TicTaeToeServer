#include "pch.h"
#include "Room.h"
#include "GameSession.h"

Room::Room(GameSession* p1, GameSession* p2) : _p1(p1), _p2(p2)
{
	p1->SendGameInfo(p2,1);
	p2->SendGameInfo(p1,2);
}
