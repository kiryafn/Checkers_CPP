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

JNIEXPORT jboolean JNICALL Java_CheckersJNI_gameFinished
        (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getBoardValue
        (JNIEnv *, jobject, jint, jint);

JNIEXPORT jint JNICALL Java_CheckersJNI_getSelectedCol
        (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getSelectedRow
        (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_CheckersJNI_setSelectedCol
        (JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_CheckersJNI_setSelectedRow
        (JNIEnv *, jobject, jint);

JNIEXPORT jboolean JNICALL Java_CheckersJNI_isPieceSelected
        (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_CheckersJNI_setPieceSelected
        (JNIEnv *, jobject, jboolean);

#ifdef __cplusplus
}
#endif
#endif
