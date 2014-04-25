#ifndef emotion_h__
#define emotion_h__

#include <stdint.h>
#include "FaceTracker.h"

using namespace std;

const int32_t emotion_type_happy = 0;
const int32_t emotion_type_num = 1;

typedef struct tagLRCoeff {
    double bias;
    vector<double> coeff;
} LRCoeff;

class CEmotion {
public:
    // 创建算法实例
    static CEmotion* Create(int32_t width, int32_t height, int32_t image_type);

    // 析构函数
    virtual ~CEmotion();

    // 设置算法参数
    int32_t SetParam(char* key, char* value);

    // 压入从摄像头获取的原始图像
    int32_t PushImage(int32_t timestamp, uint8_t* data);

    // 计算得分
    double GetScore(int32_t emotion_type);

private:
    // 构造函数
    CEmotion(int32_t width, int32_t height, int32_t image_type);
    CEmotion();

    int LoadResource();
#ifdef __ANDROID__
    int LoadResourceAndroid();
#endif

private:
    int32_t m_image_width;
    int32_t m_image_height;
    int32_t m_image_type;
    vector<double> m_scores;

    shared_ptr<CFaceTracker> m_tracker;
    Mat m_meanshape;
    PCA m_pca;
    LRCoeff m_lr_coeff;
};

#endif // emotion_h__
