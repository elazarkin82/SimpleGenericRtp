/*
 * BasicUdpStreamer.cpp
 *
 *  Created on: 5 Feb 2019
 *      Author: elazarkin
 */

#include <udp/BasicUdpStreamer.h>

BasicUdpStreamer::BasicUdpStreamer()
{

}

BasicUdpStreamer::~BasicUdpStreamer()
{

}

void BasicUdpStreamer::setSendParams(const char *ip, int port)
{

}

void BasicUdpStreamer::setReceiveParams(int port)
{
	// TODO
}

bool BasicUdpStreamer::startReceiveMode()
{
	// TODO
	return false;
}

bool BasicUdpStreamer::stopReceiveMode()
{
	// TODO
	return false;
}

int BasicUdpStreamer::send(char *buffer, int size)
{
	std::lock_guard<std::mutex> guard(m_sendProtectMutex);
	// TODO
	return 0;
}

int BasicUdpStreamer::read(char *readBuffer, const int MAX_SIZE, char *sendedFromIP)
{
	// TODO
	return 0;
}


