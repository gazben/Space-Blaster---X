#include "Network.h"

#include <SFML/Network.hpp>


network::network(/*InGameState* state*/)//:ingamestate(state)
{
	/*
	if( isServer == true){

		client = NULL;

		server = new sf::TcpSocket();

	}else
	{
		server = NULL;

		client = new sf::TcpSocket();

		connect();

	}
	*/
}

network::~network()
{
	if ( isServer == true){

		delete server;

	}else
	{
		delete client;
	}
}

void network::connect()
{

}

sf::IpAddress network::getIP(){

	return sf::IpAddress::getLocalAddress();
}

//all of the outgoing data 
void network::send()
{

}

//all of the incoming data
void network::recive()
{
	
}

void network::update()
{

	send();

	recive();

}

sf::Packet& operator <<(sf::Packet& packet, const mypacket& Mypacket)
{
	return packet << Mypacket.pos.x << Mypacket.pos.y  << Mypacket.alfa;
}

sf::Packet& operator >>(sf::Packet& packet, mypacket& Mypacket)
{
	return packet >> Mypacket.pos.x >> Mypacket.pos.y >> Mypacket.alfa;
}