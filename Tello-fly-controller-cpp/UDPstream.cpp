#include "UDPstream.h"
#include <iostream>

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
#endif

	//rec_enabled = false;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (is_error_socket(sock)) {
		throw "socket create failed";
	}

	sockaddr_in local_addr;
	memset(&local_addr, 0, sizeof(local_addr));	

	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (is_error_socket(bind(sock, (sockaddr*)(&local_addr), sizeof(local_addr)))) {
		throw "socket bind failed";
	}/*

	bool new_behavior = false;
	DWORD bites_return = 0;
	WSAIoctl(sock, _WSAIOW(IOC_VENDOR, 12), &new_behavior, sizeof(new_behavior), NULL, 0, &bites_return, NULL, NULL);*/
}

UDPstream::~UDPstream() {

#if defined(WIN)
	closesocket(sock);
	WSACleanup();
#else
	close(sock);
#endif
}

bool UDPstream::send_data(const char* data, const char* ip, int port) {

	sockaddr_in addr_other;
	addr_other.sin_family = AF_INET;
	addr_other.sin_port = htons(port);
	addr_other.sin_addr.s_addr = inet_addr(ip);

	return !is_error_socket(
		sendto(sock, data,
			strlen(data), 0, (sockaddr*)(&addr_other),
			sizeof(addr_other))
	);
}

bool UDPstream::get_data(char* data, int buffersize, char* ip, int& port) {
	sockaddr_in sender_addr;
	int len = sizeof(sockaddr_in);
	
	std::clog << "buffersize:" << buffersize << std::endl;
	if (is_error_socket(recvfrom(sock, data, sizeof(data), 0, (sockaddr*)(&sender_addr), &len))) {
		std::clog << data << "-- err --" << WSAGetLastError() << std::endl;
		return false;
	}
	std::clog << data<< "-- nn --" << std::endl;
	sprintf(ip, "%s", inet_ntoa(sender_addr.sin_addr));
	port = ntohs(sender_addr.sin_port);
	return true;
}

// UDP gram

UDPgram::UDPgram(const char* data, const char* ip, int port) {
	Data = (char*)data;
	Ip = (char*)ip;
	Port = port;
}

UDPgram::UDPgram(std::string data, const char* ip, int port) {
	Data = (char*)data.c_str();
	Ip = (char*)ip;
	Port = port;
}

// UDP data

UDPdata::UDPdata(int buffersize) {
	buffer_size = buffersize;
	data = new char[buffersize];
	ip = NULL;
	memset(data, '\0', buffersize * sizeof(char));
}

UDPdata::UDPdata(const UDPdata& b) {
	buffer_size = b.buffer_size;
	data = new char[b.buffer_size];
	strcpy((char*)ip, b.ip);
	memcpy(data, b.data, buffer_size * sizeof(char));
	port = b.port;
}

UDPdata::UDPdata(UDPdata&& b) {
	buffer_size = b.buffer_size;
	ip = b.ip;
	data = b.data;
	port = b.port;
}

UDPdata::~UDPdata() {
	delete[]data;
	delete[]ip;
}

const char* UDPdata::get_data() {
	return data;
}

const char* UDPdata::get_ip() {
	return ip;
}

int UDPdata::get_port() {
	return port;
}