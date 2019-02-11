/*
 * IComunicationObject.cpp
 *
 *  Created on: 6 Feb 2019
 *      Author: elazarkin
 */

#include <udp/IComunicationObject.h>

#include <unistd.h>

IComunicationObject::IComunicationObject()
{
	memset(m_sendIp, 0, sizeof(m_sendIp));

	m_sendPort 		= 0;
	m_receivePort 	= 0;

	m_receiveThread = NULL;

	m_receiveKeepAlive = false;
}

IComunicationObject::~IComunicationObject()
{

}

void IComunicationObject::setSendParams(const char *ip, int port)
{
	if(ip == NULL)
	{
		memset(m_sendIp, 0, sizeof(m_sendIp));
		m_sendPort = 0;
	}
	else
	{
		sprintf(m_sendIp, "%s", ip);
		m_sendPort = port;
	}
}

void IComunicationObject::setReceiveParams(int port)
{
	m_receivePort = port;
}

void IComunicationObject::receiveThreadLoop(UdpReceiveCallback *callback)
{
	initReceiveMode(m_receivePort);

	/*
	 * proccessRead is block read so not need sleep between read to read
	 */
	while(m_receiveKeepAlive)
	{
		proccessRead(callback);
	}

	destroyReceiveMode();
}

bool IComunicationObject::internalStartReceiveMode(UdpReceiveCallback *callback)
{
	std::lock_guard<std::mutex> guard(m_receiveModeMutex);

	if(m_receiveThread == NULL)
	{
		m_receiveKeepAlive = true;
		m_receiveThread = new std::thread(&IComunicationObject::receiveThreadLoop, this, callback);

		return true;
	}

	return false;
}

bool IComunicationObject::startReceiveMode(UdpReceiveCallback *callback)
{
	if(isExternStartReceiveValiable())
	{
		return internalStartReceiveMode(callback);
	}

	return false;
}

bool IComunicationObject::stopReceiveMode()
{
	std::lock_guard<std::mutex> guard(m_receiveModeMutex);

	if(m_receiveThread != NULL)
	{
		if(m_receiveThread->joinable())
		{
			m_receiveThread->join();
		}

		m_receiveThread = NULL;
	}

	return true;
}
