
#include <jni.h>

#ifndef OPENGLTESTER_NATIVE_H
#define OPENGLTESTER_NATIVE_H

extern "C" {


//void Resize_and_decodyuv(unsigned char * data,int _width,int _height, unsigned char *out, int newWidth, int newHeight);

JNIEXPORT jstring JNICALL Java_com_example_dan_opengltester_Views_MainActivity_getMyString(JNIEnv *, jobject);


//JNIEXPORT jbyteArray JNICALL Java_com_example_dan_relativewheel_CameraPreview_getMyArray(JNIEnv* jenv, jobject obj,jbyteArray array,jint length,jint x,jint y);
JNIEXPORT jintArray JNICALL Java_com_example_dan_opengltester_Views_CameraPreview_getMyArray(JNIEnv* je, jobject obj,jbyteArray myByteArray,jint myWidth,jint myHeight);

JNIEXPORT jfloatArray JNICALL Java_com_example_dan_opengltester_Content_Augment_getVerticies(JNIEnv* je, jobject obj);
};
#endif
