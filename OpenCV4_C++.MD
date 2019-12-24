<h1 align="center">OpenCV 4 C++</h1>

<h5 align='right' > update 2019.12.24</h5>

> ### 目录
>
> 1. 基本
> 2. 加载图像
> 3. 对视频or摄像头读取
> 4. 各类型(Vec, Scalar, Point, Size, Rect)
>
> CMakeLists.txt 编写









> <h3 align="center" id="">基本</h3>

图像是以矩阵格式来存储, OpenCV用Mat类来达到存储目的



如下公式可以访问任何像素

Value = Row_i x num_cols x num_channels + Col_i + channel_i





> <h3 align="center" id="">加载图像</h3>

```c++
Mat color = imread("test.jpg"); //读取为彩色图像

Mat gray = imread("test.jpg", CV_LOAD_IMAGE_GRAYSCALE); //指定读取为灰度图
```



访问图像的行或者列

```c++
int MyRaw = color.cols-1;
int MyCol = color.rows-1;
```



访问图像中的某个像素

```c++
//cv::Mat::at<typename>(row, col)
Vec3b pixel = color.at<Vec3b>(myRow, myCol);
cout << "Pixel value (B, G, R): (" << (int)pixel[0] << ", " << (int)pixel[1] << ", " << (int)pixel[2]<<")" << endl;
```

8位彩色图像的类型是Vec3b （Vec = 向量， 3 = 组件数， b = 一个字节）



展示图像

```C++
imshow("Test_bgr", color);
imshow("Test_gray", gray);
waitkey(0); 
```

waitkey表示等待用户按下某个键就关闭窗口， 0表示任何键



resize图像

`cv2.resize(src, dsize[, dst[, fx[, fy[, interpolation]]]]) → dst`



创造一个空白图像 fill with zeros

```
cv::Mat::zeros()
```



将mat的内容copy到mat2

```
mat.copyTo(mat2)
```







将图像通道分类及合并 cv::split / cv::merge

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





> <h3 align="center" id="">对视频or摄像头读取</h3>

主要是用VideoCapture 类

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





------

> <h3 align="center" id="">各类型</h3>

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

```c++
typedef Point_<int> Point2i;
typedef POint2i Point;
typedef Point_<float> POint2f;
typedef Point_<double> POint2d;
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
Mat img_roi = img(r);
```



> <h3 align="center" id="">CMakeLists.txt 编写</h3>



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







> <h3 align="center" id="">其他</h3>





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



