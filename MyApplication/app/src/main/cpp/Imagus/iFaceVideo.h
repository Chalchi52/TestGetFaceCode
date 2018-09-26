//!
//!@file    iFaceRec.h
//!
//!@brief   Declares the iFaceRec interface.
//!
//!         Copyright (c) 2013 Imagus. All rights reserved.
//!

#if !defined __IMAGUS_VIDEO_SOURCE_ENGINE_API__
#define __IMAGUS_VIDEO_SOURCE_ENGINE_API__


#include "iFaceVideoExports.h"
#include "iFaceVideoDefs.h"
#include "iFaceRecDefs.h"

#ifdef __cplusplus
#if !defined PINVOKEGEN
    #define DEFAULTPARAM = 0
#else
    #define DEFAULTPARAM
#endif
#include <iostream>
extern "C" {
#else
    #define DEFAULTPARAM
#endif



using IFR_VideoPlaybackStateCallback = void (*)(IFR_VIDEO_STATE, void *); ///< Callback for when video playback state has changed @ingroup video
using IFR_VideoSaveStateCallback = void (*)(IFR_VIDEOSAVE_STATE, const char *, void *); ///< callback for when video save state has changed @deprecated  @ingroup video
using IFR_VideoFrameCallback = void (*)(IFR_FRAME_INFO_FLAGS, IFR_IMAGE_HANDLE, IFR_IMAGE_HANDLE, IFR_IMAGE_HANDLE, IFR_DETECTOR_RESULT_HANDLE, IFR_RESULTIDS_HANDLE, void *); //< callback fro each video frame processed @ingroup video
using IFR_VideoFrameDetectionsCallback = void (*)(IFR_FRAME_INFO_FLAGS, IFR_TIME, IFR_DETECTOR_RESULT_HANDLE, IFR_RESULTIDS_HANDLE, void *); //< callback for each video Track detection per frame processed @ingroup video
using IFR_DeviceDiscoveryCallback = void (*)(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE, void *); ///< Callback for device discovery  @ingroup video


/**
Duplicates a handle, such that two handles now exist pointing to the same object. @note
that both still need to be freed using ifr_Free.

@param  h   The pointer to the handle to duplicate.

@return null if it fails, else a new handle.
@ingroup handles
*/
IFACEVIDEOAPI IFR_VIDEO_DEVICES_HANDLE           ifr_DuplicateVideoDevicesHandle(const IFR_VIDEO_DEVICES_HANDLE h);
/**
Duplicates a handle, such that two handles now exist pointing to the same object. @note
that both still need to be freed using ifr_Free.

@param  h   The pointer to the handle to duplicate.

@return null if it fails, else a new handle.
@ingroup handles
*/
IFACEVIDEOAPI IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE ifr_DuplicateDeviceDescriptorHandle(const IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE h);
/**
Duplicates a handle, such that two handles now exist pointing to the same object. @note
that both still need to be freed using ifr_Free.

@param  h   The pointer to the handle to duplicate.

@return null if it fails, else a new handle.
@ingroup handles
*/
IFACEVIDEOAPI IFR_VIDEO_SOURCE_HANDLE            ifr_DuplicateVideoSourceHandle(const IFR_VIDEO_SOURCE_HANDLE h);


//IFACEVIDEOAPI IFR_RETURN ifr_CreateVideoSource(IFR_VIDEO_SOURCE_HANDLE *videoSourceHandle, const char * source, const char * identifier,  IFR_VideoPlaybackStateCallback callback DEFAULTPARAM, void * user DEFAULTPARAM);


/**
Sets a callback into a video source which gets called everytime a video frame has been processed
@handleparam{IFR_VIDEO_SOURCE_HANDLE, videoSourceHandle}
@callbackparam{IFR_VideoFrameCallback,callback}
@callbackhandleparam
@ifr_return
@ingroup video
*/
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoFrameCallback(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_VideoFrameCallback callback, IFR_CALLBACK_HANDLE cbHandle);

/**
Sets a callback into a video source which gets called everytime a video frame detection has been processed ( this is the same as #ifr_SetVideoFrameCallback but no frame images are returned, also, there is no guarantee that the callback is made on every frame, if nothinig has changed between frames.) 
@handleparam{IFR_VIDEO_SOURCE_HANDLE, videoSourceHandle}
@callbackparam{IFR_VideoFrameDetectionsCallback,callback}
@callbackhandleparam
@ifr_return
@ingroup video
*/
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoFrameDetectionsCallback(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_VideoFrameDetectionsCallback callback, IFR_CALLBACK_HANDLE cbHandle);


/**
Sets a callback into a video source which gets called everytime th internal tracker update changed
@handleparam{IFR_VIDEO_SOURCE_HANDLE, videoSourceHandle}
@callbackparam{IFR_TrackerCallbackRoutine,callback}
@callbackhandleparam
@ifr_return
@ingroup video
*/
IFACEVIDEOAPI IFR_RETURN ifr_SetTrackerCallback(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_TrackerCallbackRoutine callback, IFR_CALLBACK_HANDLE cbHandle);



/** Sets the recording location for the video
@deprecated currently does not work. This will be replaced in a future version

@ingroup video
*/
DEPRECATED_IFACEVIDEOAPI IFR_RETURN ifr_SetVideoOutputFileLocation(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, const char * folder, IFR_VideoSaveStateCallback callback, void * user);


/** starts a video 
@handleparam{IFR_VIDEO_SOURCE_HANDLE, videoSourceHandle}
@ifr_return
@ingroup video
*/
IFACEVIDEOAPI IFR_RETURN ifr_StartVideo(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle);
/** starts a video with a time offset and duration
For use on video files or replay, will set the start time, and the video will act as if that is the entire length of the video.
This is set until the next call to #ifr_StartVideoWithOffset or #ifr_StartVideo
@handleparam{IFR_VIDEO_SOURCE_HANDLE, videoSourceHandle}
@param offset Either an absolute time, or an offset from the begining of a file
@param duration The length of time in milliseconds to play for
@ifr_return
@ingroup video
*/
IFACEVIDEOAPI IFR_RETURN ifr_StartVideoWithOffset(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_TIME offset, IFR_TIME duration);
/** stops a video 
@handleparam{IFR_VIDEO_SOURCE_HANDLE, videoSourceHandle}
@ifr_return
@ingroup video
*/

IFACEVIDEOAPI IFR_RETURN ifr_StopVideo(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle);
/** sends a command to the video 
@handleparam{IFR_VIDEO_SOURCE_HANDLE, videoSourceHandle}
@param ctrl The video command to send see #IFR_PLAYBACK_CTRL
@param data The data to go with the command  
@ifr_return
@ingroup video
*/

IFACEVIDEOAPI IFR_RETURN ifr_CtrlVideo(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_PLAYBACK_CTRL ctrl, int data);

/** Sets the frame dropping rate of the video analytics
	  The frames will be dropped from the face detection with the following rates
	 
     droprate      | meaning
     --------------|-----------------------------
       0 or 1      |  do not drop anything.
	   -1          |  drop dynamically when required for the frames to stay low latency
	   > 1         |  keep every xth frame   
	   < 1         |  drop every (-x)th frame eg, -2 and 2 do the same thing, drop every other frame
	   3           |  drop 2 out of three frames
	   -3          |  drop 1 out of three frames
	   4           |  drop 3 out of four frames
	   -4          |  drop 1 out of four frames


@handleparam{IFR_VIDEO_SOURCE_HANDLE, vsh}
@param droprate The droprate 
@ifr_return
@ingroup video
*/
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoDropRate(IFR_VIDEO_SOURCE_HANDLE vsh, int droprate);
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoEnableRestart(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, int enable);
//IFACEVIDEOAPI int ifr_GetVideoEnableRestart(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle);


/* need to rethink the detector settings  implementations.... probably a json configuration profile for the analytics*/
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoMinFaceQuality(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, float minFaceQuality);
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoMinFaceBlurriness(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, float minFaceBlurriness);
IFACEVIDEOAPI IFR_RETURN ifr_VideoSourceSetFaceSizeWindow(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, int xmin, int ymin, int xmax, int ymax);
IFACEVIDEOAPI IFR_RETURN ifr_VideoSetDetectorFlags(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_DETECTION_FLAGS flags);


IFACEVIDEOAPI IFR_RETURN ifr_VideoSetAnalysisFlags(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_VIDEO_ANALYSIS_FLAGS flags);
IFACEVIDEOAPI IFR_VIDEO_ANALYSIS_FLAGS ifr_VideoGetAnalysisFlags(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle);



IFACEVIDEOAPI IFR_RETURN ifr_VideoSourceSetFilter(IFR_VIDEO_SOURCE_HANDLE vsh, const char *);
IFACEVIDEOAPI const char * ifr_VideoSourceGetFilter(IFR_VIDEO_SOURCE_HANDLE vsh);



//IFACEVIDEOAPI IFR_UUID ifr_VideoSourceGetLocation(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle);

//IFACEVIDEOAPI IFR_RETURN ifr_VideoSourceSetRecordDirectory(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, const char * dir);


IFACEVIDEOAPI IFR_RETURN ifr_SetVideoTrackerNumBestFaces(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, int numFaces);
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoTrackerBestFaceMaxAge(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, int numFrames);
IFACEVIDEOAPI IFR_RETURN ifr_SetVideoTrackerDecayRate(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, int numFrames);

IFACEVIDEOAPI IFR_RETURN ifr_SetVideoAspectCorrection(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, float aspectCorrection);
IFACEVIDEOAPI float ifr_GetVideoAspectCorrection(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle);




IFACEVIDEOAPI int32_t ifr_VideoGetCounter(IFR_VIDEO_SOURCE_HANDLE vsh, IFR_COUNTER counter);






IFACEVIDEOAPI IFR_VIDEO_DEVICES_HANDLE ifr_GetVideoDevicesEnumerator(IFR_NVR_HANDLE nvrHandle);


IFACEVIDEOAPI size_t ifr_GetVideoDevicesCount(IFR_VIDEO_DEVICES_HANDLE videoDevices);
IFACEVIDEOAPI IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE ifr_GetVideoDevice(IFR_VIDEO_DEVICES_HANDLE videoDevices, size_t index);


IFACEVIDEOAPI IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE   ifr_CreateVideoDevice(const char * sourcename, const char * inputDevice, const char * friendlyname,IFR_TIME timestamp);


IFACEVIDEOAPI const char * ifr_GetVideoDeviceFriendlyName(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE videoDevice);
IFACEVIDEOAPI const char * ifr_GetVideoDeviceInputDevice(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE videoDevice);
IFACEVIDEOAPI const char * ifr_GetVideoDevicePath(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE videoDevice);
IFACEVIDEOAPI IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE ifr_GetVideoDeviceFromSource(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle);
IFACEVIDEOAPI const char * ifr_GetVideoDeviceConfig(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE videoDevice);
IFACEVIDEOAPI IFR_UUID ifr_GetVideoDeviceId(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE videoDevice);


//IFACEVIDEOAPI IFR_RETURN ifr_SetVideoDeviceCredentials(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE videoDevice, const char * username, const char * password);





IFACEVIDEOAPI IFR_RETURN ifr_SetVideoSourcePlaybackStateCallback(IFR_VIDEO_SOURCE_HANDLE videoSourceHandle, IFR_VideoPlaybackStateCallback callback, IFR_CALLBACK_HANDLE cbHandle);
IFACEVIDEOAPI IFR_VIDEO_SOURCE_HANDLE ifr_CreateVideoSourceFromDevice(IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE device);




// creates a vendor handle for an NVR (e.g vendor = "milestone")
IFACEVIDEOAPI IFR_NVR_HANDLE ifr_NVRInitialise(const char * vendor, IFR_DeviceDiscoveryCallback callback, IFR_CALLBACK_HANDLE cbHandle);


// Create a device from a JSON config string
IFACEVIDEOAPI IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE ifr_NVRCreateDevice(IFR_NVR_HANDLE nvrHandle, const char *config);
// Create a device from a GUID
IFACEVIDEOAPI IFR_VIDEO_DEVICE_DESCRIPTOR_HANDLE ifr_NVRCreateDeviceFromID(IFR_NVR_HANDLE nvrHandle, IFR_UUID id);
IFACEVIDEOAPI const char *ifr_NVRGetConfig(IFR_NVR_HANDLE nvrHandle);
IFACEVIDEOAPI IFR_RETURN ifr_NVRSetConfig(IFR_NVR_HANDLE nvrHandle, const char * config);

IFACEVIDEOAPI IFR_RETURN ifr_NVRDiscoverDevices(IFR_NVR_HANDLE nvrHandle);


IFACEVIDEOAPI IFR_NETWORK_SERVER_HANDLE ifr_StartNetworkServer(const char * addr, uint16_t port);



#ifdef __cplusplus
} // extern "C"
#endif //__cplusplus
#endif // __IMAGUS_VIDEO_SOURCE_ENGINE_API__
