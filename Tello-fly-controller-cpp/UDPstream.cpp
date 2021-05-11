#include "UDPstream.h"

using namespace UDP;

UDPstream::UDPstream(int port) {
#if defined(WIN)
	WSADATA WSAres;
	if (WSAStartup(MAKEWORD(2, 2), &WSAres) != 0) {
		throw "WSAstartup failed on windows";
	}
#else
#endif
}