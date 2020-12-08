//
// Created by 孙凯一 on 12/5/20.
//

extern "C" {
#include "../include/libavformat/avformat.h"
#include "../include/libavcodec/avcodec.h"
#include "../include/libavutil/avutil.h"
#include "../include/libavutil/frame.h"
}

#include "Decoder.h"
#include <thread>
#define MAX_PATH 2048

#ifndef CASANOVA_DECODER_H
#define CASANOVA_DECODER_H

#endif //CASANOVA_DECODER_H

using namespace std;

class DecoderBase : public Decoder {
public:
    DecoderBase(){};
     void start(const char* url) ;

private:

    int initFFDecoder();
    void startDecodingThread();
    static void doDecoding(DecoderBase *decoder);
    void onDecoderReady();
    void decodingLoop();
    void unUnitDecoder();
    void onDecoderDone();

    thread *decodingThread = nullptr;
    AVFormatContext *avFormatContext = nullptr;
    AVCodecContext *avCodecContext = nullptr;
    AVCodec *codec = nullptr;
    AVPacket *packet = nullptr;
    AVFrame *frame = nullptr;
    AVMediaType mediaType = AVMEDIA_TYPE_UNKNOWN;
    int streamIndex = -1;

    char  m_Url[MAX_PATH] = {0};


};

