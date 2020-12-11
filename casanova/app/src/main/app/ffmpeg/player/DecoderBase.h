//
// Created by 孙凯一 on 12/5/20.
//

extern "C" {
#include "../include/libavformat/avformat.h"
#include "../include/libavcodec/avcodec.h"
#include "../include/libavutil/avutil.h"
#include "../include/libavutil/frame.h"
#include "../include/libswscale/swscale.h"
#include "../render/NativeRender.h"
}

#include "Decoder.h"
#include <thread>
#include <android/native_window.h>
#include <jni.h>
#include <android/native_window_jni.h>

#define MAX_PATH 2048

#ifndef CASANOVA_DECODER_H
#define CASANOVA_DECODER_H

#endif //CASANOVA_DECODER_H

using namespace std;

class DecoderBase : public Decoder {
public:
    DecoderBase(JNIEnv *env, jobject surface) {
        nativeWindow = ANativeWindow_fromSurface(env, surface);
    };
     void start(const char* url) ;

private:

    int initFFDecoder();
    void startDecodingThread();
    static void doDecoding(DecoderBase *decoder);
    void onDecoderReady();
    void decodingLoop();
    void unUnitDecoder();
    void onDecoderDone();
    void decodeOnePacket();
    void onFrameAvailable();
    bool errorHappened(int resultCode);

    thread *decodingThread = nullptr;
    AVFormatContext *avFormatContext = nullptr;
    AVCodecContext *avCodecContext = nullptr;
    AVCodec *codec = nullptr;
    AVPacket *packet = nullptr;
    AVFrame *frame = nullptr;
    AVMediaType mediaType = AVMEDIA_TYPE_VIDEO;
    ANativeWindow *nativeWindow = nullptr;
    int streamIndex = -1;
    char  m_Url[MAX_PATH] = {0};

    int videoWidth = 0;
    int videoHeight = 0;
    AVFrame *RGBAFrame = nullptr;
    SwsContext *swsContext = nullptr;
    uint8_t *frameBuffer = nullptr;
    NativeRender *nativeRender = nullptr;

};

