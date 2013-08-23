#ifndef Network_h__
#define Network_h__

#include <SFML/Network.hpp>

#include "mymath/mymath.h"
#include "inGameState.h"

class mypacket
{
public:

	mm::vec2 pos;

	float alfa;

	mypacket(int x, int y, float alfa){

		pos.x = x;
		pos.y = y;

		this->alfa = alfa;

	}

	~mypacket(){}

	
};


class network{

private:

	//for the ping
	sf::Clock clock;

	bool isServer;

	sf::Socket::Status status;

	sf::TcpSocket* server;

	sf::TcpSocket* client;
	
	//InGameState* ingamestate;

public:
	
	network(/*InGameState* state*/);

	~network();

	sf::IpAddress getIP();

	void connect();

	void send();

	void recive();

	//main function
	void update();

};

sf::Packet& operator <<(sf::Packet& packet, const mypacket& character);

sf::Packet& operator >>(sf::Packet& packet, mypacket& character);


#endif // Network_h_