#include "pch.h"
#include "emotion.h"
#include "common.h"
#include "myconfig.h"
#include "coefficient.h"
#include <stdlib.h>

CEmotion* CEmotion::Create(int32_t width, int32_t height, int32_t image_type)
{
    CEmotion* p_instance = NULL;

    try {
        p_instance = new CEmotion(width, height, image_type);
    }
    catch (...) {}

    if (p_instance && p_instance->LoadResource()) {
        delete p_instance;
        p_instance = NULL;
    }

    return p_instance;
}

CEmotion::CEmotion(int32_t width, int32_t height, int32_t image_type) :
m_image_width(width),
m_image_height(height),
m_image_type(image_type),
m_scores(emotion_type_num),
m_tracker(NULL)
{
}

CEmotion::~CEmotion()
{
}

int32_t CEmotion::SetParam(char* key, char* value)
{
    return 0;
}

int32_t CEmotion::PushImage(int32_t timestamp, uint8_t* data)
{
    Mat img(m_image_height, m_image_width, CV_8UC3, data);
    // 跟踪
    m_tracker->Track(img);
    // 获取66特征点
    Mat features = m_tracker->GetFeaturePoints();

    // 通过meanshape校准当前特征
    Mat c = procrustes(m_meanshape.clone(), features.clone());
    // c-meanshape
    Mat diff = c.clone() - m_meanshape.clone().reshape(0, NUM_OF_PATCHES * 2);
    // pca
    Mat c_after_pca = m_pca.project(diff.reshape(0, 1));
    // lr
    // FIXME: 目前只考虑了happy状态
    double score = m_lr_coeff.bias;
    for (int i = 0; i < NUM_OF_COMPONENTS; ++i) {
        score += m_lr_coeff.coeff[i] * c_after_pca.at<double>(0, i);
    }

    score /= 10.0;
    double value = (1.0 / (1.0 + exp(-score)));
    value *= 100.0;
    value = pow((value / 10.0), 2);
    m_scores[0] = value / 100.0;

    return 0;
}

double CEmotion::GetScore(int32_t emotion_type)
{
    return m_scores[emotion_type];
}

int CEmotion::LoadResource()
{
    // 加载平均脸
    m_meanshape = Mat(NUM_OF_PATCHES, 2, CV_64F, meanshapeArray);

    // 加载PCA系数
    m_pca.eigenvectors = Mat(NUM_OF_COMPONENTS, NUM_OF_PATCHES * 2, CV_64F, PCA_EIGEN_VECTORS_ARRAY);
    m_pca.eigenvalues = Mat(NUM_OF_COMPONENTS, 1, CV_64F, PCA_EIGEN_VALUES_ARRAY);
    m_pca.mean = Mat(1, NUM_OF_PATCHES * 2, CV_64F, PCA_MEAN_ARRAY);

    // 加载LR系数
    m_lr_coeff.bias = LR_BIAS;
    m_lr_coeff.coeff = vector<double>(LR_COEFF, LR_COEFF + sizeof(LR_COEFF) / sizeof(LR_COEFF[0]));

    // 加载FaceTracker库模型
/*
#ifdef WIN32
    string model_file = GetExecutePath() + FACE_MODEL_RELATIVE_PATH;
    m_tracker.reset(new CFaceTracker(model_file.c_str()));
#elif defined __ANDROID__
    LoadResourceAndroid();
#endif
*/
    
    string model_file = GetExecutePath() + FACE_MODEL_RELATIVE_PATH;
    m_tracker.reset(new CFaceTracker(model_file.c_str()));

    return 0;
}

