<h1 align="center">OpenCV4 C++</h1>

为何编写该笔记， 因为网上各种博文写的太垃圾， 于是自己写一份人人都能迅速理解的笔记， 免费供大家查阅

<h5 align='right' > update 2020.9.4</h5>

### 目录

> 安装
>
> 1. 基本
> 2. 图像处理
> 3. 对视频or摄像头读取
> 4. 各类型(Vec, Scalar, Point, Size, Rect)
> 5. API
>
> - 目录待编辑***
>
> 6. CMakeLists.txt 编写
> 7. Gstream
> 8. 其他
>    - 目录待编辑***
> 9. 参考资料
>
> 

### 安装

MacOS 基于Homebrew安装

```shell
brew install opencv
```

会耗时约3个小时左右才安装完毕， 结束之后直接安装好最新版本openCV



CMakelist中务必配置

```cmake
#opencv
find_package(OpenCV REQUIRED)
message("OpenCV version: " ${OpenCV_VERSION})
include_directories(${OpenCV_INCLUDE_DIRS} )
link_directories(${OpenCV_LIB_DIR})



target_link_libraries(xxxx ${OpenCV_LIBS}) //xxxx表示自己的执行文件名称
```

### 基本

#### Mat

主要用来存储图像

Ref http://zhaoxuhui.top/blog/2019/08/24/OpenCV-Mat-Note.html

在早期OpenCV中(OpenCV 1.x)大量使用`IplImage`、`CvMat`实现数据处理，其需要手动进行内存管理，使用不是很方便。到OpenCV 2.x版本后引入C++面向对象思想，重构了代码，引入`Mat`。作为升级，`Mat`存储的数据结构与`CvMat`、`IplImage`等完全兼容，也和`Numpy(ndarray)`兼容

创建`Mat`有多种方法，常见的有以下几种, 可以一一对照

```c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat m1(4, 3, CV_8UC1);
    cout << m1 << endl << endl;

    Mat m2(3, 5, CV_8UC1, 200);
    cout << m2 << endl << endl;

    Mat m3(2, 4, CV_8UC1, -10);
    cout << m3 << endl << endl;

    Mat m4;
    m4.create(2, 3, CV_8UC1);
    cout << m4 << endl;
    cout << "CV_8UC1" << endl;
    cout << "channels:" << m4.channels() << endl;
    cout << "row & col:" << m4.rows << " & " << m4.cols << endl;
    cout << "size:" << m4.size << endl;
    cout << "dims:" << m4.dims << endl << endl;

    Mat m5(3, 2, CV_8UC3, Scalar(20, 10, 30));
    cout << m5 << endl;
    cout << "CV_8UC3" << endl;
    cout << "channels:" << m5.channels() << endl;
    cout << "row & col:" << m5.rows << " & " << m5.cols << endl;
    cout << "size:" << m5.size << endl;
    cout << "dims:" << m5.dims << endl << endl;

    Mat m6(3, 2, CV_8UC(5));
    cout << m6 << endl;
    cout << "CV_8UC5" << endl;
    cout << "channels:" << m6.channels() << endl;
    cout << "row & col:" << m6.rows << " & " << m6.cols << endl;
    cout << "size:" << m6.size << endl;
    cout << "dims:" << m6.dims << endl << endl;

    int sz[] = {3, 4, 2};
    Mat m7(3, sz, CV_8U, Scalar::all(0));
    cout << "CV_8U" << endl;
    cout << "m7 can't print out,because m7.dims = 3 and it requires m.dims <= 2" << endl;
    cout << "channels:" << m7.channels() << endl;
    cout << "row & col:" << m7.rows << " & " << m7.cols << endl;
    cout << "size:" << m7.size << endl;
    cout << "dims:" << m7.dims << endl << endl;
    return 0;
}


>>> output
[  0,   0,   0;
   0,   0,   0;
   0,   0,   0;
   0,   0,   0]

[200, 200, 200, 200, 200;
 200, 200, 200, 200, 200;
 200, 200, 200, 200, 200]

[  0,   0,   0,   0;
   0,   0,   0,   0]

[  0,   0,   0;
   0,   0,   0]
CV_8UC1
channels:1
row & col:2 & 3
size:2 x 3
dims:2

[ 20,  10,  30,  20,  10,  30;
  20,  10,  30,  20,  10,  30;
  20,  10,  30,  20,  10,  30]
CV_8UC3
channels:3
row & col:3 & 2
size:3 x 2
dims:2

[  0,   0,   0,   0,   0,   0,   0,   0,   0,   0;
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0;
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0]
CV_8UC5
channels:5
row & col:3 & 2
size:3 x 2
dims:2

CV_8U
m7 can't print out,because m7.dims = 3 and it requires m.dims <= 2
channels:1
row & col:-1 & -1
size:3 x 4 x 2
dims:3
```





利用clone 或者赋值函数, 以及at改变元素值

```cpp
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat m1(Size(3, 2), CV_16S, Scalar(-3));
    Mat m2(m1);

    Mat m3 = m1;
    Mat m4 = imread("img.jpg");
    Mat m5 = m1.clone();

    m3.at<short>(1, 1) = 2;
    m5.at<short>(0, 1) = 9;
    cout << "m1:" << endl << m1 << endl << endl;
    cout << "m2:" << endl << m2 << endl << endl;
    cout << "m3:" << endl << m3 << endl << endl;
    cout << "m5:" << endl << m5 << endl;
    return 0;
}


>>> output
m1:
[-3, -3, -3;
 -3, 2, -3]

m2:
[-3, -3, -3;
 -3, 2, -3]

m3:
[-3, -3, -3;
 -3, 2, -3]

m5:
[-3, 9, -3;
 -3, -3, -3]
```





#### 常用头文件

```c++
#include "opencv2/core.hpp" //主要包含了opencv基本数据结构，动态数据结构，绘图函数，数组操作相关函数，辅助功能与系统函数和宏
#include "opencv2/imgproc.hpp" //图像处理模块
#include "opencv2/video.hpp" //视频模块
#include "opencv2/objdetect.hpp" //
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp" //高层IO， 一些可视化模块例如imshow， imread， imwrite..etc
#include "opencv2/ml.hpp" //机器学习模块
#include "vector" //容器， 可用来存储各种数据

或者可以简单的直接
#include<opencv2/opencv.hpp> //opencv.hpp的头文件包含了opencv库里的所有头文件
```





### 图像处理

#### 加载图像

```c++
Mat color = imread("test.jpg"); //读取为彩色图像

Mat gray = imread("test.jpg", CV_LOAD_IMAGE_GRAYSCALE); //指定读取为灰度图
```



#### 访问图像的行或者列

```c++
int MyRaw = color.cols-1;
int MyCol = color.rows-1;
```



#### 访问图像中的某个像素

```c++
//cv::Mat::at<typename>(row, col)
Vec3b pixel = color.at<Vec3b>(myRow, myCol);
cout << "Pixel value (B, G, R): (" << (int)pixel[0] << ", " << (int)pixel[1] << ", " << (int)pixel[2]<<")" << endl;
```

8位彩色图像的类型是Vec3b （Vec = 向量， 3 = 组件数， b = 一个字节）



