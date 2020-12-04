#include "jni.h"
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_casanova_player_native_JNIT_getStringFromJNI(
    JNIEnv* env, jobject thiz) {
    return env->NewStringUTF("String from JNI");
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_casanova_player_ni_JNIT_getStringFromJNI(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("String from JNI");
}