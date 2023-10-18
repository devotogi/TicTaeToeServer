#include "pch.h"
#include "Lobby.h"
#include "GameSession.h"

Lobby* Lobby::_instance = nullptr;

void Lobby::AddSession(int32 sessionId, GameSession* session)
{
	EnterCriticalSection(&_cs);

	_sessions.insert({ sessionId,session });

	LeaveCriticalSection(&_cs);
}

void Lobby::PopSession(int32 sessionId)
{
	EnterCriticalSection(&_cs);

	_sessions.erase(sessionId);

	LeaveCriticalSection(&_cs);
}

GameSession* Lobby::GetSession(int32 sessionId)
{
	GameSession* ret = nullptr;

	EnterCriticalSection(&_cs);
	auto it = _sessions.find(sessionId);

	if (it != _sessions.end())
		ret = it->second;

	LeaveCriticalSection(&_cs);

	return ret;
}

GameSession* Lobby::GetSessionRandom(GameSession* session)
{
	GameSession* ret = nullptr;
	EnterCriticalSection(&_cs);

	for (auto s : _sessions)
	{
		int32 __sessionId = s.first;
		GameSession* __session = s.second;

		if (session->GetSessionID() == __sessionId) continue;

		ret = __session;
		break;
	}

	if (ret != nullptr) 
	{
		Lobby::GetInstance()->PopSession(ret->GetSessionID());
		Lobby::GetInstance()->PopSession(session->GetSessionID());
	}

	LeaveCriticalSection(&_cs);
	return ret;
}
