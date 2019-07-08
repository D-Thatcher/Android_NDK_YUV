#include <stdint.h>
#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "native.h"
#include <android/log.h>

#define  LOG_TAG    "someTag"
#define  LOG(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

JNIEXPORT jstring JNICALL Java_com_example_dan_opengltester_Views_MainActivity_getMyString(JNIEnv *env, jobject){
    return env->NewStringUTF("Hello World!");
}



int ConvertYUVtoARGB(int y, int u, int v);

int ConvertYUVtoARGB(int y, int u, int v){
    int r,g,b;

    r = y + (int)1.403f*v;
    g = y - (int)(0.344f*u + 0.714f*v);
    b = y + (int)1.770f*u;

    r = r < 0 ? 0 : (r > 255 ? 255 : r);
    g = g < 0 ? 0 : (g > 255 ? 255 : g);
    b = b < 0 ? 0 : (b > 255 ? 255 : b);

    return 0xff000000 | (r<<16) | (g<<8)| b;

}

JNIEXPORT jfloatArray JNICALL Java_com_example_dan_opengltester_Content_Augment_getVerticies(JNIEnv* je, jobject obj){
    LOG("Retrieving vertex data via native method.");
    jfloatArray myReturn = je->NewFloatArray(128);
    jfloat argb8888Data[128];
    je->SetFloatArrayRegion(myReturn,0,128,argb8888Data);
    return myReturn;
}


JNIEXPORT jintArray JNICALL Java_com_example_dan_opengltester_CameraPreview_decodeYUV420SPGrayscale(JNIEnv *je, jobject obj,jbyteArray myByteArray,jint width,jint height){
{
    const int frameSize = width * height;

    jbyte *nv12Data = je->GetByteArrayElements(myByteArray,0);
    jintArray myReturn = je->NewIntArray(frameSize);
    jint gray_data[frameSize];

    for (int pix = 0; pix < frameSize; pix++)
    {
        int pixVal = (0xff & ((int) nv12Data[pix])) - 16;
        if (pixVal < 0) pixVal = 0;
        if (pixVal > 255) pixVal = 255;
        gray_data[pix] = 0xff000000 | (pixVal << 16) | (pixVal << 8) | pixVal;
    }

    je->SetIntArrayRegion(myReturn,0,frameSize,gray_data);
    je->ReleaseByteArrayElements(myByteArray,nv12Data,0);

}


JNIEXPORT jintArray JNICALL Java_com_example_dan_opengltester_Views_CameraPreview_getMyArray(JNIEnv *je, jobject obj,jbyteArray myByteArray,jint myWidth,jint myHeight){
    int size, offset;

    LOG("Processing camera data via native method");
    size = (myWidth*myHeight);

    jbyte *nv12Data = je->GetByteArrayElements(myByteArray,0);
    jintArray myReturn = je->NewIntArray(size);
    jint argb8888Data[size];

    int y0,y1,y2,y3,u,v;

    int i,j;
    offset = size;
    j=0;
    for (i = 0; i < size; i = i + 2){
        y0 = nv12Data[i] & 0xff;
        y1 = nv12Data[(i+1)] & 0xff;
        y2 = nv12Data[(i+myWidth)] & 0xff;
        y3 = nv12Data[(i+1+myWidth)] & 0xff;

        u = (nv12Data[(offset+j)] & 0xff)-128;
        v = (nv12Data[(offset+j+1)] & 0xff)-128;

        argb8888Data[i] = ConvertYUVtoARGB(y0,u,v);
        argb8888Data[i+1] = ConvertYUVtoARGB(y1,u,v);
        argb8888Data[(myWidth+i)] = ConvertYUVtoARGB(y2,u,v);
        argb8888Data[(myWidth+i+1)] = ConvertYUVtoARGB(y3,u,v);

        if ((i != 0) &&(((i+2) % myWidth)==0)){ i += myWidth;}

        j += 2;

    }

    je->SetIntArrayRegion(myReturn,0,size,argb8888Data);
    je->ReleaseByteArrayElements(myByteArray,nv12Data,0);

    return myReturn;
}







