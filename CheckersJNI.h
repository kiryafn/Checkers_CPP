#include <jni.h>

#ifndef _Included_CheckersJNI
#define _Included_CheckersJNI
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jintArray JNICALL Java_CheckersJNI_getBoardState
        (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getBoardSize
        (JNIEnv *, jobject);

JNIEXPORT jboolean JNICALL Java_CheckersJNI_movePiece
        (JNIEnv *, jobject, jint, jint, jint, jint);

JNIEXPORT jboolean JNICALL Java_CheckersJNI_getCurrentPlayer
        (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
