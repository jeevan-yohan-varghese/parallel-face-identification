//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <omp.h>
//
//using namespace cv;
//
//int main(int argc, char** argv)
//{
//    // Load the given photo
//    Mat referenceImage = imread("C:/Users/jeeva/Downloads/reference.png", IMREAD_GRAYSCALE);
//    if (referenceImage.empty())
//    {
//        std::cerr << "Failed to read reference image" << std::endl;
//        return -1;
//    }
//
//    // Train the face detector using the reference image
//    CascadeClassifier faceDetector;
//    faceDetector.load("haarcascade_frontalface_default.xml");
//    std::vector<Rect> faces;
//    faceDetector.detectMultiScale(referenceImage, faces);
//
//    if (faces.empty())
//    {
//        std::cerr << "Failed to train face detector" << std::endl;
//        return -1;
//    }
//
//    // Open the video stream
//    VideoCapture cap("C:/Users/jeeva/Downloads/testvideo.mp4");
//    if (!cap.isOpened())
//    {
//        std::cerr << "Failed to open video stream" << std::endl;
//        return -1;
//    }
//
//    // Process each frame to detect faces
//    Mat frame, gray;
//    double fps = cap.get(CAP_PROP_FPS);
//    double frameCount = cap.get(CAP_PROP_FRAME_COUNT);
//    double durationInSeconds = frameCount / fps;
//
//#pragma omp parallel
//    {
//        while (true)
//        {
//#pragma omp single
//            {
//                bool success = cap.read(frame);
//                if (!success)
//                {
//                    break;
//                }
//
//                cvtColor(frame, gray, COLOR_BGR2GRAY);
//            }
//
//            std::vector<Rect> facesInFrame;
//            faceDetector.detectMultiScale(gray, facesInFrame);
//
//#pragma omp critical
//            {
//                // For each detected face, check if it matches the given photo
//                for (const Rect& face : facesInFrame)
//                {
//                    Mat detectedFace = gray(face);
//                    if (detectedFace.cols == referenceImage.cols &&
//                        detectedFace.rows == referenceImage.rows)
//                    {
//                        Mat difference;
//                        absdiff(referenceImage, detectedFace, difference);
//                        double similarity = 1 - (double)countNonZero(difference) / (referenceImage.cols * referenceImage.rows);
//
//                        if (similarity > 0.9)
//                        {
//                            // If a match is found, print the timestamp at which the face was detected
//                            int frameIndex = cap.get(CAP_PROP_POS_FRAMES);
//                            double timestampInSeconds = frameIndex / fps;
//                            std::cout << "Face detected at timestamp " << timestampInSeconds << std::endl;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    cap.release();
//
//    return 0;
//}
