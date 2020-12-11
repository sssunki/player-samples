//
// Created by 孙凯一 on 12/5/20.
//

#include "DecoderBase.h"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include "android/log.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

void DecoderBase::start(const char* url) {
    strcpy(m_Url, url);
    startDecodingThread();
}

void DecoderBase::startDecodingThread() {
    decodingThread = new thread(doDecoding, this);
}

void DecoderBase::doDecoding(DecoderBase *decoder) {
    __android_log_print(ANDROID_LOG_ERROR, "sunkaiyi", "start decoding");
    decoder->initFFDecoder();
    decoder->onDecoderReady();
    decoder->decodingLoop();
    decoder->unUnitDecoder();
    decoder->onDecoderDone();
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

void DecoderBase::onDecoderReady() {
    videoWidth = avCodecContext->width;
    videoHeight = avCodecContext->height;

    RGBAFrame = av_frame_alloc();

    int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGBA, videoWidth, videoHeight, 1);

    frameBuffer = (uint8_t *) av_malloc(bufferSize * sizeof(uint8_t));

    av_image_fill_arrays(RGBAFrame->data, RGBAFrame->linesize,
                         frameBuffer, AV_PIX_FMT_RGBA, videoWidth, videoHeight, 1);

    swsContext = sws_getContext(videoWidth, videoHeight, avCodecContext->pix_fmt,
                                  videoWidth, videoHeight, AV_PIX_FMT_RGBA,
                                  SWS_FAST_BILINEAR, NULL, NULL, NULL);
}

void DecoderBase::decodingLoop() {
    while (av_read_frame(avFormatContext, packet) == 0) {
        if (packet->stream_index == streamIndex) {
            if (avcodec_send_packet(avCodecContext, packet) == AVERROR_EOF) {
                return;
            }
            if (avcodec_receive_frame(avCodecContext, frame) == 0) {
                onFrameAvailable();
            }
        }
    }

}

void DecoderBase::unUnitDecoder() {
    // todo : extension
}

void DecoderBase::onDecoderDone() {
    // todo : extension
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

void DecoderBase::decodeOnePacket() {

}

void DecoderBase::onFrameAvailable() {
    sws_scale(swsContext, frame->data, frame->linesize, 0,
              videoHeight, RGBAFrame->data, RGBAFrame->linesize);

    ANativeWindow_setBuffersGeometry(nativeWindow, videoWidth, videoHeight, WINDOW_FORMAT_RGBA_8888);

    ANativeWindow_Buffer nativeWindowBuffer;

    ANativeWindow_lock(nativeWindow, &nativeWindowBuffer, nullptr);

    uint8_t *dstBuffer = static_cast<uint8_t *>(nativeWindowBuffer.bits);

    int srcLineSize = RGBAFrame->linesize[0];
    int dstLineSize = nativeWindowBuffer.stride * 4;

    for (int i = 0;  i < videoHeight; ++ i) {
        memcpy(dstBuffer + i * dstLineSize, frameBuffer + i * srcLineSize, srcLineSize);
    }

    ANativeWindow_unlockAndPost(nativeWindow);

}


