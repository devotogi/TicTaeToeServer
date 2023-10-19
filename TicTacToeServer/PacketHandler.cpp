#include "pch.h"
#include "PacketHandler.h"
#include "GameSession.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "SessionManager.h"
#include "Lobby.h"
#include "Room.h"
#include "RoomSet.h"
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
	case C2S_GAME_END:
		HandlePacket_C2S_GAME_END(session, dataPtr, packetSize);
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
	cout << "Client Room Request " << endl;
	
	if (session->GetRoom() != nullptr) return;

	Lobby::GetInstance()->MatchSession(session);
}

void PacketHandler::HandlePacket_C2S_GAME_END(GameSession* session, BYTE* packet, int32 packetSize)
{
	Room* room = session->GetRoom();

	if (room == nullptr)
		return;

	RoomSet::GetInstance()->EreaseRoom(room);
}
