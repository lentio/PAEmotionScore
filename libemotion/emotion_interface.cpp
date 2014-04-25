#include "pch.h"
#include "emotion_interface.h"
#include "emotion.h"
#include "myconfig.h"
#include "Log.h"

EMOTION_API int32_t emotion_get_major_version()
{
    return EMOTION_MAJOR_VERSION;
}

EMOTION_API int32_t emotion_get_minor_version()
{
    return EMOTION_MINOR_VERSION;
}

EMOTION_API int32_t emotion_get_micro_version()
{
    return EMOTION_MICRO_VERSION;
}

EMOTION_API int32_t emotion_get_data_score(uint8_t* data, int32_t size, int32_t score_type, int32_t image_type, int32_t image_width, int32_t image_height)
{
    double score = 0.0;
    int ret = 0;

    shared_ptr<CEmotion> p_emotion(CEmotion::Create(image_width, image_height, image_type));
    if (!p_emotion) {
        LogError("初始化失败");
        return -1;
    }

    if (ret = p_emotion->PushImage(0/*时间戳，暂时不用*/, data)) {
        LogError("处理图像失败");
        return -1;
    }

    score = p_emotion->GetScore(emotion_type_happy);
    if (score < 0.0f || isnan(score)) {
        LogError("计算笑容指数失败");
        return -1;
    }

    return (int)(score*10000+0.5);
}

EMOTION_API int32_t emotion_get_file_score(char* file, int32_t score_type)
{
    Mat src = imread(file);
    Mat t,f;
    transpose(src, t);
    flip(t, f, 1);
    
    imwrite("/mnt/sdcard/emotion/rotate.jpg", f);

    int score = emotion_get_data_score(f.data, 0, 0/*happy*/, 0/*RGB*/, 768/*width*/, 1024/*height*/);

    // 暂未实现
    return score;
}
