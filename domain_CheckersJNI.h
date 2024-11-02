#include <jni.h>

#ifndef _Included_CheckersJNI
#define _Included_CheckersJNI
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jintArray JNICALL Java_domain_CheckersJNI_getBoardState(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getBoardSize(JNIEnv *, jobject);

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_movePiece(JNIEnv *, jobject, jint, jint, jint, jint);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getBoardValue(JNIEnv *, jobject, jint, jint);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setBoardValue(JNIEnv *, jobject, jint, jint, jint);

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_getCurrentPlayer(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setCurrentPlayer(JNIEnv *env, jobject obj, jboolean a);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getSelectedCol(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getSelectedRow(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setSelectedCol(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setSelectedRow(JNIEnv *, jobject, jint);

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_isCellSelected(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setCellSelected(JNIEnv *, jobject, jboolean);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setFromRow(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setFromCol(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setToCol(JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setToRow(JNIEnv *, jobject, jint);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getFromRow(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getFromCol(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getToCol(JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getToRow(JNIEnv *, jobject);

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_gameFinished(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_domain_CheckersJNI_resetGame(JNIEnv *, jobject);


#ifdef __cplusplus
}
#endif
#endif
