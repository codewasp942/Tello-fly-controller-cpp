#include <iostream>
#include <cstring>
#include "UDPstream.h"

using namespace std;
using namespace UDP;

int main() {
	UDPstream s(8889);
	UDPdata dat;
	char str[1000];

	char k[1000],ip[1000];
	int pt;

	memset(k, '\0', 1000);

	s << UDPgram("command", "192.168.10.1", 8889);
	s.get_data(k, 100, ip, pt);

	
	cout << k << endl;

	while (1) {
		gets_s(str);
		s << UDPgram(str, "192.168.10.1", 8889);
	}
	
	return 0;
}