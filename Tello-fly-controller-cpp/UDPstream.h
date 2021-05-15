#pragma once
#include <cstring>
#include <string>
#include "platform.h"

#if defined(WIN)
#include <winsock2.h>
#include <Mstcpip.h>
#pragma comment(lib,"ws2_32.lib")
#else

#endif

namespace UDP {

#if defined(WIN)
	typedef SOCKET my_socket;
	#define is_error_socket(sock) ((sock)==SOCKET_ERROR)
#else
	typedef int my_socket;
	#define is_error_socket(sock) ((sock)<=0)
#endif

	class UDPstream	{
	public:

		/// <summary>
		/// UDP stream setup
		/// </summary>
		/// <param name="port">The port to be bound</param>
		UDPstream(int port);
		~UDPstream();

		/// <summary>
		/// send data
		/// </summary>
		/// <param name="data">Data to be sent</param>
		/// <param name="ip">Target ip address</param>
		/// <param name="port">Target port</param>
		/// <returns>If failed , return false</returns>
		bool send_data(const char* data, const char* ip, int port);

		/// <summary>
		/// Get data
		/// </summary>
		/// <param name="data">Data buffer</param>
		/// <param name="buffersize">Size of buffer</param>
		/// <param name="ip">Ip of the sender</param>
		/// <param name="port">Port of the sender</param>
		/// <returns>If failed , return false , you can use WSAGetLastError() to check errors</returns>
		bool get_data(char* data, int buffersize, char* ip, int& port);

	private:
		my_socket sock;
	};

	class UDPgram
	{
	public:

		char* Data;
		char* Ip;
		int Port;

		/// <summary>
		/// UDP gram setup
		/// </summary>
		/// <param name="data">Data to be sent</param>
		/// <param name="ip">Target ip address</param>
		/// <param name="port">Target port</param>
		UDPgram(const char* data, const char* ip, int port);
		/// <summary>
		/// UDP gram setup
		/// </summary>
		/// <param name="data">Data to be sent</param>
		/// <param name="ip">Target ip address</param>
		/// <param name="port">Target port</param>
		UDPgram(std::string data, const char* ip, int port);

		friend UDPstream& operator<<(UDPstream& stream, UDPgram gram) {
			if (!stream.send_data(gram.Data, gram.Ip, gram.Port)) {
				throw "send failed";
			}
			else {
				return stream;
			}
		}

	private:

		sockaddr_in addr;

	};

	class UDPdata
	{
	public:

		/// <summary>
		/// Alloc data
		/// </summary>
		/// <param name="buffersize">Size of buffer</param>
		UDPdata(int buffersize = 1518);
		UDPdata(const UDPdata& b);
		UDPdata(UDPdata&& b);
		~UDPdata();

		const char* get_data();
		const char* get_ip();
		int get_port();

		friend UDPstream& operator>>(UDPstream& stream,UDPdata& b) {
			stream.get_data(b.data, b.buffer_size, (char*)b.ip, b.port);
			return stream;
		}

	private:
		int buffer_size;
		char* data;
		const char* ip;
		int port;
	};

}
