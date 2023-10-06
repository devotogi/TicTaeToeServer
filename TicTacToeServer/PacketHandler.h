#pragma once
class GameSession;

class PacketHandler
{
public:
	static void HandlePacket(GameSession* session, BYTE* packet, int32 packetSize);

private:

};

