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
	__int16 _type = 0;
	__int16 _pktSize = 0;
};