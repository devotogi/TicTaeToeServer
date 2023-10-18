#pragma once
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using wchar = wchar_t;

enum PacketProtocol : __int16
{

};

struct Pos
{
public:
	int x;
	int z;

	bool operator==(const Pos& other)
	{
		return x == other.x && z == other.z;
	}

	bool operator!=(const Pos& other)
	{
		return !(*this == other);
	}

	bool operator<(const Pos& other) const
	{
		if (z != other.z)
			return z < other.z;
		return x < other.x;
	}

	bool operator>(const Pos& other) const
	{
		if (z != other.z)
			return z > other.z;
		return x > other.x;
	}

};

struct PacketHeader
{
	__int16 _pktSize = 0;
	__int16 _type = 0;
};

enum PacketType : __int16
{
	S2C_CLIENTINIT,
	C2S_CLIENTINIT,
	C2S_CLIENTREADY,
	S2C_UDPINFO,
	UDP_PING_SEND,
	UDP_PING_RECV,
	UDP_PING_COMPLETE,
	UDP_PING_GAMESTART,
	UDP_PING_SETSTONE,
	UDP_PING_RESULT,
	UDP_PING_TIMEOUT,
	UDP_TIME_FLOW,
	C2S_GAME_END,
	S2C_EXIT_ROOM,
};
