#include "pch.h"
#include "GameSession.h"
#include "SessionManager.h"
#include "BufferWriter.h"
#include "PacketHandler.h"
#include "Lobby.h"
void GameSession::SetLocalIp(char* localIp, int localIpSize)
{
	_localIpSize = localIpSize;
	::memcpy(_localIp, localIp, _localIpSize);
}

void GameSession::SetPublicIp(char* publicIp, int publicIpSize)
{
	_publicIpSize = publicIpSize;
	::memcpy(_publicIp, publicIp, publicIpSize);
}

GameSession::GameSession(const SOCKET& socket, const SOCKADDR_IN& sock) : Session(socket, sock)
{
}

GameSession::~GameSession()
{

}

void GameSession::OnRecv(Session* session, BYTE* dataPtr, int32 dataLen)
{
	PacketHandler::HandlePacket(static_cast<GameSession*>(session), dataPtr, dataLen);
}

void GameSession::OnDisconnect()
{
	Lobby::GetInstance()->PopSession(_sessionId);
	SessionManager::GetInstance()->PopSession(_sessionId);
}

void GameSession::OnConnect()
{
	SessionManager::GetInstance()->GetSessionId(_sessionId);
	SessionManager::GetInstance()->AddSession(_sessionId, this);
}
