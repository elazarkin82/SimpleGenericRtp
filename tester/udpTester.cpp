#include <stdlib.h>
#include <stdio.h>
#include <udp/BasicUdpStreamer.h>

#include <thread>

#include <unistd.h>

bool s_keepAlive;

void sendLoop()
{
	IComunicationObject *obj = new BasicUdpStreamer();

	const char text_format[] = "test message %d!";
	char buffer[128];
	int counter = 0;

	obj->setSendParams("127.0.0.1", 5555);

	while(s_keepAlive)
	{
		sprintf(buffer, text_format, counter);
		fprintf(stdout, "send: %s\n", buffer);
		obj->send(buffer, sizeof(buffer));
		usleep(100000);
	}

	delete obj;
}

std::function<void (char *, int, const char *)> callback = [&](char *buffer, int size, const char *fromIP)
{
	fprintf(stdout, "receive: %s\n", buffer);
};

bool testSendReceiveBlockRead()
{
	s_keepAlive=true;

	if(s_keepAlive)
	{
		IComunicationObject *obj = new BasicUdpStreamer();

		std::thread t1(sendLoop);

		obj->setReceiveParams(5555);

		obj->startReceiveMode(&callback);

		sleep(5);

		s_keepAlive = false;

		if(t1.joinable()) t1.join();

		obj->stopReceiveMode();

		delete obj;
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
