/*
 * BasicUdpStreamer.h
 *
 *  Created on: 29 Jan 2019
 *      Author: elazarkin
 */

#ifndef INCLUDE_UDP_BASICUDPSTREAMER_H_
#define INCLUDE_UDP_BASICUDPSTREAMER_H_

#include "IUdpObject.h"

#include <mutex>

class BasicUdpStreamer: public IUdpObject
{
private:

	std::mutex m_sendProtectMutex;

public:

	BasicUdpStreamer();

	virtual ~BasicUdpStreamer();

	void setSendParams(const char *ip, int port);

	void setReceiveParams(int port);

	bool startReceiveMode();

	bool stopReceiveMode();

	int send(const char *buffer, int size);

	int read(char *readBuffer, const int MAX_SIZE, char *sendedFromIP = NULL);
};



#endif /* INCLUDE_UDP_BASICUDPSTREAMER_H_ */
