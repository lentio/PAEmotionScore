/**
* @file emotion_Interface.h
* @brief ���飨Ц����ָ�����ӿ�
*
* ���ļ��ṩ���飨Ц����ָ�����ӿ�
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

    /// @brief ��ȡ���汾��
    /// ���汾�����ڱ�ǹ��ܷ����ش�ı�İ汾���ӿں�ǰһ�汾���ܱ��ּ���
    /// @return ���汾��
    EMOTION_API int32_t emotion_get_major_version();

    /// @brief ��ȡ�ΰ汾��
    /// �ΰ汾�����ڱ�ǹ������ӻ��߷�����С�ı�İ汾���ӿں�ǰһ�汾����
    /// @return �ΰ汾��
    EMOTION_API int32_t emotion_get_minor_version();

    /// @brief ��ȡ΢�汾��
    /// ΢�汾������bug fix
    /// @return ΢�汾��
    EMOTION_API int32_t emotion_get_micro_version();

    /// @brief ��ȡ���飨Ц����ָ��
    /// @param[in] data         ����ͼƬ����ռ��ַ
    /// @param[in] size         ����ͼƬ����ռ��С
    /// @param[in] score_type   ����ͼƬ�������ͣ�0��happy, 1��sad, 2��angry�� 3��surprised�� 4��fear�� 5��disgusted.
    /// @param[in] image_type   ����ͼ���ʽ 0: RGB 1: YUV420SP(NV21)
    /// @param[in] image_width  ����ͼ�����ؿ��ֵ
    /// @param[in] image_height ����ͼ�����ظ߶�ֵ
    /// @return ���飨Ц����ָ��
    /// \n0-99: �ɹ�����Ц��ָ��
    /// \n-1:����ʧ��
    EMOTION_API int32_t	emotion_get_data_score(uint8_t* data, int32_t size, int32_t score_type, int32_t image_type, int32_t image_width, int32_t image_height);

    /// @brief ��ȡ���飨Ц����ָ��
    /// @param[in] file        ����ͼƬ�����ļ�ϵͳ��ŵ�·���ļ���
    /// @param[in] score_type  ����ͼƬ�������ͣ�0��happy, 1��sad, 2��angry�� 3��surprised�� 4��fear�� 5��disgusted.
    /// @return ���飨Ц����ָ��
    /// \n0-99: �ɹ�����Ц��ָ��
    /// \n-1:����ʧ��
    EMOTION_API int32_t	emotion_get_file_score(char* file, int32_t score_type);

#ifdef __cplusplus
};
#endif

#endif /*__EMOTION_INTERFACE_H__*/