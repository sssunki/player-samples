//
// Created by 孙凯一 on 12/5/20.
//

#include "DecoderBase.h"
#include "stddef.h"
#include "../include/libavformat/avformat.h"
#include "../include/libavcodec/avcodec.h"

int DecoderBase::initFFDecoder() {

    avCodecContext = avformat_alloc_context();

    avformat_open_input(avCodecContext, m_Url, NULL, NULL);

    avformat_find_stream_info(avFormatContext, NULL);

    for (int i = 0; i < avFormatContext.nb_streams; i++) {
        if (avFormatContext.streams[i]->codecpar->codec_type == mediaType) {
            streamIndex = i;
        }
    }

    AVCodecParameters *codecParameters = avFormatContext.streams[streamIndex]->codecpar;

    codec = avcodec_find_decoder(codecParameters->codec_id);

    avCodecContext = avcodec_alloc_context3(codec);

    avcodec_open2(avCodecContext, codec, NULL);

    packet = av_packet_alloc();

    frame = av_frame_alloc();
}

