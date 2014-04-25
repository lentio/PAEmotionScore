#ifndef pch_h__
#define pch_h__

#define __IOS__   

#ifdef WIN32
// Windowsͷ�ļ�
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// C++ ͷ�ļ�
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>

// boostͷ�ļ�
//#include <boost/format.hpp>
//#include <boost/algorithm/string.hpp>

// OpenCVͷ�ļ�
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/ml/ml.hpp>

// ���������ռ�
using namespace std;
using namespace cv;

#endif // pch_h__
