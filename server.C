/*
 * client.C
 *
 *  Created on: 20.12.2023
 *      Author: Lau Niko, Hetfleisch Jessica
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <iostream>
#include "SIMPLESOCKET.H"
#include "TASK3.H"
#include <sstream>

class myServer: public TCPserver{
protected:

    TASK3::World *w;




public:
    myServer(int port, int size): TCPserver(port, size){

    w=new TASK3::World();

    };

    string myResponse(string input);

};


int main(){
	srand(time(nullptr));
	myServer srv(2022,25);
	srv.run();
}
string myServer :: myResponse (string input){
    int x,y;

    if (input.compare(0,6,"SHOOT[")==0){
        //std::cout << "shoot commando received./n";
        sscanf(input.c_str(),"SHOOT[%i,%i]",&x,&y);
        //std::cout << "x:" <<"y:" <<y <<std::endl;
        if (x<1)return string ("Error, x out of range");
        if (x>10)return string ("Error, x out of range");
        if (y<1)return string ("Error, y out of range");
        if (y>10)return string ("Error, y out of range");

        TASK3::ShootResult r;
        r= w->shoot(x,y);

        std::stringstream scout;

        scout << "RESULT["<<r<<"]";
        return scout.str();


        //return string("OKAY");
    }

    if(input.compare(0,8,"NEUEWELT")==0){

        delete w;
        w= new TASK3::World();
        return string("OK");

    }


    return string ("ERROR. Unknow command");
};
