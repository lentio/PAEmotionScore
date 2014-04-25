#ifndef myconfig_h__
#define myconfig_h__

#include <stdint.h>

// �汾��
static const int32_t EMOTION_MAJOR_VERSION = 1;   // ���汾��
static const int32_t EMOTION_MINOR_VERSION = 0;   // ���汾��
static const int32_t EMOTION_MICRO_VERSION = 0;   // ΢�汾��

// FaceTracker������
static const char* FACE_MODEL_RELATIVE_PATH = "/model/face2.tracker";

// meanshape�ļ���
static const char* MEANSHAPE_FILE_NAME = "/meanshape.csv";

// PCA�ļ���
static const char* PCA_FILE_NAME = "/pca.csv";
static const int32_t NUM_OF_COMPONENTS = 20;

// LRϵ��
static const char* LR_FILE_NAME = "/lr.csv";
static const int32_t NUM_OF_COEFS = 20;

// ���������
static const int32_t NUM_OF_PATCHES = 66;

#endif // myconfig_h__
