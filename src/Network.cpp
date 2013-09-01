#include "Network.h"

#include <SFML/Network.hpp>


//you have to set things manually!
network::network()
{
	inLobby = false;
	isServer = false;
	isConnected = false;

}

network::~network()
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
	
	strpacket temp; 
	
	if( isServer == false && isConnected == true){

		if( socket.receive( packet ) == sf::Socket::Done){
			//packet >> temp;

			//Globals::log->log( temp.str );
			Globals::log->log( "reciving..." );
		}

	}
	
}

void network::update()
{
	if( inLobby == true && isConnected == true){

		recive();
		sendName();
	}

// 	send();
// 
// 	recive();
}

void network::setIP(std::string inIP){

	ipadress = inIP;
}

bool network::connected()
{
	status = socket.connect( ipadress , 53000 );
	if( status == sf::Socket::Done ){ 
		isConnected = true;
		Globals::log->log("Connected!!!!!!!!!!!");
		return true; 
	}
	else{
		return false;
	}
}

void network::setState( Game* instate)
{
	game = instate;
}

void network::sendName()
{
	if( isServer == true && isConnected == true ){

		packet << game -> ingamestate -> player.getName();

		socket.send( packet );

		Globals::log->log( "sending name" );
	}
	
}

void network::setLobby( bool lobby)
{
	inLobby = lobby;
}

void network::setServer( bool server)
{
	if ( server )
	{Globals::log->log( "Server created" );
	}else{Globals::log->log( "Client created" );}
	
	
	isServer = server;
}

sf::Packet& operator <<(sf::Packet& packet, const mypacket& Mypacket)
{
	return packet << Mypacket.pos.x << Mypacket.pos.y  << Mypacket.alfa;
}

sf::Packet& operator >>(sf::Packet& packet, mypacket& Mypacket)
{
	return packet >> Mypacket.pos.x >> Mypacket.pos.y >> Mypacket.alfa;
}

sf::Packet& operator << (sf::Packet& packet, const strpacket& Mypacket)
{
	return packet << Mypacket.str;
}

sf::Packet& operator >> (sf::Packet& packet, strpacket& Mypacket)
{
	return packet >> Mypacket.str;
}

strpacket::strpacket( std::string inStr)
{
	str = inStr;
}

strpacket::strpacket()
{

}

strpacket::~strpacket()
{

}