//#ifdef WIN32
//int CEmotion::LoadResourceWin32()
//{
//    int ret = 0;
//
//    try {
//        // TODO1: 需要添加接口，使得文件路径可配置
//        // TODO2: 提高接口的稳定性
//
//        // 加载Face模型
//        string model_file = GetExecutePath() + FACE_MODEL_RELATIVE_PATH;
//        m_tracker.reset(new CFaceTracker(model_file.c_str()));
//
//        // 加载meanshape
//        auto LoadMeanshape_ = []() {
//            Mat meanshape(NUM_OF_PATCHES, 2, CV_64F);
//            ifstream ifs(GetExecutePath() + MEANSHAPE_FILE_NAME, ios::in);
//            while (ifs.good()) {
//                string readbuf;
//                ifs >> readbuf;
//
//                vector<string> fields;
//                boost::split(fields, readbuf, boost::is_any_of(";"));
//                if (fields.size() == 1) continue;
//
//                double dx = 0.0;
//                double dy = 0.0;
//                for (int i = 0; i < NUM_OF_PATCHES; ++i) {
//                    sscanf(fields[i * 2].c_str(), "%lf", &dx);
//                    sscanf(fields[i * 2 + 1].c_str(), "%lf", &dy);
//                    meanshape.at<double>(i, 0) = dx;
//                    meanshape.at<double>(i, 1) = dy;
//                }
//            }
//            ifs.close();
//            return meanshape;
//        };
//        m_meanshape = LoadMeanshape_();
//
//        // 加载PCA系数
//        auto InitPCA_ = [](PCA& pca) {
//            Mat eigen_vectors = Mat::zeros(NUM_OF_COMPONENTS, NUM_OF_PATCHES * 2, CV_64F);
//            Mat eigen_values = Mat::zeros(NUM_OF_COMPONENTS, 1, CV_64F);
//            Mat mean = Mat::zeros(1, NUM_OF_PATCHES * 2, CV_64F);
//
//            ifstream ifs(GetExecutePath() + PCA_FILE_NAME, ios::in);
//            // 读入eigen_vectors
//            string readbuf;
//            vector<string> fields;
//            for (int j = 0; j < NUM_OF_COMPONENTS; ++j) {
//                ifs >> readbuf;
//                boost::split(fields, readbuf, boost::is_any_of(";"));
//                for (int i = 0; i < NUM_OF_PATCHES * 2; ++i) {
//                    double value = 0.0;
//                    sscanf(fields[i].c_str(), "%lf", &value);
//                    eigen_vectors.at<double>(j, i) = value;
//                }
//            }
//            // 读入eigen_values
//            for (int j = 0; j < NUM_OF_COMPONENTS; ++j) {
//                ifs >> readbuf;
//                double value = 0.0;
//                sscanf(readbuf.c_str(), "%lf", &value);
//                eigen_values.at<double>(j, 0) = value;
//            }
//            // 读入mean
//            {
//                ifs >> readbuf;
//                boost::split(fields, readbuf, boost::is_any_of(";"));
//                for (int i = 0; i < NUM_OF_PATCHES * 2; ++i) {
//                    double value = 0.0;
//                    sscanf(fields[i].c_str(), "%lf", &value);
//                    mean.at<double>(0, i) = value;
//                }
//            }
//            ifs.close();
//
//            pca.eigenvectors = eigen_vectors;
//            pca.eigenvalues = eigen_values;
//            pca.mean = mean;
//        };
//        InitPCA_(m_pca);
//
//        // 加载LR系数
//        auto InitLR_ = [](LRCoeff& lr_coeff)
//        {
//            lr_coeff.bias = 0.0;
//            lr_coeff.coeff.resize(NUM_OF_COEFS);
//
//            ifstream ifs(GetExecutePath() + LR_FILE_NAME, ios::in);
//            if (ifs.good()) {
//                string readbuf;
//                ifs >> readbuf;
//
//                vector<string> fields;
//                boost::split(fields, readbuf, boost::is_any_of(";"));
//
//                for (size_t i = 0; i < NUM_OF_COEFS + 1; ++i) {
//                    double value;
//                    sscanf(fields[i].c_str(), "%lf", &value);
//
//                    if (i == 0) {
//                        lr_coeff.bias = value;
//                    }
//                    else {
//                        lr_coeff.coeff[i - 1] = value;
//                    }
//                }
//            }
//            ifs.close();
//        };
//        InitLR_(m_lr_coeff);
//    }
//    catch (...) {
//        ret = -1;
//    }
//
//    return ret;
//}
//#endif

#ifdef __ANDROID__
int CEmotion::LoadResourceAndroid()
{
    string model_file = string("/mnt/sdcard/emotion/") + FACE_MODEL_RELATIVE_PATH;
    m_tracker.reset(new CFaceTracker(model_file.c_str()));

    return 0;
}
#endif
