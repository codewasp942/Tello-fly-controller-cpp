#pragma once
#include "platform.h"

#if defined(WIN)
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else

#endif

namespace UDP {

	class UDPstream	{
	public:

		UDPstream(int);
		~UDPstream();

	private:
#if defined(WIN)
		SOCKET sock;
#else
		int sock;
#endif
	};

}
