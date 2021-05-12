#include "UDPstream.h"
#include <windows.h>

using namespace UDP;

UDPstream::UDPstream(int port) {
#if defined(WIN)
	WSADATA WSAres;
	if (WSAStartup(MAKEWORD(2, 2), &WSAres) != 0) {
		throw "WSAstartup failed on windows";
	}
	if ((LOBYTE(WSAres.wVersion) != 2) || (HIBYTE(WSAres.wVersion) != 2)) {
		throw "WSA version is not valid";
	}
#else
#endif
}

UDPstream::~UDPstream() {
#if defined(WIN)
	WSACleanup();
#else
#endif
}