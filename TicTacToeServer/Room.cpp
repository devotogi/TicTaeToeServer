#include "pch.h"
#include "Room.h"
#include "GameSession.h"

Room::Room(GameSession* p1, GameSession* p2) : _p1(p1), _p2(p2)
{
	p1->SendOtherPlayerUDPIP(p2);
	p2->SendOtherPlayerUDPIP(p1);
}
