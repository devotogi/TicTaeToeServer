#include "pch.h"
#include "RoomSet.h"
#include "Room.h"
 
RoomSet* RoomSet::_instance = nullptr;

void RoomSet::AddRoom(Room* room)
{
	EnterCriticalSection(&_cs);
	_set.insert(room);
	LeaveCriticalSection(&_cs);
}

void RoomSet::EreaseRoom(Room* room)
{
	if (room == nullptr) return;

	EnterCriticalSection(&_cs);
	
	if (_set.count(room) == 0)
	{
		LeaveCriticalSection(&_cs);
		return;
	}

	if (room != nullptr)
	{
		_set.erase(room);
		delete room;
	}
	LeaveCriticalSection(&_cs);
}
