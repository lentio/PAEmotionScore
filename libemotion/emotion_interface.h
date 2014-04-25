/**
* @file emotion_Interface.h
* @brief 表情（笑脸）指数检测接口
*
* 本文件提供表情（笑脸）指数检测接口
*
* @author liqian587@pingan.com.cn
* @version 1.0.0
* @date 2014
*/

#ifndef __EMOTION_INTERFACE_H__
#define __EMOTION_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#ifdef LIBEMOTION_EXPORTS
#define EMOTION_API __declspec(dllexport)
#else
#define EMOTION_API __declspec(dllimport)
#endif
#else
#define EMOTION_API
#endif

#include <stdint.h>

    /// @brief 获取主版本号
    /// 主版本号用于标记功能发生重大改变的版本，接口和前一版本不能保持兼容
    /// @return 主版本号
    EMOTION_API int32_t emotion_get_major_version();

    /// @brief 获取次版本号
    /// 次版本号用于标记功能增加或者发生较小改变的版本，接口和前一版本兼容
    /// @return 次版本号
    EMOTION_API int32_t emotion_get_minor_version();

    /// @brief 获取微版本号
    /// 微版本号用于bug fix
    /// @return 微版本号
    EMOTION_API int32_t emotion_get_micro_version();

    /// @brief 获取表情（笑脸）指数
    /// @param[in] data         输入图片缓存空间地址
    /// @param[in] size         输入图片缓存空间大小
    /// @param[in] score_type   输入图片表情类型：0：happy, 1：sad, 2：angry， 3：surprised， 4：fear， 5：disgusted.
    /// @param[in] image_type   输入图像格式 0: RGB 1: YUV420SP(NV21)
    /// @param[in] image_width  输入图像像素宽度值
    /// @param[in] image_height 输入图像像素高度值
    /// @return 表情（笑脸）指数
    /// \n0-99: 成功返回笑容指数
    /// \n-1:调用失败
    EMOTION_API int32_t	emotion_get_data_score(uint8_t* data, int32_t size, int32_t score_type, int32_t image_type, int32_t image_width, int32_t image_height);

    /// @brief 获取表情（笑脸）指数
    /// @param[in] file        输入图片本地文件系统存放的路径文件名
    /// @param[in] score_type  输入图片表情类型：0：happy, 1：sad, 2：angry， 3：surprised， 4：fear， 5：disgusted.
    /// @return 表情（笑脸）指数
    /// \n0-99: 成功返回笑容指数
    /// \n-1:调用失败
    EMOTION_API int32_t	emotion_get_file_score(char* file, int32_t score_type);

#ifdef __cplusplus
};
#endif

#endif /*__EMOTION_INTERFACE_H__*/