#pragma once
class GameSession;

class Lobby
{
private:
	static Lobby* _instance;
	std::map<int32, GameSession*> _sessions;
	CRITICAL_SECTION _cs;
	uint32 _sessionId = 0;

public:
	Lobby()
	{
		InitializeCriticalSection(&_cs);
	}

	~Lobby()
	{
		DeleteCriticalSection(&_cs);
	}

public:
	void AddSession(int32 sessionId, GameSession* session);
	void PopSession(int32 sessionId);
	GameSession* GetSession(int32 sessionId);
	GameSession* GetSessionRandom(GameSession* session);

	static Lobby* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new Lobby();

		return _instance;
	}
};

