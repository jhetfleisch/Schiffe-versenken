/*
 * client.C
 *
 *  Created on: 20.12.2023
 *      Author: Lau Niko, Hetfleisch Jessica
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"

using namespace std;

class myClient: public TCPclient{
public:
    myClient(): TCPclient(){};

    string response(string incomingMsg);
};

int main() {
	srand(time(NULL));
	myClient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);

	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}
		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);

	}
}


string myClient :: response (string incomingMsg){
    return string ("unknow");
};






