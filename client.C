/*
 * client.C
 *
 *  Created on: 20.12.2023
 *      Author: Lau Niko, Hetfleisch Jessica
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream>
#include <cstdio>

#include "SIMPLESOCKET.H"

using namespace std;



int zfl (TCPclient *c ) {                                // Strategie: Feld wird nur mit zufälligen Parametern beschossen

    string msg;
    stringstream s;
    int r;
    int z1 = 0;                                         // Zähler für die Anzahl der Durchläufe

    s << "NEUEWELT"<<  endl;                            // Eine neue Welt wird angefordert
    c->sendData(s.str());
    msg = c->receive(32);
    cout << msg << endl;

    do{

        int x = rand() %10 +1;                          // zufällige Zahlen zwischen 1 und 10
        int y = rand() %10 +1;


        stringstream s;

        s << "SHOOT[" << x << "," << y << "]";
        msg = s.str ();
        c->sendData(msg.c_str());
        z1++;                                          // Anzahl der der Durchläufe wird hier um 1 hochgezählt
        msg = c->receive(32);                          // empfangener String vom Server, überschreibt den String msg
        cout << "got response" << msg << endl;
        sscanf(msg.c_str(), "RESULT[%i]", &r);                 // aus dem String des Servers wird die Variable r ausgelesn und in eine Integer Variable umgewandelt

    }while (r != 4);

    cout << z1 << endl;
    //cout << "Alle Schiffe wurden versenkt" << endl;
    return (0);

}

int jdfld (TCPclient *c ){                              // Strategie: Alle Felder werden nacheinander beschossen.

    int x = 1;
    int y = 1;
    int z3 = 0;                                         // Durchlaufzähler
    int r;

    stringstream s;
    string msg;

    s << "NEUEWELT"<<  endl;                            // Eine neue Welt wird angefordert
    c->sendData(s.str());
    msg = c->receive(32);
    cout << msg << endl;


    for ( x=1; x<=10; x++){                                 // Aüßere Schleife zum hochzählen der x-Parameter
        for (y=1; y<=10; y++){                              // Innere Schleife zum Durchlaufen der y-Parameter

                stringstream s;

                s << "SHOOT[" << x << "," << y << "]";
                msg = s.str ();
                c->sendData(msg.c_str());
                z3++;                                          // Anzahl der der Durchläufe wird hier um 1 hochgezählt
                msg = c->receive(32);
                sscanf(msg.c_str(), "RESULT[%i]", &r);

                if (r ==4){
                cout << z3 << endl;
                return z3;
                }

        }
    }

}


int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);
    jdfld (&c);                                 // Strategie jdfld einmalig durchlaufen lassen
    //zfl (&c);                                 // Strategie zfl einmalig durchlaufen lassen
    /*for (int x=0; x<101; x++){                // Schleife um die Strategie zfl beliebig oft durchzuführen
    zfl (&c);
    }*/

    /*for (int x=0; x<101; x++){                // Schleife um die Strategie jdfld beliebig oft durchzuführen
    jdfld (&c);
    }*/


    return 0;
}







