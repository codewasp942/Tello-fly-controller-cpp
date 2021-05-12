#pragma once
#include "platform.h"

#if defined(WIN)
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else

#endif

namespace UDP {

#if defined(WIN)
	typedef SOCKET my_socket;
#else
	typedef int my_socket;
#endif

	class UDPstream	{
	public:

		UDPstream(int);
		~UDPstream();

	private:
		my_socket sock;
	};

}
