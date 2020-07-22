//   Copyright 2015 Ansersion
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//

#ifndef MY_RTP_TCP_SESSION_H
#define MY_RTP_TCP_SESSION_H

#ifdef _MSC_VER
//#include <windows.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "myRtpSession.h"


class MyRTPTCPSession : public MyRTPSession
{
	public:
		MyRTPTCPSession();
		virtual ~MyRTPTCPSession();
		virtual int MyRTP_SetUp(MediaSession * media_session, SocketType tunnelling_sock);

		/* Wait 1 second for TEARDOWN at default */
		virtual void MyRTP_Teardown(MediaSession * media_session, struct timeval * tval = NULL);
		virtual uint8_t * GetMyRTPData(uint8_t * data_buf, size_t * size, unsigned long timeout_ms);
		virtual uint8_t * GetMyRTPPacket(uint8_t * packet_buf, size_t * size, unsigned long timeout_ms);

		void SetDestroiedClbk(void (*clbk)()) {DestroiedClbk = clbk;}

        virtual void LockSocket();
        virtual void UnlockSocket();
        virtual bool TryLockSocket();
#ifdef _MSC_VER
			virtual SOCKET GetTunnellingSocket() const { return TunnellingSock; }
#else
		virtual int GetTunnellingSocket() const { return TunnellingSock; }
#endif
        virtual void SetRecvRtspCmdClbk(void (*clbk)(char *cmd));
    private:
        int MyTcpCreate(const RTPSessionParams &sessparams,const RTPTransmissionParams *transparams);
        // int Poll();
        // int ProcessPolledData();
	protected: 
		void OnNewSource(RTPSourceData *dat);
		void OnBYEPacket(RTPSourceData *dat);
		void OnRemoveSource(RTPSourceData *dat);

	private:
#ifdef _MSC_VER
		SOCKET TunnellingSock;
#else
        int TunnellingSock;
#endif
		void (*DestroiedClbk)();
#ifdef _MSC_VER
		CRITICAL_SECTION SocketMutex;
#else
        pthread_mutex_t SocketMutex;
#endif
        int TrylockTimes;


};

#endif
