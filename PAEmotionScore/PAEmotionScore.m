//
//  PAEmotionScore.m
//  PAEmotionScore
//
//  Created by InnovationLab on 14-4-25.
//  Copyright (c) 2014年 pingantech. All rights reserved.
//

using namespace cv;
using namespace std;

#import "PAEmotionScore.h"
#import "emotion_interface.h"

@implementation PAEmotionScore

+ (int)getImageEmtionScore:(UIImage *)image
{
    // preprocess image
    UIImage* scaledImage = [self OriginImage:image scaleToSize:CGSizeMake(640, 480)];
    Mat t = [self cvMatFromUIImage: scaledImage];
    Mat buf;
    t.copyTo(buf);
    
    // todo: clm  (char*)[data bytes]
    int score = emotion_get_data_score((uint8_t *)buf.data, 0, 0/*happy*/, 0/*RGB*/, 640/*width*/, 480/*height*/);
    
    return score;
}


+ (Mat)cvMatFromUIImage:(UIImage *)image
{
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image.CGImage);
    CGFloat cols = image.size.width;
    CGFloat rows = image.size.height;
    
    cv::Mat cvMat(rows, cols, CV_8UC4); // 8 bits per component, 4 channels (color channels + alpha)
    
    CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,                 // Pointer to  data
                                                    cols,                       // Width of bitmap
                                                    rows,                       // Height of bitmap
                                                    8,                          // Bits per component
                                                    cvMat.step[0],              // Bytes per row
                                                    colorSpace,                 // Colorspace
                                                    kCGImageAlphaNoneSkipLast |
                                                    kCGBitmapByteOrderDefault); // Bitmap info flags
    
    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), image.CGImage);
    CGContextRelease(contextRef);
    
    return cvMat;
}

+ (UIImage*) OriginImage:(UIImage *)image scaleToSize:(CGSize)size
{
	// 创建一个bitmap的context
	// 并把它设置成为当前正在使用的context
	UIGraphicsBeginImageContext(size);
	
	// 绘制改变大小的图片
	[image drawInRect:CGRectMake(0, 0, size.width, size.height)];
	
	// 从当前context中创建一个改变大小后的图片
	UIImage* scaledImage = UIGraphicsGetImageFromCurrentImageContext();
	
	// 使当前的context出堆栈
	UIGraphicsEndImageContext();
	
	// 返回新的改变大小后的图片
	return scaledImage;
}
@end
