#include "pch.h"
#include "PacketHandler.h"
#include "GameSession.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "SessionManager.h"
#include "Lobby.h"
#include "Room.h"
void PacketHandler::HandlePacket(GameSession* session, BYTE* packet, int32 packetSize)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(packet);
	BYTE* dataPtr = packet + sizeof(PacketHeader);
	int32 dataSize = packetSize - sizeof(PacketHeader);

	switch (header->_type)
	{
	case C2S_CLIENTINIT:
		HandlePacket_C2S_CLIENTINIT(session, dataPtr, packetSize);
		break;
	case C2S_CLIENTREADY:
		HandlePacket_C2S_CLIENTREADY(session, dataPtr, packetSize);
		break;

	}
}

void PacketHandler::HandlePacket_C2S_CLIENTINIT(GameSession* session, BYTE* packet, int32 packetSize)
{
	int32 port;
	int32 localIpSize;
	int32 publicIpSize;
	char localIp[256] = {0};
	char publicIp[256] = {0};

	BufferReader br(packet);
	
	br.Read(port);
	br.Read(localIpSize);
	br.ReadWString(localIp, localIpSize);
	br.Read(publicIpSize);
	br.ReadWString(publicIp, publicIpSize);

	session->SetUDPPort(port);
	session->SetLocalIp(localIp, localIpSize);
	session->SetPublicIp(publicIp, publicIpSize);

	BYTE sendBuffer[256] = {0};
	BufferWriter bw(sendBuffer);
	PacketHeader* pkt = bw.WriteReserve<PacketHeader>();
	pkt->_pktSize = bw.GetWriterSize();
	pkt->_type = S2C_CLIENTINIT;

	session->Send(sendBuffer, bw.GetWriterSize());
}

void PacketHandler::HandlePacket_C2S_CLIENTREADY(GameSession* session, BYTE* packet, int32 packetSize)
{
	if (session->GetRoom() != nullptr) return;

	GameSession* find = Lobby::GetInstance()->GetSession(session->GetSessionID());

	if (find == nullptr)
		Lobby::GetInstance()->AddSession(session->GetSessionID(), session);
	
	GameSession* second = Lobby::GetInstance()->GetSessionRandom(session);

	if (second == nullptr) return;

	Room* room = new Room(session, second);
	session->SetRoom(room);
	second->SetRoom(room);

}
