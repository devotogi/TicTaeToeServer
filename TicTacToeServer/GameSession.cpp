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

void GameSession::SendGameInfo(GameSession* session, int playerNumber)
{
	BYTE sendBuffer[1000] = {};
	BufferWriter bw(sendBuffer);
	
	char* localIp = session->GetLocalIp();
	int localIpSize = session->GetLocalIpSize();
	char* publicIp = session->GetPublicIp();
	int publicIpSize = session->GetPublicIpSize();
	int port = session->GetPort();

	PacketHeader* header = bw.WriteReserve<PacketHeader>();
	bw.Write(localIpSize);
	bw.WriteWString(localIp,localIpSize);
	bw.Write(publicIpSize);
	bw.WriteWString(publicIp, publicIpSize);
	bw.Write(port);
	bw.Write(playerNumber);

	header->_pktSize = bw.GetWriterSize();
	header->_type = S2C_UDPINFO;

	session->Send(sendBuffer, header->_pktSize);
}

void GameSession::ExitRoom()
{
	BYTE sendBuffer[1000] = {};
	BufferWriter bw(sendBuffer);

	PacketHeader* header = bw.WriteReserve<PacketHeader>();

	header->_pktSize = bw.GetWriterSize();
	header->_type = S2C_EXIT_ROOM;

	Send(sendBuffer, header->_pktSize);
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