#### 展示图像

```C++
imshow("Test_bgr", color);
imshow("Test_gray", gray);
waitkey(0); 
```

waitkey表示等待用户按下某个键就关闭窗口， 0表示任何键



#### resize图像

将图像大小缩放

```c++
void cv::resize	(	InputArray 	src,
OutputArray 	dst,
Size 	dsize,
double 	fx = 0,
double 	fy = 0,
int interpolation = INTER_LINEAR 
)
```

Ex.

```c++
cv::resize(src, dst, Size(xxx, xxx), 0, 0, INTER_LINEAR)
```





#### 创造一个像素点全为0的图像 fill with zeros

```
cv::Mat::zeros()
```



#### 图像ROI区域选定

ex. 在原图上 利用`cv::Rect`选定出roi区域， 可以在此roi上做变化， 比如改变颜色之类的

```c++
Mat orange = imread("./images/orange.png");

Mat roi = orange(Rect(0, 0, apple.cols, apple.rows));
```





#### 图像复制的方法

**CopyTo**的方法有两种

第一个功能其实就是把输入图像完完全全拷贝到输出图像上，并且将输出图像的大小调整成输入图像的大小

```
void copyTo( OutputArray m ) const;
```





```
void copyTo(OutputArray m, InputArray mask) const;
```

也就是参数可以是一张输出图像，或者一张输出图像和一个掩码图

//TODO mask参数的用法待了解



**clone()**





区别： 当目标矩阵与源矩阵具有相同的type和size时，copyTo不会为目标矩阵重新分配内存

而clone总是会为目标矩阵重新分配内存

```c++
#copyTo
Mat mat1 = Mat::ones(1, 5, CV_32F);   // [1,1,1,1,1]
Mat mat2 = mat1;   // mat2与mat1指向同一内存地址
Mat mat3 = Mat::zeros(1, 5, CV_32F);  // [0,0,0,0,0]
mat3.copyTo(mat1); // mat1未被重新分配内存，通过mat1可以改变mat2的内容
cout << mat1 << endl;   // [0,0,0,0,0] 
cout << mat2 << endl;   // [0,0,0,0,0]

#clone()
Mat mat1 = Mat::ones(1, 5, CV_32F);   // [1,1,1,1,1]
Mat mat2 = mat1;   // mat2与mat1指向同一内存地址
Mat mat3 = Mat::zeros(1, 5, CV_32F);   // [0,0,0,0,0]
mat1 = mat3.clone();   // mat1被重新分配内存，通过mat1不能改变mat2的内容
cout << mat1 << endl;   // [0,0,0,0,0]
cout << mat2 << endl;   // [1,1,1,1,1]

```





#### 图像基础运算

比如两幅图像可以相加、相减、相乘、相除、位运算、平方根、对数、绝对值等；图像也可以放大、缩小、旋转，还可以截取其中的一部分作为ROI（感兴趣区域）进行操作，各个颜色通道还可以分别提取及对各个颜色通道进行各种运算操作。总之，对于图像可以进行的基本运算非常的多，只是挑了些常用的操作详解

```c++
void add(InputArray src1, InputArray src2, OutputArray dst,InputArray mask=noArray(), int dtype=-1);//dst = src1 + src2
void subtract(InputArray src1, InputArray src2, OutputArray dst,InputArray mask=noArray(), int dtype=-1);//dst = src1 - src2
void multiply(InputArray src1, InputArray src2,OutputArray dst, double scale=1, int dtype=-1);//dst = scale*src1*src2
void divide(InputArray src1, InputArray src2, OutputArray dst,double scale=1, int dtype=-1);//dst = scale*src1/src2
void divide(double scale, InputArray src2,OutputArray dst, int dtype=-1);//dst = scale/src2
void scaleAdd(InputArray src1, double alpha, InputArray src2, OutputArray dst);//dst = alpha*src1 + src2
void addWeighted(InputArray src1, double alpha, InputArray src2,double beta, double gamma, OutputArray dst, int dtype=-1);//dst = alpha*src1 + beta*src2 + gamma
void sqrt(InputArray src, OutputArray dst);//计算每个矩阵元素的平方根
void pow(InputArray src, double power, OutputArray dst);//src的power次幂
void exp(InputArray src, OutputArray dst);//dst = e**src（**表示指数的意思）
void log(InputArray src, OutputArray dst);//dst = log(abs(src))
```



```c++
void bitwise_and(InputArray src1, InputArray src2,OutputArray dst, InputArray mask=noArray());//dst = src1 & src2
void bitwise_or(InputArray src1, InputArray src2,OutputArray dst, InputArray mask=noArray());//dst = src1 | src2
void bitwise_xor(InputArray src1, InputArray src2,OutputArray dst, InputArray mask=noArray());//dst = src1 ^ src2
void bitwise_not(InputArray src, OutputArray dst,InputArray mask=noArray());//dst = ~src

```

bitwise_and是对二进制数据进行“与”操作，即对图像（灰度图像或彩色图像均可）每个像素值进行二进制“与”操作，1&1=1，1&0=0，0&1=0，0&0=0
bitwise_or是对二进制数据进行“或”操作，即对图像（灰度图像或彩色图像均可）每个像素值进行二进制“或”操作，1|1=1，1|0=0，0|1=0，0|0=0
bitwise_xor是对二进制数据进行“异或”操作，即对图像（灰度图像或彩色图像均可）每个像素值进行二进制“异或”操作，1^1=0,1^0=1,0^1=1,0^0=0
bitwise_not是对二进制数据进行“非”操作，即对图像（灰度图像或彩色图像均可）每个像素值进行二进制“非”操作，~1=0，~0=1



#### 将图像通道分类及合并 cv::split / cv::merge

https://blog.csdn.net/guduruyu/article/details/70837779

处理多通道图像时，有时需要对各个通道进行分离，分别处理；有时还需要对分离处理后的各个通道进行合并，重新合并成一个多通道的图像

```C++
int main()
{
	cv::Mat src = imread("lenna.jpg", cv::IMREAD_COLOR);
	cv::imshow("src", src);
 
	// Split the image into different channels
	std::vector<cv::Mat> rgbChannels(3);
	split(src, rgbChannels);
 
	// Show individual channels
	cv::Mat blank_ch, fin_img;
	blank_ch = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC1);
 
	// Showing Red Channel
	// G and B channels are kept as zero matrix for visual perception
	std::vector<cv::Mat> channels_r;
	channels_r.push_back(blank_ch);
	channels_r.push_back(blank_ch);
	channels_r.push_back(rgbChannels[2]);
 
	/// Merge the three channels
	cv::merge(channels_r, fin_img);
	cv::imshow("R", fin_img);
	
 
	// Showing Green Channel
	std::vector<cv::Mat> channels_g;
	channels_g.push_back(blank_ch);
	channels_g.push_back(rgbChannels[1]);
	channels_g.push_back(blank_ch);
	cv::merge(channels_g, fin_img);
	cv::imshow("G", fin_img);
	
 
	// Showing Blue Channel
	std::vector<cv::Mat> channels_b;
	channels_b.push_back(rgbChannels[0]);
	channels_b.push_back(blank_ch);
	channels_b.push_back(blank_ch);
	cv::merge(channels_b, fin_img);
	cv::imshow("B", fin_img);
	
	cv::waitKey(0);
	return 0;
}

```



