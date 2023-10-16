#pragma once
#include "Session.h"
#include "Room.h"

class GameSession : public Session
{
private:
	int  _localIpSize = 0;
	char _localIp[256] = { 0 };
	int  _publicIpSize = 0;
	char _publicIp[256] = { 0 };
	int _udpPort = 0;
	Room* _room; 
public:
	static Session* MakeGameSession(const SOCKET& socket, const SOCKADDR_IN& sockAddr) { return new GameSession(socket, sockAddr); }

public:
	void SetLocalIp(char* localIp, int localIpSize);
	void SetPublicIp(char* publicIp, int publicIpSize);
	void SetUDPPort(int udpPort) { _udpPort = udpPort; };
	void SetRoom(Room* room) { _room = room; }
	Room* GetRoom() { return _room; }

public:
	GameSession(const SOCKET& socket, const SOCKADDR_IN& sock);
	virtual ~GameSession();

	virtual void OnRecv(Session* session, BYTE* dataPtr, int32 dataLen);
	virtual void OnDisconnect();
	virtual void OnConnect();
};

