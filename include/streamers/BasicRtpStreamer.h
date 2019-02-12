/*
 * BasicRtpStreamer.h
 *
 *  Created on: 12 Feb 2019
 *      Author: elazarkin
 */

#ifndef INCLUDE_RTP_BASICRTPSTREAMER_H_
#define INCLUDE_RTP_BASICRTPSTREAMER_H_

#include "BasicUdpStreamer.h"

class BasicRtpStreamer: public BasicUdpStreamer
{
public:
	BasicRtpStreamer();
	virtual ~BasicRtpStreamer();

protected:

	bool isExternStartReceiveValiable();
};

#endif /* INCLUDE_RTP_BASICRTPSTREAMER_H_ */
