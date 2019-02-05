/*
 * IUdpObject.h
 *
 *  Created on: 29 Jan 2019
 *      Author: elazarkin
 */

#ifndef INCLUDE_UDP_IUDPOBJECT_H_
#define INCLUDE_UDP_IUDPOBJECT_H_

#include <stdlib.h>

class IUdpObject
{
public:

	typedef void(UdpReceiveCallback)(char *buffer, int size, const char *receiveAddr);

	virtual ~IUdpObject(){}

	virtual void setSendParams(const char *ip, int port) = 0;

	virtual void setReceiveParams(int port) = 0;

	virtual bool startReceiveMode() = 0;

	virtual bool stopReceiveMode() = 0;

	virtual int send(char *buffer, int size) = 0;

	virtual int read(char *readBuffer, const int MAX_SIZE, char *sendedFromIP = NULL) = 0;
};


#endif /* INCLUDE_UDP_IUDPOBJECT_H_ */
