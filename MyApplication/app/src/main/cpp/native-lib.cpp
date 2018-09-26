#include <jni.h>
#include <string>
#include "Imagus/iFaceRec.h"
#include "ImagusTypes/ImagusTypes.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <cmath>

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_mind_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    //printf("%s\n", ifr_GetLicenceHostID());
    //printf("%s\n", ifr_GetLicenceInfo());
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT
jint JNICALL Java_com_example_mind_myapplication_MainActivity_lameMain(JNIEnv *env,
                                                                       jobjectArray argv) {

//    printf("%s\nifr_GetLicenceHostID: ", ifr_GetVersion());
//    printf("%s\nifr_GetLicenceHostID: ", ifr_GetLicenceHostID());
//    printf("%s\nifr_GetLicenceInfo: ", ifr_GetLicenceInfo());
    //return env->0;
}