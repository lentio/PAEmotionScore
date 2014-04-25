#ifndef myconfig_h__
#define myconfig_h__

#include <stdint.h>

// 版本号
static const int32_t EMOTION_MAJOR_VERSION = 1;   // 主版本号
static const int32_t EMOTION_MINOR_VERSION = 0;   // 副版本号
static const int32_t EMOTION_MICRO_VERSION = 0;   // 微版本号

// FaceTracker库配置
static const char* FACE_MODEL_RELATIVE_PATH = "/model/face2.tracker";

// meanshape文件名
static const char* MEANSHAPE_FILE_NAME = "/meanshape.csv";

// PCA文件名
static const char* PCA_FILE_NAME = "/pca.csv";
static const int32_t NUM_OF_COMPONENTS = 20;

// LR系数
static const char* LR_FILE_NAME = "/lr.csv";
static const int32_t NUM_OF_COEFS = 20;

// 特征点个数
static const int32_t NUM_OF_PATCHES = 66;

#endif // myconfig_h__
