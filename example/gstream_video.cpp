
// #include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>

// #include <opencv2/videoio.hpp>
// #include <opencv2/highgui.hpp>

std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink max-buffers=1 drop=True ";
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

    std::cout << "Hit ESC to exit" << "\n" ;
    long frameCounter = 0;
    std::time_t timeBegin = std::time(0);
    int tick = 0;
    int fps = 0;
    cv::Mat frame;
    cv::Mat output;


    ///save to disk 定义writer
    cv::VideoWriter writer;
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    writer.open("appsrc ! autovideoconvert ! omxh264enc ! matroskamux ! filesink location=test.mp4 ", codec, (double)25, cv::Size(1280, 720), true);

    if (!writer.isOpened()) {
        std::cout << "Could not open the output video file for write\n";
        return -1;
    }


    while(true)
    {

        cap.read(frame);
        if (!cap.read(frame)) {
            std::cout<<"Capture read error"<<std::endl;
            break;
        }



        frameCounter++;
        std::time_t timeNow = std::time(0) - timeBegin;
        if (timeNow - tick >= 1)
        {
            tick++;
            fps = frameCounter;
            frameCounter = 0;
        }
        cv::putText(frame, cv::format("Average FPS=%d",fps),
                    cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0,0,255));

        frame.convertTo(output, CV_8UC3);
        writer.write(output);
        cv::imshow("CSI Camera",frame);
        int keycode = cv::waitKey(30) & 0xff ;
        if (keycode == 27) break ;
    }

    cap.release();
    cv::destroyAllWindows() ;
    return 0;
}

