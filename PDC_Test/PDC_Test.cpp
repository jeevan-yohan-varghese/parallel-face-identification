//C:/Users/jeeva/Videos/anitta_chechi.mp4
//C:/Users/jeeva/Downloads/testvideo.mp4
#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>
#include <chrono>
using namespace std::chrono;


using namespace std;
using namespace cv;


int main(int argc, char** argv) {
    steady_clock::time_point begin = std::chrono::steady_clock::now();
    VideoCapture cap("C:/Users/jeeva/Downloads/testvideo6.mp4");
    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_default.xml");

#pragma omp parallel
    {
        Mat frame, gray;
        vector<Rect> faces;

        while (true) {
#pragma omp single
            {
                if (!cap.read(frame))
                    break;

                cvtColor(frame, gray, COLOR_BGR2GRAY);
                face_cascade.detectMultiScale(gray, faces, 1.3, 5);
            }

#pragma omp for
            for (size_t i = 0; i < faces.size(); i++) {
                rectangle(frame, faces[i], Scalar(0, 0, 255), 2);
                steady_clock::time_point now = std::chrono::steady_clock::now();
                duration<double> time_span = duration_cast<duration<double>>(now - begin);
                std::cout << "Face detected at " << time_span.count() << " seconds." << std::endl;
                Mat face = frame(faces[i]);
                std::string filename = "exports/face_"  + std::to_string(i) + ".jpg";
                imwrite(filename, face);
            
            }

#pragma omp single
            {
                imshow("Face Detection", frame);
                if (waitKey(10) == 27) break;
            }
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
