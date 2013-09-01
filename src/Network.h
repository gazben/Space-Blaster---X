#ifndef Network_h__
#define Network_h__

#include <SFML/Network.hpp>

#include "mymath/mymath.h"
#include "game.h"

class strpacket{

public:

	strpacket();
	strpacket( std::string );
	~strpacket();

	std::string str;
};

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
	sf::Time time;
	sf::Clock clock;

	bool inLobby;
	bool isServer;
	bool isConnected;

	sf::Packet packet;

	std::string ipadress;
	sf::Socket::Status status;
	sf::TcpSocket socket;

	Game* game;

public:
	
	network();

	network( Game* , std::string , bool );

	~network();

	sf::IpAddress getIP();

	void setState( Game*);

	void setIP(std::string);

	void setServer( bool );

	void setLobby( bool );

	bool connected();

	void sendName();

	void send();

	void recive();

	//main function
	void update();


};

sf::Packet& operator <<(sf::Packet& packet, const mypacket& character);

sf::Packet& operator >>(sf::Packet& packet, mypacket& character);

sf::Packet& operator << (sf::Packet& packet, const strpacket& Mypacket);

sf::Packet& operator >> (sf::Packet& packet, strpacket& Mypacket);

#endif // Network_h_