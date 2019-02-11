/*
 * IUdpObject.h
 *
 *  Created on: 29 Jan 2019
 *      Author: elazarkin
 */

#ifndef INCLUDE_UDP_ICOMUNICATIONOBJECT_H_
#define INCLUDE_UDP_ICOMUNICATIONOBJECT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <thread>
#include <mutex>
#include <functional>

class IComunicationObject
{
public:

	typedef std::function<void(char *buffer, int size, const char *receiveAddr)> UdpReceiveCallback;

private:

	char m_sendIp[256];

	int m_sendPort;

	int m_receivePort;

	std::mutex m_receiveModeMutex;

	std::thread *m_receiveThread;

	bool m_receiveKeepAlive;

protected:

	virtual int proccessRead(UdpReceiveCallback *callback) = 0;

	virtual bool initReceiveMode(int port) = 0;

	virtual bool destroyReceiveMode() = 0;

	virtual bool initSendMode(const char *ip, int port) = 0;

	virtual bool destroySendMode() = 0;

	virtual bool isExternStartReceiveValiable() = 0;

	bool internalStartReceiveMode(UdpReceiveCallback *callback);

private:

	void receiveThreadLoop(UdpReceiveCallback *callback);

public:

	IComunicationObject();

	virtual ~IComunicationObject();

	void setSendParams(const char *ip, int port);

	void setReceiveParams(int port);

	bool startReceiveMode(UdpReceiveCallback *callback);

	bool stopReceiveMode();

	virtual int send(const char *buffer, int size) = 0;
};


#endif /* INCLUDE_UDP_ICOMUNICATIONOBJECT_H_ */
