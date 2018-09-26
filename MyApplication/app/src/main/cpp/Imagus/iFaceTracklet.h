//!
//! @file    iFaceRec.h
//!
//! @brief   Declares the iFaceRec interface.
//!
//!         Copyright (c) 2013 Imagus. All rights reserved.
//!


#if !defined __IMAGUS_TRACKLET_HEADER__
#define __IMAGUS_TRACKLET_HEADER__





#include "iFaceRecExports.h"
#include "iFaceRecDefs.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
@deprecated use the #IFR_FACETRACKER_HANDLE to create a tracker then feed it with info to create tracks
Creates an empty tracklet handle associated with a specific location
@param id a new track id to use 
@param location a new locarion id to use
@rethandle{IFR_TRACKLET_HANDLE}
*/
DEPRECATED_IFACEAPI IFR_TRACKLET_HANDLE ifr_CreateTracklet(IFR_UUID id, IFR_UUID location);

/**
Serialises a #IFR_TRACKLET_HANDLE
Returns an IFR_BUFFER_HANDLE (which needs to be freed with #ifr_Free)
Use buffer functions to get length, data pointer for writing to disk etc.
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@rethandle{IFR_BUFFER_HANDLE}
@ingroup tracks
*/
IFACEAPI IFR_BUFFER_HANDLE ifr_SerialiseTracklet(IFR_TRACKLET_HANDLE trackletHandle);

/**
Deserialises a tracklet serialsied by the function #ifr_SerialiseTracklet
@handleparam{IFR_BUFFER_HANDLE,bufferHandle}
@rethandle{IFR_TRACKLET_HANDLE}
@ingroup tracks
*/
IFACEAPI IFR_TRACKLET_HANDLE ifr_DeserialiseTracklet(IFR_BUFFER_HANDLE bufferHandle);

/**
Gets the device ID of the device that created the frames that the track came from 
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@return the device #IFR_UUID
@ingroup tracks
*/
IFACEAPI IFR_UUID ifr_TrackletGetDeviceID(IFR_TRACKLET_HANDLE trackletHandle);
/**
Gets the track UUID 
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@return the track #IFR_UUID
@ingroup tracks
*/
IFACEAPI IFR_UUID ifr_TrackletGetTrackUUID(IFR_TRACKLET_HANDLE trackletHandle);
/**
Gets the tracklet UUID 
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@return the tracklet #IFR_UUID
@ingroup tracks
*/
IFACEAPI IFR_UUID ifr_TrackletGetTrackletUUID(IFR_TRACKLET_HANDLE trackletHandle);


/** 
@getcount{IFR_ALGORITHM,IFR_TRACKLET_HANDLE,trackletHandle}
@sa #ifr_TrackletGetRequestedModel
@ingroup tracks
*/
IFACEAPI size_t        ifr_TrackletGetNumberOfRequestedModels(IFR_TRACKLET_HANDLE trackletHandle);
/**
@getitem{IFR_ALGORITHM,IFR_TRACKLET_HANDLE,trackletHandle}
@sa #ifr_TrackletGetNumberOfRequestedModels
@ingroup tracks
*/
IFACEAPI IFR_ALGORITHM ifr_TrackletGetRequestedModel(IFR_TRACKLET_HANDLE trackletHandle, int index);

/** Adds a model request to a track. This is usefull if you want the track to always generate a model beforee serialisation, so that the model is included
funtionally this makes no difference, but performance wise, it can mean the models are generated before serialisation,and included if requested.
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@param model model to add
@ingroup tracks
*/
IFACEAPI void          ifr_TrackletAddRequestedModel(IFR_TRACKLET_HANDLE trackletHandle, IFR_ALGORITHM model);



IFACEAPI IFR_FACE_HANDLE ifr_TrackletGetFace(IFR_TRACKLET_HANDLE trackletHandle, IFR_TIME timestamp);
/** 
@deprecated this is unlikely to be useful, use the #IFR_FACETRACKER_HANDLE, and push the whole image and results in 
Adds a face to a tracklet at a specified location
If this function is used the faces should be added in order of time, and the times should be correctly set in the image

@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@handleparam{IFR_FACE_HANDLE,face}
@ifr_return
@param eyes the eye location in the image that the tracklet should be associated with 
*/
DEPRECATED_IFACEAPI IFR_RETURN ifr_TrackletAddFace(IFR_TRACKLET_HANDLE trackletHandle, IFR_FACE_HANDLE face, IFR_EYES eyes);

/** 
@getitem{IFR_TRACK_HISTORY_RECORD,IFR_TRACKLET_HANDLE,trackletHandle}
@sa #ifr_TrackletGetHistoryCount
@ingroup tracks
*/
IFACEAPI const IFR_TRACK_HISTORY_RECORD * ifr_TrackletGetHistory(IFR_TRACKLET_HANDLE trackletHandle, size_t index);
/** 
@getcount{IFR_TRACK_HISTORY_RECORD,IFR_TRACKLET_HANDLE,trackletHandle}
@sa #ifr_TrackletGetHistory
@ingroup tracks
*/
IFACEAPI size_t ifr_TrackletGetHistoryCount(IFR_TRACKLET_HANDLE trackletHandle);

/** Gets the Facelist associated witht the tracklet 
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@rethandle{IFR_FACELIST_HANDLE}
@ingroup tracks
*/
IFACEAPI IFR_FACELIST_HANDLE ifr_TrackletGetFaceList(IFR_TRACKLET_HANDLE trackletHandle);

/** Gets the Start Time of the tracklet
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@return #IFR_TIME 
@ingroup tracks
*/
IFACEAPI IFR_TIME ifr_TrackletGetStartTime(IFR_TRACKLET_HANDLE trackletHandle);

/** Gets the End Time of the tracklet
@handleparam{IFR_TRACKLET_HANDLE,trackletHandle}
@return #IFR_TIME 
@ingroup tracks
*/
IFACEAPI IFR_TIME ifr_TrackletGetEndTime(IFR_TRACKLET_HANDLE trackletHandle);






#ifdef __cplusplus
} // extern "C"
#endif



#endif // __IMAGUS_TRACKLET_HEADER__