//!@brief   Declares the interface to the iFaceVideo library
//!
//!         Copyright (c) 2013 Imagus. All rights reserved.
//!

#if !defined __IMAGUS_VIDEO_DEFINITIONS__
#define __IMAGUS_VIDEO_DEFINITIONS__

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

	using IFR_VIDEO_SOURCE = struct IFR_VIDEO_SOURCE;  ///< A Video Source Object
	using IFR_VIDEO_SOURCE_HANDLE = IFR_VIDEO_SOURCE *; ///< A HANDLE to an video source object.

	using IFR_VIDEO_DEVICE_DESCRIPTOR = struct IFR_VIDEO_DEVICE_DESCRIPTOR;  ///< A Video Device Descriptor
	using IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE = IFR_VIDEO_DEVICE_DESCRIPTOR *; ///< A Video Device Descriptor HANDLE
	using IFR_VIDEO_DEVICES = struct IFR_VIDEO_DEVICES;                      ///< A Video Devices list object
	using IFR_VIDEO_DEVICES_HANDLE = IFR_VIDEO_DEVICES *;                     ///< A Video Devices list object HANDLE

	using IFR_NVR = struct IFR_NVR; ///< A Video NVR Object
	using IFR_NVR_HANDLE = IFR_NVR *; ///< A HANDLE to an video nvr object.


    using IFR_NETWORK_SERVER = struct IFR_NETWORK_SERVER; ///< A Network Server object
    using IFR_NETWORK_SERVER_HANDLE = IFR_NETWORK_SERVER *; ///<A Network Server Handle


/*!
Enum defining current state of video playback
@ingroup video
*/
	typedef enum IFR_VIDEO_STATE
	{
		IFR_PLAYBACK_STARTING = 1, ///< The video is starting but has not yet started
		IFR_PLAYBACK_PLAYING = 2,  ///< The video has played its first frame, and will continue playing frames until stopped 
		IFR_PLAYBACK_END_REACHED = 3, ///< The video has reached a natural end. 
		IFR_PLAYBACK_STOPPED = 4,     ///< The video has stopped and will not continue until started again
		IFR_PLAYBACK_LICENCING_ERROR = 6 ///< There is a licenceing priblem with video.
	} IFR_VIDEO_STATE;

	using IFR_VIDEO_ANALYSIS_FLAGS = int32_t;
	const IFR_VIDEO_ANALYSIS_FLAGS IFR_VIDEO_ANALYSIS_REQUEST_COLOUR_FRAME = 1 << 0;  ///< Flag to indicate a colour frame is required.
	const IFR_VIDEO_ANALYSIS_FLAGS IFR_VIDEO_ANALYSIS_BLUR_FACES = 1 << 1;			  ///< flag to indicate faces are required to be blured 
	const IFR_VIDEO_ANALYSIS_FLAGS IFR_VIDEO_ANALYSIS_PREDICTION_FACES = 1 << 2;      ///< flag to indicate all predicted frames are to be used in tracks

	using IFR_FRAME_INFO_FLAGS = int32_t;
	const IFR_FRAME_INFO_FLAGS IFR_FRAME_LIVE = 1 << 0;       // indicates that the video being played is considered live
	const IFR_FRAME_INFO_FLAGS IFR_FRAME_TIME_BREAK = 1 << 1; // indicates that the current frame has a different time base and is considered independant from the previous frame.

	typedef enum IFR_PLAYBACK_CTRL
	{
/*		IFR_PAUSE = 0,
		IFR_PLAY_FWD = 1,
		IFR_STEP_FWD = 2,
		IFR_PLAY_BKD = 3,
		IFR_STEP_BKD = 4,*/
		IFR_RESTART = 5, ///< Starts the video agian from scratch @deprecated 
		IFR_ROTATE_CLK_90 = 6	///< rotates the video 90 degress 
	} IFR_PLAYBACK_CTRL;


/*! @cond DONTDOXYCOMMENT 
	// These enums are going to be removed, so are not documented 
*/
	using IFR_VIDEOSAVE_STATE = int32_t;
	const IFR_VIDEOSAVE_STATE IFR_VIDEOSAVE_STARTED_NEW_FILE = 0; 
	const IFR_VIDEOSAVE_STATE IFR_VIDEOSAVE_CLOSED_FILE = 1;      


	typedef enum IFR_COUNTER
	{
		IFR_COUNTER_COMPRESSEDFRAMES = 1,
		IFR_COUNTER_DECOMPRESSEDFRAMES = 2,
		IFR_COUNTER_DROP_RATE = 3,
		IFR_COUNTER_INFLIGHT_FRAMES = 4,
		IFR_COUNTER_INFLIGHT_MODELS = 5,
		IFR_COUNTER_FWD_PLAY_BUFFER_SIZE = 6,
		IFR_COUNTER_BKD_PLAY_BUFFER_SIZE = 7,
		IFR_COUNTER_PLAY_SPEED = 8,
		IFR_COUNTER_DETECT_XMIN = 9,
		IFR_COUNTER_DETECT_XMAX = 10,
		IFR_COUNTER_DETECT_YMIN = 11,
		IFR_COUNTER_DETECT_YMAX = 12,
		IFR_COUNTER_FRAME_WIDTH = 13,
		IFR_COUNTER_FRAME_HEIGHT = 14,
		IFR_COUNTER_BEST_FACE_MAX_AGE = 15,
		IFR_COUNTER_NUM_BEST_FACES = 16,
		IFR_COUNTER_DECAY_RATE = 17,
		IFR_COUNTER_MIN_QUALITY = 18
	} IFR_COUNTER;

	/*! @endcond */
#ifdef __cplusplus
} //extern "C"
#endif

#endif //__IMAGUS_FACE_DEFINITIONS__
