#pragma once
class GameSession;

class PacketHandler
{
public:
	static void HandlePacket(GameSession* session, BYTE* packet, int32 packetSize);

private:
	static void HandlePacket_C2S_CLIENTINIT(GameSession* session, BYTE* packet, int32 packetSize);
	static void HandlePacket_C2S_CLIENTREADY(GameSession* session, BYTE* packet, int32 packetSize);
};

