#include <jni.h>

#ifndef _Included_CheckersJNI
#define _Included_CheckersJNI
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jintArray JNICALL Java_CheckersJNI_getBoardState(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getBoardSize(JNIEnv *, jobject);

JNIEXPORT jboolean JNICALL Java_CheckersJNI_movePiece(JNIEnv *, jobject, jint, jint, jint, jint);

JNIEXPORT jint JNICALL Java_CheckersJNI_getBoardValue(JNIEnv *, jobject, jint, jint);

JNIEXPORT jboolean JNICALL Java_CheckersJNI_getCurrentPlayer(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getSelectedCol(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getSelectedRow(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_CheckersJNI_setSelectedCol(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_CheckersJNI_setSelectedRow(JNIEnv *, jobject, jint);

JNIEXPORT jboolean JNICALL Java_CheckersJNI_isCellSelected(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_CheckersJNI_setCellSelected(JNIEnv *, jobject, jboolean);

JNIEXPORT void JNICALL Java_CheckersJNI_setFromRow(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_CheckersJNI_setFromCol(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_CheckersJNI_setToCol(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_CheckersJNI_setToRow(JNIEnv *, jobject, jint);

JNIEXPORT jint JNICALL Java_CheckersJNI_getFromRow(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getFromCol(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getToCol(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_CheckersJNI_getToRow(JNIEnv *, jobject);

JNIEXPORT jboolean JNICALL Java_CheckersJNI_gameFinished(JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
