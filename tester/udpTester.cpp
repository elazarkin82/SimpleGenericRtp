#include <stdlib.h>
#include <stdio.h>
#include <udp/BasicUdpStreamer.h>

#include <thread>

#include <unistd.h>

bool s_keepAlive;

void sendLoop()
{
	IUdpObject *obj = new BasicUdpStreamer();

	const char buffer[] = "test message %d!";

	obj->setSendParams("127.0.0.1", 5555);

	while(s_keepAlive)
	{
		obj->send(buffer, sizeof(buffer));
	}

	delete obj;
}

void receiveLoop()
{
	IUdpObject *obj = new BasicUdpStreamer();

	obj->setReceiveParams(5555);

	delete obj;
}

bool testSendReceiveBlockRead()
{
	if((s_keepAlive=true))
	{
		std::thread t1(sendLoop);
		std::thread t2(receiveLoop);

		sleep(5);

		s_keepAlive = false;

		if(t1.joinable()) t1.join();
		if(t2.joinable()) t2.join();
	}

	return true;
}

int main(int argc, char **argv)
{
	for(int i = 0; i < 10; i++)
	{
		fprintf(stdout, "testSendReceiveBlockRead num %d %s!\n", i, (testSendReceiveBlockRead() ? "success":"fail"));
	}

	return 0;
}
