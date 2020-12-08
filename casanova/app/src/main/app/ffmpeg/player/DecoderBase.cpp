//
// Created by 孙凯一 on 12/5/20.
//

#include "DecoderBase.h"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include "android/log.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
}

void DecoderBase::doDecoding(DecoderBase *decoder) {
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "start decoding");
    decoder->initFFDecoder();
    decoder->onDecoderReady();
    decoder->decodingLoop();
    decoder->unUnitDecoder();
    decoder->onDecoderDone();
}

void DecoderBase::onDecoderReady() {
}

void DecoderBase::decodingLoop() {
}

void DecoderBase::unUnitDecoder() {
}

void DecoderBase::onDecoderDone() {
}

int DecoderBase::initFFDecoder() {

    avFormatContext = avformat_alloc_context();
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "1");

    int result = avformat_open_input(&avFormatContext, m_Url, NULL, NULL);

    if (result != 0) {
        __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "open input failed");
        __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "%s",m_Url);
        char* error = av_err2str(result);
        __android_log_print(ANDROID_LOG_ERROR, "reason", "%s", error);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "open input success");
    }


    // todo: fix this crash
    avformat_find_stream_info(avFormatContext, NULL);
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "3");

    for (int i = 0; i < avFormatContext->nb_streams; i++) {
        if (avFormatContext->streams[i]->codecpar->codec_type == mediaType) {
            streamIndex = i;
        }
    }
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "4");

    AVCodecParameters *codecParameters = avFormatContext->streams[streamIndex]->codecpar;
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "5");

    codec = avcodec_find_decoder(codecParameters->codec_id);
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "6");

    avCodecContext = avcodec_alloc_context3(codec);
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "7");

    avcodec_open2(avCodecContext, codec, NULL);
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "8");

    packet = av_packet_alloc();
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "9");

    frame = av_frame_alloc();
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "10");

    return 0;
}

void DecoderBase::startDecodingThread() {
    decodingThread = new thread(doDecoding, this);
}

void DecoderBase::start(const char* url) {
    strcpy(m_Url, url);
    startDecodingThread();
}

