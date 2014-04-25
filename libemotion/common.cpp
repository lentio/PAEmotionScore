#include "pch.h"
#include "common.h"
#include "myconfig.h"

#ifdef WIN32
static string GetExecutePathWin32();
#endif

string GetExecutePath()
{
#ifdef WIN32
    return GetExecutePathWin32();
#elif defined(__IOS__)
    #import <Foundation/Foundation.h>
    NSString * DocumentsPath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
    return [DocumentsPath UTF8String];
#elif defined(__ANDROID__)
    return string("/mnt/sdcard/emotion/");
#endif
}

#ifdef WIN32
string GetExecutePathWin32()
{
    char szExecutePath[MAX_PATH] = { 0 };

    GetModuleFileName(NULL, szExecutePath, MAX_PATH - 1);
    strcpy(strrchr(szExecutePath, '\\'), "");

    return szExecutePath;
}
#endif

cv::Mat procrustes(Mat m1, Mat m2)
{
    Mat mean_m1(2, 1, CV_64F);
    mean_m1.at<double>(0, 0) = cv::sum(m1.clone().reshape(0, NUM_OF_PATCHES).col(0))[0] / NUM_OF_PATCHES;
    mean_m1.at<double>(1, 0) = cv::sum(m1.clone().reshape(0, NUM_OF_PATCHES).col(1))[0] / NUM_OF_PATCHES;

    // 中心对齐
    auto center_ = [](Mat m) {
        Mat mean_m = m.clone().reshape(0, m.rows*m.cols / 2).t(); // 操作后，mean_m有两行，第一行为x坐标，第二行为y坐标
        double mean_m_x = 0.0f;
        double mean_m_y = 0.0f;
        for (int i = 0; i < mean_m.cols; ++i) {
            mean_m_x += mean_m.at<double>(0, i);
            mean_m_y += mean_m.at<double>(1, i);
        }
        mean_m_x /= mean_m.cols;
        mean_m_y /= mean_m.cols;
        for (int i = 0; i < mean_m.cols; ++i) {
            mean_m.at<double>(0, i) -= mean_m_x;
            mean_m.at<double>(1, i) -= mean_m_y;
        }
        mean_m = mean_m.t(); // 71/66行，2列

        //// for debug
        //for (int j = 0; j < mean_m.rows; ++j) {
        //    cout << (boost::format("%.17e;%.17e") % mean_m.at<double>(j, 0) % mean_m.at<double>(j, 1)).str() << endl;
        //}

        mean_m = mean_m.reshape(0, m.rows*m.cols);

        return mean_m;  // mean_m有一行，按照x1,y1,x2,y2坐标
    };
    m1 = center_(m1.clone());
    m2 = center_(m2.clone());

    // 缩放
    auto scale_ = [](Mat m1, Mat m2) {
        double sum_square_1 = 0.0;
        double sum_square_2 = 0.0;

        for (int row = 0; row < m1.rows; ++row) {
            for (int col = 0; col < m1.cols; ++col) {
                sum_square_1 += pow(m1.at<double>(row, col), 2);
                sum_square_2 += pow(m2.at<double>(row, col), 2);
            }
        }

        sum_square_1 = sqrt(sum_square_1 / 2/*m1.shape[1]*/);
        sum_square_2 = sqrt(sum_square_2 / 2/*m2.shape[1]*/);

        m2 = (m2 / sum_square_2)*sum_square_1;

        //// for debug
        //Mat t = m2.reshape(0, NUM_OF_PATCHES);
        //for (int j = 0; j < t.rows; ++j) {
        //    cout << (boost::format("%.17e;%.17e") % t.at<double>(j, 0) % t.at<double>(j, 1)).str() << endl;
        //}

        return m2;
    };
    m2 = scale_(m1.clone(), m2.clone());

    // 旋转
    Mat m1_66 = m1.clone().reshape(0, NUM_OF_PATCHES);
    Mat m2_66 = m2.clone().reshape(0, NUM_OF_PATCHES);

    Mat w, u, vt;
    SVD::compute(m1_66.t()*m2_66, w, u, vt, SVD::FULL_UV);

    // Reference: A Brief Introduction to Statistical Shape Analysis.pdf,Page 4
    Mat V = vt.t();
    Mat UT = u.t();
    Mat VUT = V*UT; // 到此为止，完全对应python脚本中的r=dot(v.T, u.T)

    m2 = m2.reshape(0, NUM_OF_PATCHES);
    m2 = m2*VUT;

    //// for debug
    //Mat t = m2.reshape(0, 66);
    //for (int j = 0; j < t.rows; ++j) {
    //    cout << (boost::format("%.17e;%.17e") % t.at<double>(j, 0) % t.at<double>(j, 1)).str() << endl;
    //}


    //double mean_m1_x = sum(m1.reshape(0, 66).colRange(0, 66));

    // 模仿python脚本中的m2 = m2+mean_m1
    m2 = m2.reshape(0, NUM_OF_PATCHES);
    for (int j = 0; j < m2.rows; ++j) {
        m2.at<double>(j, 0) += mean_m1.at<double>(0, 0);
        m2.at<double>(j, 1) += mean_m1.at<double>(1, 0);
    }

    //// for debug
    //Mat t = m2.reshape(0, NUM_OF_PATCHES);
    //for (int j = 0; j < t.rows; ++j) {
    //    cout << (boost::format("%.17e;%.17e") % t.at<double>(j, 0) % t.at<double>(j, 1)).str() << endl;
    //}

    return m2.reshape(0, m2.rows*m2.cols);
}
