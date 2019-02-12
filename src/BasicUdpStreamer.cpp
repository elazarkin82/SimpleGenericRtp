/*
 * BasicUdpStreamer.cpp
 *
 *  Created on: 5 Feb 2019
 *      Author: elazarkin
 */

#include <streamers/BasicUdpStreamer.h>

BasicUdpStreamer::BasicUdpStreamer()
{
	m_receiveSocketFd = -1;
	m_sendSocketFd = -1;
}

BasicUdpStreamer::~BasicUdpStreamer()
{
	destroySendMode();
	destroyReceiveMode();
}

bool BasicUdpStreamer::isExternStartReceiveValiable()
{
	return true;
}

bool BasicUdpStreamer::initReceiveMode(int port)
{
	bool ret = false;

	if(m_receiveSocketFd > 0) destroyReceiveMode();

	m_receiveProtectMutex.lock();

	if((m_receiveSocketFd=socket(AF_INET, SOCK_DGRAM, 0)) > 0)
	{
		struct timeval tv;

		m_last_receive_sockaddr.sin_family = AF_INET;
		m_last_receive_sockaddr.sin_port = htons(port);
		m_last_receive_sockaddr.sin_addr.s_addr = INADDR_ANY;

		if (bind(m_receiveSocketFd, (const sockaddr *)&m_last_receive_sockaddr, sizeof(m_last_receive_sockaddr)) != -1)
		{
			ret = true;
		}
		else
		{
			fprintf(stderr, "receive socket bind failed\n");
			close(m_receiveSocketFd);
			m_receiveSocketFd = -1;
		}

		tv.tv_sec = 0;
		tv.tv_usec = 100000;
		setsockopt(m_receiveSocketFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

		ret = true;
	}

	m_receiveProtectMutex.unlock();

	return ret;
}

bool BasicUdpStreamer::destroyReceiveMode()
{
	std::lock_guard<std::mutex> guard(m_receiveProtectMutex);

	if(m_receiveSocketFd > 0)
	{
		close(m_receiveSocketFd);
		m_receiveSocketFd = -1;
	}
	return false;
}

bool BasicUdpStreamer::initSendMode(const char *ip, int port)
{
	bool ret = false;

	if(m_sendSocketFd > 0) destroySendMode();

	m_sendProtectMutex.lock();

	if ((m_sendSocketFd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
	{
		m_send_sockaddr.sin_family = AF_INET;
		m_send_sockaddr.sin_port = htons(port);
		m_send_sockaddr.sin_addr.s_addr = inet_addr(ip);
	}
	else
	{
		fprintf(stderr, "socket creation failed\n");
	}

	m_sendProtectMutex.unlock();

	return ret;
}

bool BasicUdpStreamer::destroySendMode()
{
	std::lock_guard<std::mutex> guard(m_sendProtectMutex);

	if(m_sendSocketFd > 0)
	{
		close(m_sendSocketFd);
		m_sendSocketFd = -1;
	}

	return true;
}

int BasicUdpStreamer::send(const char *buffer, int size)
{
	std::lock_guard<std::mutex> guard(m_sendProtectMutex);

	static int len = sizeof(struct sockaddr_in);

	if(m_sendSocketFd > 0)
	{
		sendto(m_sendSocketFd, buffer, size, MSG_CONFIRM, (const struct sockaddr *) &m_send_sockaddr, len);
	}

	return 0;
}

int BasicUdpStreamer::proccessRead(UdpReceiveCallback *callback)
{
	static unsigned int len = sizeof(struct sockaddr_in);

	if(m_receiveSocketFd)
	{
		int ret = recvfrom(m_receiveSocketFd, m_readBuffer, sizeof(m_readBuffer), 0, (sockaddr *)&m_last_receive_sockaddr, &len);

		fprintf(stdout, "proccessRead: %d bytes\n", ret);

		if(ret > 0) callback[0](m_readBuffer, ret, "TODO_ADD_IP");

		return ret;
	}

	return 0;
}


