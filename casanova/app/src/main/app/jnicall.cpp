#include "jni.h"
#include "ffmpeg/player/DecoderBase.h"
#include "android/log.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_casanova_player_ni_FFmpegPlayer_getStringFromJNI(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("String from JNI");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_casanova_player_ni_FFmpegPlayer_initPlayer(JNIEnv *env, jobject thiz, jstring jurl) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_casanova_player_ni_FFmpegPlayer_initDecoder(JNIEnv *env, jobject thiz, jstring jurl,
                                                             jobject surface) {
    const char* url = env->GetStringUTFChars(jurl, nullptr);
    auto *decoderBase = new DecoderBase(env, surface);
    decoderBase->start(const_cast<char *>(url));

}