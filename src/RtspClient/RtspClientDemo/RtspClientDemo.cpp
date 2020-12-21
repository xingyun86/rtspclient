// RtspClientDemo.cpp : Defines the entry point for the application.
//
//   Copyright 2015-2016 Ansersion
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

#include <iostream>
#include "rtspClient.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <thread>
#ifdef _MSC_VER
#include <winsock2.h>
#include <stdint.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

using std::cout;
using std::endl;

void* audio(void* args);
void* video(void* args);

#include <regex>

int main(int argc, char* argv[])
{
	NETWORK_STARTUP();
	//pthread_t RecvVideo;
	//pthread_t RecvAudio;
	std::thread RecvVideo;
	std::thread RecvAudio;

	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <URL>" << endl;
		cout << "For example: " << endl;
		cout << argv[0] << " rtsp://127.0.0.1/ansersion" << endl;
		cout << argv[0] << " rtsp://username:password@127.0.0.1:554/stream" << endl;
		system("pause");
		return 1;
	}

	cout << "Start play " << argv[1] << endl;
	cout << "Then put video data into test_video_recv.h264; ";
	cout << "And put audio data into test_audio_recv.mp3" << endl;

	//string RtspUri("rtsp://ppshuai:pps123456@192.168.1.64:554/Streaming/Channels/101?transportmode=unicast&profile=Profile_1");
	string RtspUri(argv[1]);
	
	// string RtspUri("rtsp://192.168.81.145/ansersion");
	RtspClient Client;

	/* Set up rtsp server resource URI */
	Client.SetURI(RtspUri);

	/* Send DESCRIBE command to server */
	Client.DoDESCRIBE();

	/* Parse SDP message after sending DESCRIBE command */
	Client.ParseSDP();

	/* Send SETUP command to set up all 'audio' and 'video'
	 * sessions which SDP refers. */
	Client.DoSETUP();

	/* Send PLAY command to play 'video' and 'audio' sessions.*/
	Client.DoPLAY();

	RecvAudio = std::thread(audio, &Client);
	RecvVideo = std::thread(video, &Client);
	RecvAudio.join();
	RecvVideo.join();
	//pthread_create(&RecvAudio, NULL, audio, (void*)(&Client));
	//pthread_create(&RecvVideo, NULL, video, (void*)(&Client));
	//pthread_join(RecvAudio, NULL);
	//pthread_join(RecvVideo, NULL);

	printf("start TEARDOWN\n");
	/* Send TEARDOWN command to teardown all of the sessions */
	Client.DoTEARDOWN();

	NETWORK_CLEANUP();

	return 0;
}

void* audio(void* args)
{
	/* Receive 1000 RTP 'video' packets
	 * note(FIXME):
	 * if there are several 'video' session
	 * refered in SDP, only receive packets of the first
	 * 'video' session, the same as 'audio'.*/
	int packet_num = 0;
	const size_t BufSize = 65534;
	uint8_t buf[BufSize];
	size_t size = 0;

	RtspClient* Client = (RtspClient*)args;

	/* Write h264 video data to file "test_packet_recv.h264"
	 * Then it could be played by ffplay */
	FILE * fp = fopen("test_audio_recv.mp3", "wb");

	if (fp != nullptr)
	{
		while (++packet_num < 1000) {
			if (!Client->GetMediaData("audio", buf, &size, BufSize)) continue;
			if (fwrite(buf, 1, size, fp) < 0) {
				perror("write");
			}
			printf("recv audio data %d: %lu bytes\n", packet_num, size);
		}
		fclose(fp);
	}
	return NULL;
}

void* video(void* args)
{
	/* Receive 1000 RTP 'video' packets
	 * note(FIXME):
	 * if there are several 'video' session
	 * refered in SDP, only receive packets of the first
	 * 'video' session, the same as 'audio'.*/
	int packet_num = 0;
	const size_t BufSize = 65534;
	uint8_t buf[BufSize];
	size_t size = 0;

	RtspClient* Client = (RtspClient*)args;

	/* Write h264 video data to file "test_packet_recv.h264"
	 * Then it could be played by ffplay */
	FILE * fp = fopen("test_video_recv.h264", "wb");
	if (fp != nullptr)
	{
		while (++packet_num < 1000) {
			if (!Client->GetMediaData("video", buf, &size, BufSize)) continue;
			if (fwrite(buf, 1, size, fp) < 0) {
				perror("write");
			}
			printf("recv video data %d: %lu bytes\n", packet_num, size);
		}
		fclose(fp);
	}
	return NULL;
}
