#ifndef pch_h__
#define pch_h__

#define __IOS__   

#ifdef WIN32
// Windows头文件
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// C++ 头文件
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>

// boost头文件
//#include <boost/format.hpp>
//#include <boost/algorithm/string.hpp>

// OpenCV头文件
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/ml/ml.hpp>

// 声明命名空间
using namespace std;
using namespace cv;

#endif // pch_h__
