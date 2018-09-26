//!
//!@file    iFaceRecExports.h
//!
//!@brief   Declares the iFaceRecExports interface.
//!
//!         Copyright (c) 2013 Imagus. All rights reserved.
//!



#pragma once
#if !defined __IFACEVIDEOAPI_EXPORTS_H__ 
#define __IFACEVIDEOAPI_EXPORTS_H__ 

    #if defined (_MSC_VER)
        #if defined(ImagusVideo_EXPORTS) || defined(iFaceVideo_EXPORTS)
            #define  IFACEVIDEOAPI  __declspec(dllexport) 
            #define  DEPRECATED_IFACEVIDEOAPI  __declspec(dllexport,deprecated) 
        #else
            #define  IFACEVIDEOAPI  __declspec(dllimport) 
            #define  DEPRECATED_IFACEVIDEOAPI  __declspec(dllimport,deprecated) 
        #endif // iFaceRec_EXPORTS
    #else // defined (_MSC_VER)
        #if defined(ImagusVideo_EXPORTS) || defined(iFaceVideo_EXPORTS)
            #define IFACEVIDEOAPI __attribute__((visibility("default")))
        #else
            #define IFACEVIDEOAPI
        #endif
    
        #ifdef __GNUC__ 
            #define DEPRECATED_IFACEVIDEOAPI __attribute__ ((deprecated)) 
        #else 
            #define DEPRECATED_IFACEVIDEOAPI 
            #pragma message("DEPRECATED is not defined for this compiler") 
        #endif 
    #endif

#endif //__IFACEVIDEOAPI_EXPORTS_H__ 
