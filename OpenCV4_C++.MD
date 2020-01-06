<h1 align="center">OpenCV4 C++</h1>

为何编写该笔记， 因为网上各种博文写的太垃圾， 于是自己写一份人人都能迅速理解的笔记， 免费供大家查阅

<h5 align='right' > update 2020.1.6</h5>

> ### 目录
>
> 1. 基本
> 2. 加载图像
> 3. 对视频or摄像头读取
> 4. 各类型(Vec, Scalar, Point, Size, Rect)
> 5. API
>    - 目录待编辑***
>
> 6. CMakeLists.txt 编写
>
> 7. others
>    - 目录待编辑***









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



#### cv::VideoCapture() 类 读取视频or读取摄像头画面

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
Mat img_roi = img(r); //原图 从左上x:0 y:0的位置 取height, width = 100进行剪裁
```









------

> <h3 align="center" id="">API</h3>

#### convertTo()

void convertTo( OutputArray m, int rtype, double alpha=1, double beta=0 ) const

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

void cv::putText (intputoutputarray img, const String & text, Point org, int fontFace,o double fontscale, Scalar color, int thickness = 1, int lineType = LINE_8,  bool bottomLeftOrigin = false)





#### cv::getTextSize() 

Size cv::getTextSize(const String & text, int fontFace, double fontScale, int thickness, int * baseLine)

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

