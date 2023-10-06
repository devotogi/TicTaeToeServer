#include "pch.h"
#include "GameSession.h"
#include "SessionManager.h"
#include "BufferWriter.h"
#include "PacketHandler.h"

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
	SessionManager::GetInstance()->PopSession(_sessionId);
}

void GameSession::OnConnect()
{
	SessionManager::GetInstance()->GetSessionId(_sessionId);
	SessionManager::GetInstance()->AddSession(_sessionId, this);
}
