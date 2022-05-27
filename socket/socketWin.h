#pragma comment(lib, "ws2_l2.lib")
#include <Ws2tcpip.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <unistd.h>


#define IP_ADDRESS "192.168.100.58"
#define PORT 4000

using namespace std;

class socketclient {
	public:
        SOCKET sock = 0;
        int valread;
				

	//public:
        socketclient(){}

		void init() {
            WSAData wsaData;
            WORD DllVersion = MAKEWORD(2,1);
            WSAStartup(DllVersion, &wsaData);

            if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
				printf("\n Socket creation error \n");
			}

            sockaddr_in serv_addr;
			serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
            serv_addr.sin_port = htons(PORT);

			if (connect(sock, (const sockaddr *)&serv_addr,sizeof(serv_addr)) != 0) {
				printf("\nConnection Failed \n");
			}
		}

		// alpha are numbers from 0 to 255
		void paintLine(int pRed, int pGreen, int pBlue, int pAlpha, int x0, int y0, int x1, int y1) {
			string message = "line,"+to_string(pRed)+","+to_string(pGreen)+","+to_string(pBlue)+","+to_string(pAlpha)+",";
			message += to_string(x0)+","+to_string(y0)+","+to_string(x1)+","+to_string(y1)+"\n";
			const char* msg = message.c_str();
            cout<<msg<<endl;
			send(sock,msg, strlen(msg), 0);
		}

		void paintDot(int pRed, int pGreen, int pBlue, int pAlpha, int x0, int y0, int pRadius) {
			string message = "dot,"+to_string(pRed)+","+to_string(pGreen)+","+to_string(pBlue)+","+to_string(pAlpha)+",";
			message += to_string(x0)+","+to_string(y0)+","+to_string(pRadius)+"\n";
			const char* msg = message.c_str();
            cout<<msg<<endl;
			send(sock,msg, strlen(msg), 0);
		}

		void clear() {
			const char* msgclear = "clear\n";
            cout<<msgclear<<endl;
			send(sock, msgclear, strlen(msgclear), 0);
		}

		void closeConnection() {
			closesocket(sock);
		}
};

// int main(int argc, char const *argv[])
// {

//     socketclient client;

//     client.init();

//     client.clear();
//     client.paintLine(100, 255, 176, 255, 100, 100, 250, 600);
//     client.paintDot(200, 0, 15, 200, 500, 600, 15);
//     client.paintDot(220, 150, 15, 200, 600, 600, 20);

//     client.closeConnection();

//     return 0;
// }
