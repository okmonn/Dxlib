#pragma once
#include <string>

namespace std
{
#ifdef _UNICODE
	typedef std::wstring tstring;
#else
	typedef std::string tstring;
#endif
}

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef __int64 int64;
typedef unsigned __int64 uint64;
typedef unsigned long ulong;

struct ID3D12Device;
struct IDXGIFactory4;
