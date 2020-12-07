//
// Created by 孙凯一 on 12/5/20.
//

#include "Decoder.h"
#include "../ffmpeg/include/libavformat/avformat.h"
#include "../ffmpeg/include/libavcodec/avcodec.h"
#include "../ffmpeg/include/libavutil/avutil.h"
#include "../ffmpeg/include/libavutil/frame.h"
#define MAX_PATH 2048

#ifndef CASANOVA_DECODER_H
#define CASANOVA_DECODER_H

#endif //CASANOVA_DECODER_H

class DecoderBase : public Decoder {
public:

private:
    int initFFDecoder();

    AVFormatContext avFormatContext = nullptr;
    AVCodecContext avCodecContext = nullptr;
    AVCodec codec = nullptr;
    AVPacket packet = nullptr;
    AVFrame frame = nullptr;
    AVMediaType mediaType = AVMEDIA_TYPE_UNKNOWN;
    int streamIndex = -1;

    char  m_Url[MAX_PATH] = {0};


};

