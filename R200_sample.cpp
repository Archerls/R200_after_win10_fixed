///*******************************************************************************
//
//INTEL CORPORATION PROPRIETARY INFORMATION
//This software is supplied under the terms of a license agreement or nondisclosure
//agreement with Intel Corporation and may not be copied or disclosed except in
//accordance with the terms of that agreement
//Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.
//
//*******************************************************************************/
//#include <windows.h>
//#include "RealSense/SenseManager.h"
//#include "RealSense/SampleReader.h"
//#include "util_cmdline.h"
//#include "util_render.h"
//#include <conio.h>
//
//using namespace Intel::RealSense;
//
//int wmain(int argc, WCHAR* argv[]) {
//	/* Creates an instance of the SenseManager */
//	SenseManager *pp = SenseManager::CreateInstance();
//	if (!pp) {
//		wprintf_s(L"Unable to create the SenseManager\n");
//		return 3;
//	}
//
//	/* Collects command line arguments */
//	UtilCmdLine cmdl(pp->QuerySession());
//	if (!cmdl.Parse(L"-listio-nframes-sdname-csize-dsize-isize-lsize-rsize-file-record-noRender-mirror", argc, argv)) return 3;
//
//	/* Sets file recording or playback */
//	CaptureManager *cm = pp->QueryCaptureManager();
//	cm->SetFileName(cmdl.m_recordedFile, cmdl.m_bRecord);
//	if (cmdl.m_sdname) cm->FilterByDeviceInfo(cmdl.m_sdname, 0, 0);
//
//	// Create stream renders
//	UtilRender renderc(L"Color"), renderd(L"Depth"), renderi(L"IR"), renderr(L"Right"), renderl(L"Left");
//	Status sts;
//	do {
//		/* Apply command line arguments */
//		bool revert = false;
//		if (cmdl.m_csize.size() > 0) {
//			pp->EnableStream(Capture::STREAM_TYPE_COLOR, cmdl.m_csize.front().first.width, cmdl.m_csize.front().first.height, (pxcF32)cmdl.m_csize.front().second);
//		}
//		if (cmdl.m_dsize.size() > 0) {
//			pp->EnableStream(Capture::STREAM_TYPE_DEPTH, cmdl.m_dsize.front().first.width, cmdl.m_dsize.front().first.height, (pxcF32)cmdl.m_dsize.front().second);
//		}
//		if (cmdl.m_isize.size() > 0) {
//			pp->EnableStream(Capture::STREAM_TYPE_IR, cmdl.m_isize.front().first.width, cmdl.m_isize.front().first.height, (pxcF32)cmdl.m_isize.front().second);
//		}
//		if (cmdl.m_rsize.size() > 0) {
//			pp->EnableStream(Capture::STREAM_TYPE_RIGHT, cmdl.m_rsize.front().first.width, cmdl.m_rsize.front().first.height, (pxcF32)cmdl.m_rsize.front().second);
//		}
//		if (cmdl.m_lsize.size() > 0) {
//			pp->EnableStream(Capture::STREAM_TYPE_LEFT, cmdl.m_lsize.front().first.width, cmdl.m_lsize.front().first.height, (pxcF32)cmdl.m_lsize.front().second);
//		}
//		if (cmdl.m_csize.size() == 0 && cmdl.m_dsize.size() == 0 && cmdl.m_isize.size() == 0 && cmdl.m_rsize.size() == 0 && cmdl.m_lsize.size() == 0) {
//			DataDesc desc = {};
//			if (cm->QueryCapture()) {
//				cm->QueryCapture()->QueryDeviceInfo(0, &desc.deviceInfo);
//			}
//			else {
//				desc.deviceInfo.streams = Capture::STREAM_TYPE_LEFT | Capture::STREAM_TYPE_RIGHT;
//				revert = true;
//			}
//			pp->EnableStreams(&desc);
//		}
//
//		/* Initializes the pipeline */
//		sts = pp->Init();
//		if (sts < Status::STATUS_NO_ERROR) {
//			if (revert) {
//				/* Enable a single stream */
//				pp->Close();
//				pp->EnableStream(Capture::STREAM_TYPE_DEPTH);
//				sts = pp->Init();
//				if (sts < Status::STATUS_NO_ERROR) {
//					pp->Close();
//					pp->EnableStream(Capture::STREAM_TYPE_COLOR);
//					sts = pp->Init();
//				}
//			}
//			if (sts < Status::STATUS_NO_ERROR) {
//				wprintf_s(L"Failed to locate any video stream(s)\n");
//				pp->Release();
//				return sts;
//			}
//		}
//
//		/* Reset all properties */
//		Capture::Device *device = pp->QueryCaptureManager()->QueryDevice();
//		device->ResetProperties(Capture::STREAM_TYPE_ANY);
//
//		/* Set mirror mode */
//		if (cmdl.m_bMirror) {
//			device->SetMirrorMode(Capture::Device::MirrorMode::MIRROR_MODE_HORIZONTAL);
//		}
//		else {
//			device->SetMirrorMode(Capture::Device::MirrorMode::MIRROR_MODE_DISABLED);
//		}
//
//		/* Stream Data */
//		for (int nframes = 0; nframes < cmdl.m_nframes; nframes++) {
//			/* Waits until new frame is available and locks it for application processing */
//			sts = pp->AcquireFrame(false);
//
//			if (sts < Status::STATUS_NO_ERROR) {
//				if (sts == Status::STATUS_STREAM_CONFIG_CHANGED) {
//					wprintf_s(L"Stream configuration was changed, re-initilizing\n");
//					pp->Close();
//				}
//				break;
//			}
//
//			/* Render streams, unless -noRender is selected */
//			if (cmdl.m_bNoRender == false) {
//				const Capture::Sample *sample = pp->QuerySample();
//				if (sample) {
//					if (sample->depth && !renderd.RenderFrame(sample->depth)) break;
//					if (sample->color && !renderc.RenderFrame(sample->color)) break;
//					if (sample->ir && !renderi.RenderFrame(sample->ir))    break;
//					if (sample->right && !renderr.RenderFrame(sample->right)) break;
//					if (sample->left && !renderl.RenderFrame(sample->left))  break;
//				}
//			}
//
//			/* Releases lock so pipeline can process next frame */
//			pp->ReleaseFrame();
//
//			if (_kbhit()) { // Break loop
//				int c = _getch() & 255;
//				if (c == 27 || c == 'q' || c == 'Q') break; // ESC|q|Q for Exit
//			}
//		}
//	} while (sts == Status::STATUS_STREAM_CONFIG_CHANGED);
//
//	wprintf_s(L"Exiting\n");
//
//	// Clean Up
//	pp->Release();
//	return 0;
//}
