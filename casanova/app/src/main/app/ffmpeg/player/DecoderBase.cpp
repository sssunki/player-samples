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

    int result = -1;

    do {
        avFormatContext = avformat_alloc_context();

        if (errorHappened(avformat_open_input(&avFormatContext, m_Url, NULL, NULL))) {
            __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "input open error");
            break;
        }

        if (errorHappened(avformat_find_stream_info(avFormatContext, NULL))) {
            __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "find stream info error");
            break;
        }

        for (int i = 0; i < avFormatContext->nb_streams; i++) {
            if (avFormatContext->streams[i]->codecpar->codec_type == mediaType) {
                streamIndex = i;
                break;
            }
        }
        if (streamIndex == -1) {
            __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "get stream error");
            break;
        }

        AVCodecParameters *codecParameters = avFormatContext->streams[streamIndex]->codecpar;
        codec = avcodec_find_decoder(codecParameters->codec_id);
        if (codec == nullptr) {
            __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "get codec error");
            break;
        }

        avCodecContext = avcodec_alloc_context3(codec);
        if (errorHappened(avcodec_parameters_to_context(avCodecContext, codecParameters))) {
            break;
        }

        if (avcodec_open2(avCodecContext, codec, NULL) < 0) {
            __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "codec open error");
            break;
        }

        packet = av_packet_alloc();
        frame = av_frame_alloc();

        result = 0;

    } while (false);

    return result;
}


void DecoderBase::startDecodingThread() {
    decodingThread = new thread(doDecoding, this);
}

void DecoderBase::start(const char* url) {
    strcpy(m_Url, url);
    startDecodingThread();
}

bool DecoderBase::errorHappened(int resultCode) {
    if (resultCode == 0) {
        return false;
    } else {
        char* error = av_err2str(resultCode);
        __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "open input failed");
        __android_log_print(ANDROID_LOG_ERROR, "reason", "%s", error);
        return true;
    }
}