#### 改变图像色彩空间

```C++
void cv::cvtColor	(	InputArray 	src, OutputArray 	dst, int 	code, int dstCn = 0 )	
```

- code 主要包含各种色彩转换接口
  - https://docs.opencv.org/3.4/d8/d01/group__imgproc__color__conversions.html#ga4e0972be5de079fed4e3a10e24ef5ef0
- dstCn : 输出的图像的通道数， 默认为0表示跟原图像一样



#### 存取图像

```c++
bool cv::imwrite	(	const String & 	filename, InputArray 	img, const std::vector< int > & 	params = std::vector< int >())
```

- filename : Name of the file.
- img : Image to be saved.
- params : Format-specific parameters encoded as pairs (paramId_1, paramValue_1, paramId_2, paramValue_2, ... .) see [cv::ImwriteFlags](https://docs.opencv.org/3.4/d4/da8/group__imgcodecs.html#ga292d81be8d76901bff7988d18d2b42ac)

#### 图像去噪 - 滤波器

**高斯滤波**

可以模糊化图片， 也有抗噪声的效果

```c++
void cv::GaussianBlur	(	InputArray 	src,
OutputArray 	dst,
Size 	ksize,
double 	sigmaX,
double 	sigmaY = 0,
int 	borderType = BORDER_DEFAULT 
)
```

| src        | input image; the image can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F. |
| ---------- | ------------------------------------------------------------ |
| dst        | output image of the same size and type as src.               |
| ksize      | Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd. Or, they can be zero's and then they are computed from sigma. |
| sigmaX     | Gaussian kernel standard deviation in X direction.           |
| sigmaY     | Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height, respectively (see [getGaussianKernel](https://docs.opencv.org/3.4/d4/d86/group__imgproc__filter.html#gac05a120c1ae92a6060dd0db190a61afa) for details); to fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY. |
| borderType | pixel extrapolation method, see [BorderTypes](https://docs.opencv.org/3.4/d2/de8/group__core__array.html#ga209f2f4869e304c82d07739337eae7c5). [BORDER_WRAP](https://docs.opencv.org/3.4/d2/de8/group__core__array.html#gga209f2f4869e304c82d07739337eae7c5a697c1b011884a7c2bdc0e5caf7955661) is not supported. |





#### 阈值threshold

对array上的每个像素进行阈值处理

```c++
double cv::threshold	(	InputArray 	src, OutputArray 	dst, double 	thresh, double 	maxval,
int type )	
```

- Thresh : threshold value.
- maxval : maximum value to use with the [THRESH_BINARY](https://docs.opencv.org/4.2.0/d7/d1b/group__imgproc__misc.html#ggaa9e58d2860d4afa658ef70a9b1115576a147222a96556ebc1d948b372bcd7ac59) and [THRESH_BINARY_INV](https://docs.opencv.org/4.2.0/d7/d1b/group__imgproc__misc.html#ggaa9e58d2860d4afa658ef70a9b1115576a19120b1a11d8067576cc24f4d2f03754) thresholding types.
- threshold type :查看https://docs.opencv.org/4.2.0/d7/d1b/group__imgproc__misc.html#gaa9e58d2860d4afa658ef70a9b1115576

#### 霍夫检测（线， 圆）

**霍夫直线**

理论参考 https://blog.csdn.net/weixin_44638957/article/details/105881922

```c++
void cv::HoughLines( 
  cv::InputArray image, 
  cv::OutputArray lines, 
  double rho, double theta, 
  int threshold, 
  double srn = 0, 
  double stn = 0 );

// Input single channel image 
// N-by-1 two-channel array 
// rho resolution (pixels) 
// theta resolution (radians) 
// Unnormalized accumulator threshold 
// rho refinement (for MHT) 
// theta refinement (for MHT)
```

```c++
void cv::HoughLinesP	(	InputArray 	image,
OutputArray 	lines,
double 	rho,
double 	theta,
int 	threshold,
double 	minLineLength = 0,
double 	maxLineGap = 0 
)
```



- Image 输入图像
- Lines 输出直线
- Rho 极坐标r得步长
- Theta角度步长
- Threshold累加器阈值
- Srn、stn多尺度霍夫变换时候需要得参数，经典霍夫变换不需要
- Min_theta :  限定最小角度
- Max_theta ： 限定在min_theta 及CV_PI之间
- double *minLineLength* = 0
- double *maxLineGap* = `0` 





```c++
void cv::HoughCircles	(	InputArray 	image,
OutputArray 	circles,
int 	method,
double 	dp,
double 	minDist,
double 	param1 = 100,
double 	param2 = 100,
int 	minRadius = 0,
int 	maxRadius = 0 
)	
```



**霍夫圆**

参考 https://blog.csdn.net/weixin_44638957/article/details/105883829



```cpp
void HoughCircles( InputArray image, 
                  OutputArray circles,
									int method, 
                  double dp, 
                  double minDist,
									double param1=100, 
                  double param2=100,
									int minRadius=0, 
                  int maxRadius=0 );
```

第一个参数image是输入图像矩阵，要求是灰度图像；

第二个参数 circles是一个包含检测到的圆的信息的向量，向量内第一个元素是圆的横坐标，第二个是纵坐标，第三个是半径大小；

第三个参数 methodmethod是所使用的圆检测算法，目前只有CV_HOUGH_GRADIENT一个可选；

第四个参数 dp是累加面与原始图像相比的分辨率的反比参数，dp=2时累计面分辨率是元素图像的一半，宽高都缩减为原来的一半，dp=1时，两者相同。（关于这个分辨率的概念没有理解透，按道理低分辨率应该意味着更快的检测速度，然而实测恰恰相反）

第五个参数 minDist定义了两个圆心之间的最小距离；

第六个参数param1是Canny边缘检测的高阈值，低阈值被自动置为高阈值的一半；

第七个参数param2是累加平面对是否是圆的判定阈值；

第八和第九个参数定义了检测到的圆的半径的最大值和最小值；



#### 边缘检测

[求导的一些介绍](https://blog.csdn.net/kakiebu/article/details/79362576?ops_request_misc=%7B%22request%5Fid%22%3A%22158805933119195162532436%22%2C%22scm%22%3A%2220140713.130102334.pc%5Fblog.%22%7D&request_id=158805933119195162532436&biz_id=0&utm_source=distribute.pc_search_result.none-task-blog-2~blog~first_rank_v2~rank_v25-2)

[图像一阶导数or二阶导数](https://blog.csdn.net/du_shuang/article/details/82932546)

一般来说，当我们想要获取图像的边缘时，首先想到的就是像素值发生突变的位置，而如何用数学表达来刻画"突变"，一个很好的方式就是使用导数，而在图像中，由于像素是离散的，我们一般使用差分来近似处理，使用某种算子来近似计算全图每一点的梯度值，其中梯度明显大于邻近像素的点就被认为是边缘(实际处理中，使用大于某一阈值作为评判标准)

边缘检测一般步骤：

1. 滤波 ： 边缘检测的算法主要是基于图像强度的一阶和二阶导数，**但导数通常对噪声很敏感，因此必须采用滤波器来， 改善与噪声**有关的边缘检测器的性能。常见的滤波方法主要有高斯滤波， 即采用离散化的高斯函数产生一组归一化的高斯核（具体见“高斯滤波原理及其编程离散化实现方法”一文），然后基于高斯核函数对图像灰度矩阵的每一点进行加权求和
2. 增强 ： 增强边缘的基础是确定图像各点邻域强度的变化值。增强算法可以将图像灰度点邻域强度值有显著变化的点凸显出来。在具体编程实现时，可通过计算梯度幅值来确定
3. 检测 ： 经过增强的图像，往往邻域中有很多点的梯度值比较大，而在特定的应用中，这些点并不是我们要找的边缘点，所以应该采用某种方法来对这些点进行取舍。实际工程中，常用的方法是通过阈值化方法来检测



**一阶导数和二阶导数**

**計算一階導數**

許多邊緣檢測操作都是基於亮度的一階[導數](https://zh.wikipedia.org/wiki/导数)——這樣就得到了原始資料亮度的[梯度](https://zh.wikipedia.org/w/index.php?title=Image_gradient&action=edit&redlink=1)。使用這個資訊我們能夠在圖像的亮度梯度中搜尋峰值。

如果*I*（*x*） 表示點*x*的亮度，*I*′（*x*） 表示點*x*的一階導數（亮度梯度），這樣我們就會發現：

$I'(x) = -1/2 * I(x-1) + 0 *I (x) + 1/2 * I(x+1)$

對於更高效能的圖像處理來說，**一階導數能夠通過帶有遮罩的原始資料（1維）[卷積](https://zh.wikipedia.org/wiki/卷积)計算得到**

[−1/2,  0,  1/2]

**計算二階導數**

其它一些邊緣檢測操作是基於亮度的二階導數。這實質上是亮度梯度的[變化率](https://zh.wikipedia.org/w/index.php?title=变化率&action=edit&redlink=1)。在理想的連續變化情況下，在二階導數中檢測過零點將得到梯度中的局部最大值。另一方面，二階導數中的峰值檢測是邊線檢測，只要圖像操作使用一個合適的尺度表示。如上所述，邊線是雙重邊緣，這樣我們就可以在邊線的一邊看到一個亮度梯度，而在另一邊看到相反的梯度。這樣如果圖像中有邊線出現的話我們就能在亮度梯度上看到非常大的變化。為了找到這些邊線，我們可以在圖像亮度梯度的二階導數中尋找過零點。

如果*I*（*x*） 表示點*x*的亮度，*I*′′（*x*） 表示點*x*亮度的二階導數，那麼：

$I'(x) = 1 * I(x-1)  -2 *I (x) + 1 * I(x+1)$

同樣，許多演算法也使用[卷積](https://zh.wikipedia.org/wiki/卷积)遮罩快速處理圖像資料：



[+1, −2, +1]



**Canny算法**

canny算子是一种更系统性的边缘检测算子，其使用sobel算子作为检测器的补一份，同时首先使用gauss滤波器减弱噪声的影响，提取出边缘之后再用NMS(非极大值抑制)和阈值筛选来减少虚假边缘，这里我主要涉及其中的非极大值抑制部分。

在目标检测任务中对检测框NMS已经是一个家喻户晓的基本操作，但其实这是图像处理算法中的常用技巧。canny中的非极大值抑制，即要在sobel提取出的梯度图中找到梯度的局部最大值，并将非极大值置为0，从而减少虚检。而canny中的NMS是指是否为梯度方向上的极大值，不像角点检测等场景下是其邻域中的最大值。具体的算法步骤如下：

- 对sobel提取的垂直和水平方向的结果使用反正切的近似获得梯度方向
- 根据梯度方向在滤波器范围内找到两个邻近的亚像素点(sub-pixel)
- 使用双线性插值获得这两个亚像素点的梯度估计值
- 将两个估计值和当前点的梯度相比较，若不是极大值，则置为0，否则保持不变

```c++
void Canny(InputArray image,OutputArray edges, double threshold1, double threshold2, int apertureSize=3,bool L2gradient=false )
```

第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和类型。
第三个参数，double类型的threshold1，第一个滞后性阈值。
第四个参数，double类型的threshold2，第二个滞后性阈值。
第五个参数，int类型的apertureSize，表示应用Sobel算子的孔径大小，其有默认值3。
第六个参数，bool类型的L2gradient，一个计算图像梯度幅值的标识，有默认值false

PS.这个函数阈值1和阈值2两者的小者用于边缘连接，而大者用来控制强边缘的初始段，推荐的高低阈值比在2:1到3:1之间



**sobel算法**

sobel算子就是实现上述算法的一种基本算子，其一般分为水平和垂直两个方向的计算，两个方向上的算子互为转置。在两个方向分别计算完成之后，取其绝对值的和或平方和的算术平方根(1，2范数)，即得到最终的梯度结果。**(一般来说在硬件上计算绝对值要比平方开方廉价很多，所以一般使用绝对值较多)**

```c++
C++: void Sobel (
InputArray src,//输入图
 OutputArray dst,//输出图
 int ddepth,//输出图像的深度
 int dx,
 int dy,
 int ksize=3,
 double scale=1,
 double delta=0,
 int borderType=BORDER_DEFAULT );
```

需要针对x及y方向分别进行求梯度



还需要convertScaleAbs转换函数， （把求导后的结果都转成正数？）

针对输入的每个元素 乘上alpha + beta 取abs 并转换为int8

```c++
void cv::convertScaleAbs	(	InputArray 	src,
OutputArray 	dst,
double 	alpha = 1,
double 	beta = 0 
)	
```

最终利用addWeighted 针对两个输入进行权重分配然后相加， 该函数执行 $dst = src1*alpha + src2*beta + gamma;$

```c++
void cv::addWeighted	(	InputArray 	src1,
double 	alpha,
InputArray 	src2,
double 	beta,
double 	gamma,
OutputArray 	dst,
int 	dtype = -1 
)	
```





**scharr算法**

```c++
void cv::Scharr	(	InputArray 	src,
OutputArray 	dst,
int 	ddepth,
int 	dx,
int 	dy,
double 	scale = 1,
double 	delta = 0,
int 	borderType = BORDER_DEFAULT 
)
```

检测边缘的效果更好， 主要跟sobel的区别在于内核数值不同



**Laplacian算法**

<img src="https://www.zhihu.com/equation?tex=Laplace%28f%29%3D%5Cfrac%7B%5Cpartial%5E2f%7D%7B%5Cpartial+x%5E2%7D%2B%5Cfrac%7B%5Cpartial%5E2f%7D%7B%5Cpartial+y%5E2%7D">

sobel算子具有明确的方向性(垂直和水平)，将图像旋转某一角度，其提取效果就会下降，但是laplace算子却是具有旋转不变性的，这一点可从其模板中心对称性，或者从原始公式证明得到

由于laplace算子使用了二阶导数，所以其相比sobel这种一阶方法对噪声更敏感，其受噪声的影响更明显（想象一下一条平滑的函数图像上出现了很多锯齿段，这样自然会错误地发现更多虚假的极值点）

```c++
void Laplacian(InputArray src,OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, intborderType=BORDER_DEFAULT );
```

第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和通道数。
第三个参数，int类型的ddept，目标图像的深度。
第四个参数，int类型的ksize，用于计算二阶导数的滤波器的孔径尺寸，大小必须为正奇数，且有默认值1。
第五个参数，double类型的scale，计算拉普拉斯值的时候可选的比例因子，有默认值1。
第六个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
第七个参数， int类型的borderType，边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate()处得到更详细的信息

#### Mask 掩膜

在有些图像处理的函数中有的参数里面会有mask参数，即此函数支持掩膜操作

```c++
void cv::inRange	(	InputArray 	src,
InputArray 	lowerb,
InputArray 	upperb,
OutputArray 	dst 
)	
```

inrange类似threshhold， 如果一幅灰度图像的某个像素的灰度值在指定的高、低阈值范围之内，则在dst图像中令该像素值为255，否则令其为0，这样就生成了一幅二值化的输出图像

针对三通道图像
dst(I) = lowerb(I)0 ≤ src(I)0 < upperb(I)0 ∧ lowerb(I)1 ≤ src(I)1 < upperb(I)1 ∧lowerb(I)2 ≤ src(I)2 < upperb(I)2
即，每个通道的像素值都必须在规定的阈值范围内





#### 形态学

结构元素可以是矩形/椭圆/十字形，可以用`getStructuringElement()`来生成不同形状的结构元素, 就是产生一个卷积核运用在膨胀或者腐蚀上

```c++
Mat cv::getStructuringElement	(	int shape, Size 	ksize, Point 	anchor = Point(-1,-1))	
```

- shape : 元素的形状[MorphShapes](https://docs.opencv.org/4.2.0/d4/d86/group__imgproc__filter.html#gac2db39b56866583a95a5680313c314ad)
- ksize ：结构元素的尺寸
- anchor ： 在元素中的anchor的位置预设是(-1, -1)表示在正中间， 只有crossshapeed element取决于anchor的位置， In other cases the anchor just regulates how much the result of the morphological operation is shifted

```c++
void cv::morphologyEx	(	InputArray 	src,
OutputArray 	dst,
int 	op,
InputArray 	kernel,
Point 	anchor = Point(-1,-1),
int 	iterations = 1,
int 	borderType = BORDER_CONSTANT,
const Scalar & 	borderValue = morphologyDefaultBorderValue() 
)	
```

Parameters

- src : source image
- Dst : 与source一样size的目标图像
- op ： 形态学操作 [MorphTypes](https://docs.opencv.org/4.2.0/d4/d86/group__imgproc__filter.html#ga7be549266bad7b2e6a04db49827f9f32)
- kernel ： 就是利用getStructuringElement 制作的kernel
- anchor ： 
- iteration：erosion or dilation的次数
- borderType ： 像素外推的方法[BorderTypes](https://docs.opencv.org/4.2.0/d2/de8/group__core__array.html#ga209f2f4869e304c82d07739337eae7c5)
- borderValue : 边界值， 如果边界是个常数的话



#### 轮廓

```c++
void cv::findContours	(	InputArray 	image,
OutputArrayOfArrays 	contours,
OutputArray 	hierarchy,
int 	mode,
int 	method,
Point 	offset = Point() 
)	
```

基于二值图像上找到轮廓，基于 [[216]](https://docs.opencv.org/4.2.0/d0/de3/citelist.html#CITEREF_Suzuki85), 轮廓对于检测及识别是形状分析是很好的工具

- image : source image 二值图
- contours ： 找到的轮廓， 存储的方式为`vector< vector<Point> >`, point存储的就是属于这个轮廓的坐标， vector 存储属于这个轮廓的所有坐标点， 外圈vector存储所有的轮廓
- hierachy ：Optional output vector (e.g. std::vector<cv::Vec4i>), containing information about the image topology. It has as many elements as the number of contours. For each i-th contour contours[i], the elements hierarchy[i][0] , hierarchy[i][1] , hierarchy[i][2] , and hierarchy[i][3] are set to 0-based indices in contours of the next and previous contours at the same hierarchical level, the first child contour and the parent contour, respectively. If for the contour i there are no next, previous, parent, or nested contours, the corresponding elements of hierarchy[i] will be negative.
- mode ：轮廓获取的模式
- method ：轮廓近似的方法， 用最少的顶点连成形状[ContourApproximationModes](https://docs.opencv.org/4.2.0/d3/dc0/group__imgproc__shape.html#ga4303f45752694956374734a03c54d5ff)
- Offset : 设置轮廓的点的偏移值， 当轮廓从image的roi找出来， 但需要从整张图来分析的时候

```c++
double cv::contourArea	(	InputArray 	contour,
bool 	oriented = false 
)	
```

计算出contour的面积



### 画出边界框

```c++
Rect cv::boundingRect	(	InputArray 	array	)	
```

找到可以用最小矩形框出物体的（x, y, w, h)

- array :输入灰度图 或者 2d点集合（vector or mat）





#### 图像分割

```c++
void cv::grabCut	(	InputArray 	img,
InputOutputArray 	mask,
Rect 	rect,
InputOutputArray 	bgdModel,
InputOutputArray 	fgdModel,
int 	iterCount,
int 	mode = GC_EVAL 
)
```

- img : soruce img
- mask : single channel mask (ROI区域的mask)
- Rect : 
- bdgModel : 临时背景模型数组
- fgdModel ： 临时前景模型数组
- interCount ： 指定多少就等于 13乘以多少
- mode : 

| img       | Input 8-bit 3-channel image.                                 |
| --------- | ------------------------------------------------------------ |
| mask      | Input/output 8-bit single-channel mask. The mask is initialized by the function when mode is set to [GC_INIT_WITH_RECT](https://docs.opencv.org/3.4/d7/d1b/group__imgproc__misc.html#ggaf8b5832ba85e59fc7a98a2afd034e558a5f8853c1e5a89c4aa2687d1f78a7e550). Its elements may have one of the [GrabCutClasses](https://docs.opencv.org/3.4/d7/d1b/group__imgproc__misc.html#gad43d3e4208d3cf025d8304156b02ba38). |
| rect      | ROI containing a segmented object. The pixels outside of the ROI are marked as "obvious background". The parameter is only used when mode==[GC_INIT_WITH_RECT](https://docs.opencv.org/3.4/d7/d1b/group__imgproc__misc.html#ggaf8b5832ba85e59fc7a98a2afd034e558a5f8853c1e5a89c4aa2687d1f78a7e550) . |
| bgdModel  | Temporary array for the background model. Do not modify it while you are processing the same image. |
| fgdModel  | Temporary arrays for the foreground model. Do not modify it while you are processing the same image. |
| iterCount | Number of iterations the algorithm should make before returning the result. Note that the result can be refined with further calls with mode==[GC_INIT_WITH_MASK](https://docs.opencv.org/3.4/d7/d1b/group__imgproc__misc.html#ggaf8b5832ba85e59fc7a98a2afd034e558ab01527c7effb50fd1c54d8c4e671ed22) or mode==GC_EVAL . |
| mode      | Operation mode that could be one of the [GrabCutModes](https://docs.opencv.org/3.4/d7/d1b/group__imgproc__misc.html#gaf8b5832ba85e59fc7a98a2afd034e558) |





#### 特征检测

https://www.cnblogs.com/skyfsm/p/7401523.html

一种可行的方法是找出2张图片中的特征点，描述这些特征点的属性，然后比较这两幅图片的特征点的属性。如果有足够多的特征点具有相同的属性

图像的特征点可以简单的理解为图像中比较显著的点，如轮廓点，较暗区域中的亮点，较亮区域中的暗点等

openCV 3.x之后的版本， 各种特征检测调用的方法

```c++
cv::xfeatures2d::SURF
cv::xfeatures2d::SIFT
cv::xfeatures::BriefDescriptorExtractor
cv::xfeatures2d::FREAK
cv::xfeatures2d::StarDetector
```

**SIFT 特征关键点检测**



**SURF特征关键点检测**

必须包含以下头文件

```c++
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace cv::xfeatures2d;
```

使用的例子

```c++
std::vector<KeyPoint> keyPoints_1, keyPoints_2;
int minHessian = 700;
// 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准
Ptr<SURF>detector = SURF::create(minHessian); //智能指针创建surf detector
//【3】调用detect函数检测出SURF特征关键点，保存在vector容器中
detector->detect( image1, keyPoints_1 );

detector->detect( image2, keyPoints_2 );

Mat img_keypoints_1; Mat img_keypoints_2;

//将找到的关键点绘制在img_keypoints_1上
drawKeypoints( image1, keyPoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
drawKeypoints( image2, keyPoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
```

**Fast 特征关键点检测**

比sift, surf都来的快速

```c++
vector<KeyPoint>detectKeyPoint;
Mat keyPointImage1,keyPointImage2;

Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();
fast->detect(srcGrayImage,detectKeyPoint);
drawKeypoints(srcImage,detectKeyPoint,keyPointImage1,Scalar(0,0,255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
drawKeypoints(srcImage,detectKeyPoint,keyPointImage2,Scalar(0,0,255),DrawMatchesFlags::DEFAULT);

imshow("src image",srcImage);
imshow("keyPoint image1",keyPointImage1);
imshow("keyPoint image2",keyPointImage2);
```









**ORB 特征关键点检测**

Oriented Fast and Rotated BRIEF

ORB采用FAST（features from accelerated segment test）算法来检测特征点。FAST**核心思想**就是找出那些卓尔不群的点，即拿一个点跟它周围的点比较，如果它和其中大部分的点都不一样就可以认为它是一个特征点

**FAST具体计算过程：**

1. 从图片中选取一个像素点P，下面我们将判断它是否是一个特征点。我们首先把它的密度（即灰度值）设为Ip。
2. 设定一个合适的阙值t ：当2个点的灰度值之差的绝对值大于t时，我们认为这2个点不相同。
3. 考虑该像素点周围的16个像素。（见上图）
4. 现在如果这16个点中有连续的n个点都和P点不同，那么它就是一个角点。 这里n设定为12。
5. 【个人认为作者这个方法有问题】我们现在提出一个高效的，来快速排除一大部分非特征点的点。该测试仅仅检查在位置1、9、5和13四个位置的像素（首先检查1和9，看它们是否和P点相同。如果是，再检查5和13）。如果是一个角点，那么上述四个像素点中至少有3个应该和P点相同。如果都不满足，那么不可能是一个角点



使用方法



```c++
static Ptr<ORB> cv::ORB::create	(	int 	nfeatures = 500,
float 	scaleFactor = 1.2f,
int 	nlevels = 8,
int 	edgeThreshold = 31,
int 	firstLevel = 0,
int 	WTA_K = 2,
int 	scoreType = ORB::HARRIS_SCORE,
int 	patchSize = 31,
int 	fastThreshold = 20 
)	
```



#### 图像拼接

使用二维特征点(Features2D)和单映射(Homography)寻找已知物体

```c++
Mat cv::findHomography	(	InputArray 	srcPoints,
InputArray 	dstPoints,
int 	method = 0,
double 	ransacReprojThreshold = 3,
OutputArray 	mask = noArray(),
const int 	maxIters = 2000,
const double 	confidence = 0.995 
)	
```

使用函数 [findHomography](http://opencv.willowgarage.com/documentation/cpp/calib3d_camera_calibration_and_3d_reconstruction.html?#findHomography) 寻找匹配上的关键点的变换

- srcPoints	源平面中点的坐标矩阵，可以是CV_32FC2类型，也可以是vector<Point2f>类型
- dstPoints	目标平面中点的坐标矩阵，可以是CV_32FC2类型，也可以是vector<Point2f>类型
- method	计算单应矩阵所使用的方法。不同的方法对应不同的参数，具体如下：
  0 - 利用所有点的常规方法
  RANSAC - RANSAC-基于RANSAC的鲁棒算法
  LMEDS - 最小中值鲁棒算法
  RHO - PROSAC-基于PROSAC的鲁棒算法
- ransacReprojThreshold	
  将点对视为内点的最大允许重投影错误阈值（仅用于RANSAC和RHO方法）。如果

则点被认为是个外点（即错误匹配点对）。若srcPoints和dstPoints是以像素为单位的，则该参数通常设置在1到10的范围内。

- mask	
  可选输出掩码矩阵，通常由鲁棒算法（RANSAC或LMEDS）设置。 请注意，输入掩码矩阵是不需要设置的。
- maxIters	RANSAC算法的最大迭代次数，默认值为2000。
- confidence	可信度值，取值范围为0到1.

------



### 对视频or摄像头读取



#### 对视频or摄像头（webcam）进行读取

```
cv::VideoCapture() 类 
```



VideoCapture构造函数如下

- videoCapture()
- VideoCapture(const String & filename)
- VideoCapture(const String & filename, int apiPreference)
- VideoCapture(int index)



VideoCapture cap(0)  带入0 表示开启默认摄像头

VideoCapture cap("xxxx.mp4") 也可以传入video文件， 也能像下面这样

VideoCapture cap("img_%02d.jpg") 传入图像img_00.jpg, img_01.jpg, img_02.jpg



```c++
VideoCapture cap; //open the default camera
if (videoFile ！= "") //检查命令行参数videoFile 有没有值
  cap.open(videoFile); //有的话， 就打开videoFile
else
  cap.open(0);
if(!cap.isOpened()) //检查是否可以读取视频文件名 or 摄像头
  return -1;

namedWindow("Video", 1);
for (;;)
{
  Mat frame; 
  cap >> frame; // 从摄像头读取帧到frame变量上
  if (frame)//如果有读取到
    imshow("Video", frame);//显示在屏幕上
  if (waitKey(30) >= 0) break;
}

//记得释放掉资源
cap.release();
```



#### 保存视频 VideoWriter

要保存视频需要先创建一个writer实例， 设置好一切的参数

```c++
cv::VideoWriter::VideoWriter
```

VideoWriter主要构造函数如下

```c++
//1
cv::VideoWriter::VideoWriter	(	
  const String & 	filename, 
  int 	fourcc, 
  double 	fps, 
  Size 	frameSize, 
  bool 	isColor = true )

//2  
cv::VideoWriter::VideoWriter	(	const String & 	filename, int 	apiPreference,
int 	fourcc, double 	fps, Size 	frameSize, bool 	isColor = true 
)	
```

- fps：以多大的帧率保存*
- Fourcc ： 四字符code表示压缩帧的方式
  - 可参考 http://www.fourcc.org/codecs.php
- frameSize：图像的大小，size类型
- isColor：是否是彩色图像*

Ex.

```c++
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
 
using namespace cv;
 
void main()
{
	VideoCapture capture(0);
	VideoWriter writer("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));
	Mat frame;
	
	while (capture.isOpened())
	{
		capture >> frame; //读取每一帧, 用法相当于read()
		writer << frame; //保存每一帧， 用法相当于write()
		imshow("video", frame);
		if (cvWaitKey(20) == 27)
		{
			break;
		}
	}
}
```



#### 程序计时

利用opencv自带的模块

```c++
float start = getTickCount(); //计时器
//计时程序

float end = getTickCount();

float last = end-start;

cout << "time consume: " << (last / getTickFrequency() * 1000) << endl;

//getTickFrequency表示CPU的频率，这里用的是opencv版的，*1000可以转换为秒

//总次数/一秒内重复的次数*1000 = 时间(ms) 
//总次数/一秒内重复的次数*1000000 = 时间(s)
```



opencv3.2 自带模块

```
cv::TickMeter
```





```cpp
#include "opencv2/opencv.hpp"

TickMeter tm; //定义timer
timer.start();
// do something ...
timer.stop();
std::cout << timer.getTimeSec();//输出是s
```

getTimeMicro() //返回微秒 us

getTimeMilli() //返回毫秒 ms

getTimeSec() //返回秒 s



#### 计算FPS 并显示在图像

Example

```c++
#include <ctime> //for recored time


long frameCounter = 0;
std::time_t timeBegin = std::time(0);
int tick = 0;
int fps = 0;
cv::Mat frame;

while(true)
{
    cap.read(frame);
    frameCounter++;
    std::time_t timeNow = std::time(0) - timeBegin; //计算时间
    if (timeNow - tick >= 1)
    {
      tick++;
      //            std::cout << "Frames per second: " << frameCounter << std::endl;
      fps = frameCounter;
      frameCounter = 0;
    }
    cv::putText(frame, cv::format("Average FPS=%d",fps),
                cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0,0,255));
    cv::imshow("CSI Camera",frame); 
}
```



------

### 各类型

#### Vec 对象类型

数值向量的模板类， 定义向量的类型和组件的数量

官方预定义的类型

```c++
typedef Vec<unchar, 4> Vec4b;
typedef Vec<int, 2> Vec2i;
typedef Vec<float, 2> Vec2f;
typedef Vec<double, 2> Vec2b;
```

#### Scalar对象类型

由Vec派生的模板类， 用于传递和读取像素值

以下是初始化的方式

```c++
Scalar s0(0); //赋值
Scalar s1(0.0, 1.0, 2.0, 3.0); //赋多值
Scalar s2(s1);//靠另一个值赋予值
```

#### Point 对象类型

主要用来描述2D坐标平面上的点 （x, y)

```c++
typedef Point_<int> Point2i;
typedef POint2i Point;
typedef Point_<float> POint2f;
typedef Point_<double> POint2d;
```

Ex.

```c++
Point pt;
pt.x = 10;
pt.y = 8;

// 或者如下

Point pt =  Point(10, 8);
```



#### Size对象类型

通常用于指定图像或矩形大小， 这个类添加了两个成员 width 和 height， 以及area()函数

```c++
Size s(100, 100);
Mat img = Mat::zeros(s, CV_8UC1); // 100 x 100 单通道matrix
s.width = 200;
int area = s.area(); //returns 100x200
```

#### Rect 对象

可以用来定义ROI（region of interest, 简称ROI)

`Rect_(_Tp _x, _Tp _y, _Tp _width, _Tp _height)`

定义一个左上角点坐标为`(_x, _y)`， `_width*_height`矩形的宽和高

```c++
Mat img = imread("lena,jpg");
Rect rect_roi(0, 0, 100, 100);
Mat img_roi = img(r); //原图 从左上x:0 y:0的位置 取height, width = 100进行剪裁
```









------

### API

#### namedWindows()

```c++
void namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE )
```

**name** – window的名字， 也可用来辨别是否为同一个视窗

**flags** –Flags of the window. The supported flags are:

​	- WINDOW_NORMAL ： 如果设定为这个， 则user可以自行resize window

​	- WINDOW_AUTOSIZE ： 如果设定这个， user不能自己resize window， 会自动的调整成要display的图像一样

​	- WINDOW_OPENGL  如果设定这个， 则可以support openGL

#### convertTo()  转换数据类型

```c++
void convertTo( OutputArray m, int rtype, double alpha=1, double beta=0 ) const
```



把一个矩阵从一种数据类型转换到另一种数据类型，同时可以带上缩放因子和增量，公式如下：

```cpp
m(x,y) = saturate_cast<rType>(alpha * (*this) (x,y) + beta);
```

> m       – 目标矩阵。如果m在运算前没有合适的尺寸或类型，将被重新分配。
>
> rtype – 目标矩阵的类型。因为目标矩阵的通道数与源矩阵一样，所以rtype也可以看做是目标矩阵的位深度。如果rtype为负值，目标矩阵和源矩阵将使用同样的类型。
>
> alpha – 尺度变换因子（可选）。默认值是1。即把原矩阵中的每一个元素都乘以alpha。
>
> beta   – 附加到尺度变换后的值上的偏移量（可选）。默认值是0。即把原矩阵中的每一个元素都乘以alpha，再加上beta。



#### cv::putText()

将编辑好的文字放在图像img上

```c++
void cv::putText (intputoutputarray img, const String & text, Point org, int fontFace,o double fontscale, Scalar color, int thickness = 1, int lineType = LINE_8,  bool bottomLeftOrigin = false)
```

- img : Image.
- text: Text string to be drawn.
- org : Bottom-left corner of the text string in the image.
- fontFace : Font type, see [HersheyFonts](https://docs.opencv.org/3.4/d0/de1/group__core.html#ga0f9314ea6e35f99bb23f29567fc16e11).
- fontScale : Font scale factor that is multiplied by the font-specific base size.
- color : Text color.
- thickness : Thickness of the lines used to draw a text.
- lineType: Line type. See [LineTypes](https://docs.opencv.org/3.4/d0/de1/group__core.html#gaf076ef45de481ac96e0ab3dc2c29a777)
- bottomLeftOrigin : When true, the image data origin is at the bottom-left corner. Otherwise, it is at the top-left corner.

#### cv::getTextSize() 

```c++
Size cv::getTextSize(const String & text, int fontFace, double fontScale, int thickness, int * baseLine)
```

输入传入的text以及给定的字体大小等 计算出需要的长度和宽度

- text 输入的文本
- fontFace 是字体类型
- fontScale 字体大小
- thickness字体粗细
- BaseLine 文字最底部y坐标



Example

```c++
String text = "Funny text inside the box";
int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
double fontScale = 2;
int thickness = 3;
Mat img(600, 800, CV_8UC3, Scalar::all(0));
int baseline=0;
Size textSize = getTextSize(text, fontFace,
                            fontScale, thickness, &baseline);
baseline += thickness;
// center the text
Point textOrg((img.cols - textSize.width)/2,
              (img.rows + textSize.height)/2);
// draw the box
rectangle(img, textOrg + Point(0, baseline),
          textOrg + Point(textSize.width, -textSize.height),
          Scalar(0,0,255));
// ... and the baseline first
line(img, textOrg + Point(0, thickness),
     textOrg + Point(textSize.width, thickness),
     Scalar(0, 0, 255));
// then put the text itself
putText(img, text, textOrg, fontFace, fontScale,
        Scalar::all(255), thickness, 8);
```



#### cv::rectangle() 绘制矩形

Void cv::rectangle(inputoutputarray img, Point pt1, Point2 pt2, const Scalar & color, int thickness = -1, int lineType = LINE_8, int shift = 0)

- Img ： image
- pt1 : 左上坐标点
- pt2 : 右下坐标点
- color : 框的颜色
- thickness ：框的厚度
- lineType：线条样式
- Shift ： 几乎不用， 默认为0









------



### CMakeLists.txt 编写



情况

```
Hello 文件夹
├── CMakeLists.txt
├── cmake-build-debug
├── main.cpp
└── src
```



CMakeLists.txt 编写范例

```cmake
cmake_minimum_required(VERSION 3.15)
project(Hello)


set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
message("OpenCV version: " ${OpenCV_VERSION})
#openCV
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

#set source file
set(src main.cpp)


add_executable(${PROJECT_NAME} ${src})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
```







------



### Gstreamer



#### CSI camera 开启webcam方式

代码参考 [https://github.com/JetsonHacksNano/CSI-Camera/blob/master/simple_camera.cpp](https://github.com/JetsonHacksNano/CSI-Camera/blob/master/simple_camera.cpp)

Example

```c++
// #include <iostream>
#include <opencv2/opencv.hpp>
// #include <opencv2/videoio.hpp>
// #include <opencv2/highgui.hpp>

std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main()
{
    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;

    std::string pipeline = gstreamer_pipeline(capture_width,
	capture_height,
	display_width,
	display_height,
	framerate,
	flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";
 
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if(!cap.isOpened()) {
	std::cout<<"Failed to open camera."<<std::endl;
	return (-1);
    }

    cv::namedWindow("CSI Camera", cv::WINDOW_AUTOSIZE);
    cv::Mat img;

    std::cout << "Hit ESC to exit" << "\n" ;
    while(true)
    {
    	if (!cap.read(img)) {
		std::cout<<"Capture read error"<<std::endl;
		break;
	}
	
	cv::imshow("CSI Camera",img);
	int keycode = cv::waitKey(30) & 0xff ; 
        if (keycode == 27) break ;
    }

    cap.release();
    cv::destroyAllWindows() ;
    return 0;
}

```

#### CSI camera Video Write的方式

```C++
cv::VideoWriter writer;
    writer.open("appsrc ! autovideoconvert ! omxh265enc ! matroskamux ! filesink location=test.mkv ", 0, (double)25, cv::Size(1024, 1024), true);
```







#### 问题合集



**问题** execute:532 Failed to create CaptureSession CSI摄像头无法正常开启, 需要reboot 设备才行

**原因** 应该是前面使用的gstreamer未正常关闭or释放

**解决** 

python version

```python
def gstreamer_auto(self):
return ('nvarguscamerasrc ! '
'video/x-raw(memory:NVMM), format=NV12, '
'width=3280, height=2464, '
'framerate=10/1 ! '
'nvvidconv flip-method=2 ! '
'video/x-raw, format=I420 ! '
'appsink max-buffers=1 drop=True ')
```

c++ version 

```c++
std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink max-buffers=1 drop=True ";
}
```



参考https://devtalk.nvidia.com/default/topic/1066047/jetson-nano/how-to-free-restart-the-gstreamer-nvarguscamerasrc-module/



**问题**

OpenCV Error: Unsupported format or combination of formats (cvWriteFrame() needs images with depth = IPL_DEPTH_8U and nChannels = 3.) in CvVideoWriter_GStreamer::writerFrame

**原因** 

需要将图像进行类型转换利用 convertTo(), 类型为

**解决**

https://devtalk.nvidia.com/default/topic/985594/general-graphics-programming/how-to-write-video-frames-from-visionworks-to-gstreamer-pipe/



#### info

[jetson Nano GStreamer example pipelines for H264 H265 and VP8 decoding](https://developer.ridgerun.com/wiki/index.php?title=Jetson_Nano/Gstreamer/Example_Pipelines/Decoding)

------

### 其他



随机产生数字Random Number Generator

cv::RNG 类

https://docs.opencv.org/master/d1/dd6/classcv_1_1RNG.html#details



randomColor



### CommandLineParser 管理命令行参数

主要先在常量char向量中定义需要或允许的参数

```
const char* keys = 
{
	"{help h usage ? | | print this message}" #定义help参数
	"{@video | | Video file, if not defined try to use webcamera}"
}

#格式依照如下
"{name_param | default_value | description}"
name_param 可以@开头， 将参数定义为默认输入


CommnadLineParser parser(argc, argv, keys);
```



**问题**

OpenCV Error: Assertion failed (scn == 3 || scn == 4) in cv::cvtColor

说明cvtColor声明失败



#### 图像元素类型

```
Type:类型 CV_[位数][带符号与否][类型前缀][通道数]
例:CV_8UC3表示使用8位的unsighed char类型.每个像素由三个元素组成的三通道.
CV_64FC1 F表示float channel = 1

类型汇总:
CV_8U  (8 bit 无符号整形0~255) CV_8UC1 (1通道)  CV_8UC2 (2通道)  CV_8UC3 (3通道)  CV_8UC4(4通道) 
CV_8S   (8 bit有符号整形-128~127)
CV_8SC1 (1通道)  CV_8SC2 (2通道)   CV_8SC3 (3通道)  CV_8SC4 (4通道)   

CV_16U  (16 bit 无符号整形0~65535)
CV_16UC1 (1通道)  CV_16UC2 (2通道)   CV_16UC3 (3通道)   CV_16UC4 (4通道)   

CV_16S  (16 bit 有符号整形-32768~32767)
CV_16SC1(1通道)   CV_16SC2(2通道)   CV_16SC3(3通道)   CV_16SC4(4通道)   

CV_32S  (32 bit 有符号整形-2147483648~2147483647)
CV_32SC1   CV_32SC2    CV_32SC3  CV_32SC4   

CV_32F  (32 bit 浮点)
CV_32FC1   CV_32FC2  CV_32FC3   CV_32FC4  

CV_64F   (64 bit 浮点)
CV_64FC1   CV_64FC2  CV_64FC3  CV_64FC4  
```



------

### 参考资料



待编辑
