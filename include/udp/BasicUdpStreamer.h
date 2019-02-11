/*
 * BasicUdpStreamer.h
 *
 *  Created on: 29 Jan 2019
 *      Author: elazarkin
 */

#ifndef INCLUDE_UDP_BASICUDPSTREAMER_H_
#define INCLUDE_UDP_BASICUDPSTREAMER_H_

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <mutex>

#include "IComunicationObject.h"

class BasicUdpStreamer: public IComunicationObject
{
private:

	char m_readBuffer[65536];

	std::mutex m_sendProtectMutex, m_receiveProtectMutex;

	int m_receiveSocketFd, m_sendSocketFd;

	struct sockaddr_in m_send_sockaddr, m_last_receive_sockaddr;

protected:

	int proccessRead(UdpReceiveCallback *callback);

	bool isExternStartReceiveValiable();

	bool initReceiveMode(int port);

	bool destroyReceiveMode();

	bool initSendMode(const char *ip, int port);

	bool destroySendMode();

public:

	BasicUdpStreamer();

	virtual ~BasicUdpStreamer();

	int send(const char *buffer, int size);
};



#endif /* INCLUDE_UDP_BASICUDPSTREAMER_H_ */
