#ifndef FaceTracker_h__
#define FaceTracker_h__

#include "FaceTracker/Tracker.h"
using namespace cv;

class CFaceTracker
{
public:
    CFaceTracker(const char* model_file);
    ~CFaceTracker(void);

public:
    void Reset();
    int Track(const Mat& image);
    Mat GetFeaturePoints();

private:
    CFaceTracker();

private:
    FACETRACKER::Tracker m_tracker;
    bool m_is_fail;
    Mat m_gray;
    int m_idx;

    // ²ÎÊý
    vector<int> m_wSize_succ;
    vector<int> m_wSize_fail;
    int m_number_of_iteration;
    double m_clamp;
    double m_tol;
};

#endif // FaceTracker_h__
