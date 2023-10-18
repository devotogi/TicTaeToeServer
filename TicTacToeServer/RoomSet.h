#pragma once
class RoomSet
{
private:
	static RoomSet* _instance;
	set<class Room*> _set;
	CRITICAL_SECTION _cs;

public:
	RoomSet()
	{
		InitializeCriticalSection(&_cs);
	}

	~RoomSet()
	{
		DeleteCriticalSection(&_cs);
	}

	void AddRoom(Room* room);
	void EreaseRoom(Room* room);

	static RoomSet* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new RoomSet();

		return _instance;
	}
};

