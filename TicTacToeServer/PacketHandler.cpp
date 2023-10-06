#include "pch.h"
#include "PacketHandler.h"
#include "GameSession.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "SessionManager.h"

void PacketHandler::HandlePacket(GameSession* session, BYTE* packet, int32 packetSize)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(packet);
	BYTE* dataPtr = packet + sizeof(PacketHeader);
	int32 dataSize = packetSize - sizeof(PacketHeader);

	switch (header->_type)
	{

	}
}