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
    // �����㷨ʵ��
    static CEmotion* Create(int32_t width, int32_t height, int32_t image_type);

    // ��������
    virtual ~CEmotion();

    // �����㷨����
    int32_t SetParam(char* key, char* value);

    // ѹ�������ͷ��ȡ��ԭʼͼ��
    int32_t PushImage(int32_t timestamp, uint8_t* data);

    // ����÷�
    double GetScore(int32_t emotion_type);

private:
    // ���캯��
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
