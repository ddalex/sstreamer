#include <stdlib.h>
#include <stdio.h>

#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>


void init() {
    unsigned libavdevice_version = avdevice_version();
    fprintf(stderr, "libavdevice version %d.%d.%d\n",
        libavdevice_version >> 16, (libavdevice_version >> 8)&0xFF, libavdevice_version & 0xFF);
    fprintf(stderr, "libavdevice configuration %s\n", avdevice_configuration());

    av_log_set_level(AV_LOG_DEBUG);
    avcodec_register_all();
    avdevice_register_all();
}


int alloc_input(AVFormatContext **ic) {
   
    int err=0;
    AVDictionary *format_opts = NULL;
    AVDictionary *opts = NULL;

    AVInputFormat *iformat = av_find_input_format("x11grab");
    if (iformat == NULL || iformat->priv_class == NULL) {
        fprintf(stderr, "Cannot find input format\n");
        return 1;
    }

    *ic = avformat_alloc_context();
    if (!ic) {
        fprintf(stderr, "Cannot alloc context\n");
        return 1;
    }

    av_dict_set(&format_opts, "framerate", "25", 0);
    av_dict_set(&format_opts, "video_size", "640x480", 0);

    err = avformat_open_input(ic, ":0.0", iformat, &format_opts);

    if (err < 0) {
        fprintf(stderr, "Cannot open input\n");
        return -1;
    }

    err = avformat_find_stream_info(*ic, &opts);

    if (err < 0) {
        fprintf(stderr, "Cannot find stream info\n");
        return -2;
    }
    return 0;
}

int close_input(int err, AVFormatContext *ic) {
    switch (err) {
        case -2:
        avformat_close_input(&ic);
        case -1:
        avformat_free_context(ic);
    }
}


static AVCodec *find_codec_or_die(const char *name, enum AVMediaType type)
{
    const AVCodecDescriptor *desc;
    const char *codec_string = encoder ? "encoder" : "decoder";
    AVCodec *codec;

    codec = encoder ?
        avcodec_find_encoder_by_name(name) :
        avcodec_find_decoder_by_name(name);

    if (!codec && (desc = avcodec_descriptor_get_by_name(name))) {
        codec = encoder ? avcodec_find_encoder(desc->id) :
                          avcodec_find_decoder(desc->id);
        if (codec)
            av_log(NULL, AV_LOG_VERBOSE, "Matched %s '%s' for codec '%s'.\n",
                   codec_string, codec->name, desc->name);
    }

    if (!codec) {
        av_log(NULL, AV_LOG_FATAL, "Unknown %s '%s'\n", codec_string, name);
        exit_program(1);
    }
    if (codec->type != type) {
        av_log(NULL, AV_LOG_FATAL, "Invalid %s type '%s'\n", codec_string, name);
        exit_program(1);
    }
    return codec;
}


int main(int argc, char **argv) {
    int retval = 0;
    int err=0;

    AVFormatContext *ic;        // input context
    AVCodecContext *enc_ctx;    // encoding context
    AvCodec *enc;               // encoder
    AVRational frame_rate;

    init();

    if ( (err = alloc_input(&ic)) < 2)
    {
        close_input(err, ic);
        exit(1);
    }

    enc = find_codec("libx264", AVMEDIA_TYPE_VIDEO); 

    printf("ready to process input\n");

    close_input(-255, ic);  // close all levels

    return retval;
}
