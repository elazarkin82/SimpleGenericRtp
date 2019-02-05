/*
 * IUdpObject.h
 *
 *  Created on: 29 Jan 2019
 *      Author: elazarkin
 */

#ifndef INCLUDE_UDP_IUDPOBJECT_H_
#define INCLUDE_UDP_IUDPOBJECT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class IUdpObject
{
public:

	typedef void(UdpReceiveCallback)(char *buffer, int size, const char *receiveAddr);

private:

	static void MOCK_RECEIVE_CALLBACK(char *buffer, int size, const char *receiveAddr)
	{
		fprintf(stderr, "called MOCK_RECEIVE_CALLBACK - maybe something not initilized!\n");
	}

	UdpReceiveCallback *m_callback;

	char m_sendIp[256];

	int m_sendPort;

	int m_receivePort;

public:

	IUdpObject()
	{
		setReceiveCallback(NULL);

		memset(m_sendIp, 0, sizeof(m_sendIp));

		m_sendPort 		= 0;
		m_receivePort 	= 0;
	}

	void setReceiveCallback(UdpReceiveCallback *callback)
	{
		m_callback = callback == NULL ? MOCK_RECEIVE_CALLBACK:callback;
	}

	const UdpReceiveCallback *getCallback()
	{
		return m_callback;
	}

	virtual ~IUdpObject(){}

	void setSendParams(const char *ip, int port)
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

	void setReceiveParams(int port)
	{
		m_receivePort = port;
	}

	virtual bool startReceiveMode() = 0;

	virtual bool stopReceiveMode() = 0;

	virtual int send(const char *buffer, int size) = 0;

	virtual int read(char *readBuffer, const int MAX_SIZE, char *sendedFromIP = NULL) = 0;
};


#endif /* INCLUDE_UDP_IUDPOBJECT_H_ */
