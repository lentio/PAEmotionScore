//#include "pch.h"
#include "FaceTracker.h"

CFaceTracker::CFaceTracker(const char* model_file) :
m_tracker(),
m_is_fail(false),
m_gray(),
m_wSize_succ(1),
m_wSize_fail(3),
m_number_of_iteration(0),
m_clamp(0),
m_tol(0),
m_idx(0)
{
    // 加载模型
    m_tracker.Load(model_file);

    m_gray = Mat::zeros(480, 640, CV_8UC1);

    m_wSize_succ[0] = 7;
    m_wSize_fail[0] = 11;
    m_wSize_fail[1] = 9;
    m_wSize_fail[2] = 7;

    m_number_of_iteration = 5;
    m_clamp = 3;
    m_tol = 0.01;
}

CFaceTracker::~CFaceTracker(void)
{
}

void CFaceTracker::Reset()
{
    m_tracker.FrameReset();
    m_is_fail = false;
}

int CFaceTracker::Track(const Mat& image)
{
    vector<int> wSize;
    wSize = m_is_fail ? m_wSize_fail : m_wSize_succ;

    cvtColor(image, m_gray, CV_BGR2GRAY);

    if (!m_tracker.Track(m_gray, wSize, -1/*未知*/, m_number_of_iteration, m_clamp, m_tol, false/*未知*/)) {
        m_idx = m_tracker._clm.GetViewIdx();
        m_is_fail = false;
        return 0;
    }
    else {
        Reset();
        return -1;
    }
}

// 输出: 返回66x2矩阵
Mat CFaceTracker::GetFeaturePoints()
{
    const Mat shape = m_tracker._shape;
    const int half_shape_rows = shape.rows / 2;

    Mat points = Mat::zeros(66, 2, CV_64F);

    for (int i = 0; i < half_shape_rows; ++i) {
        points.at<double>(i, 0) = shape.at<double>(i, 0);
        points.at<double>(i, 1) = shape.at<double>(i + half_shape_rows, 0);
    }

    return points;
}
