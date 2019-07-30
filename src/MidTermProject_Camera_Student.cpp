/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{   
    ofstream MyExcelFile;
    MyExcelFile.open("./test.csv");
    MyExcelFile << "Detector, Extractor, Process Time, NN_dis, n_matched, descriptor_dtype, des_norm" << endl;
    double total_time = 0;
    static float toal_dis = 0;
    static int total_matched = 0;
    string detectorType;
    string descriptorType;
    //BRISK,BRIEF, ORB, FREAK, AKAZE are binary hamming class descriptors(type=0,CV_8U),others are euclid descriptor(type=5  CV_32F)
    std::vector<std::string> detectorT = { "SHITOMASI", "FAST", "HARRIS", "BRISK", "ORB", "SIFT","AKAZE"};//"SHITOMASI", "FAST", "HARRIS", "BRISK", "ORB", "SIFT","AKAZE" 
    std::vector<std::string> descriptorT = {"BRISK", "BRIEF", "ORB", "FREAK", "SIFT","AKAZE"};//"BRISK", "BRIEF", "ORB", "FREAK", "SIFT","AKAZE",
    for(auto it=detectorT.begin();it!=detectorT.end();++it) {
        for(auto ij=descriptorT.begin();ij!=descriptorT.end();++ij) {
            detectorType = *it;
            descriptorType = *ij;


            /* INIT VARIABLES AND DATA STRUCTURES */
            int des_type =0;
            int d_norm = 0;
            // data location
            string dataPath = "../";

            // camera
            string imgBasePath = dataPath + "images/";
            string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
            string imgFileType = ".png";
            int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
            int imgEndIndex = 9;   // last file index to load
            int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

            // misc
            int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
            vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
            bool bVis = false;            // visualize results

            /* MAIN LOOP OVER ALL IMAGES */

            for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
            {
                /* LOAD IMAGE INTO BUFFER */

                // assemble filenames for current index
                ostringstream imgNumber;
                imgNumber << setfill('0') << setw(imgFillWidth) << imgStartIndex + imgIndex;
                string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;
                //std::cout<<imgFullFilename<<endl;

                // load image from file and convert to grayscale
                cv::Mat img, imgGray;
                img = cv::imread(imgFullFilename);
                cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

                //// STUDENT ASSIGNMENT
                //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize
                //cout<< "Buffer size: " << dataBuffer.size() << endl;
                // push image into data frame buffer
                DataFrame frame;
                frame.cameraImg = imgGray;
                if(dataBuffer.size() == dataBufferSize) {
                    dataBuffer.erase(dataBuffer.begin());
                }       
                dataBuffer.push_back(frame);

                //// EOF STUDENT ASSIGNMENT
                cout << "#1 : LOAD IMAGE INTO BUFFER done" << endl;

                /* DETECT IMAGE KEYPOINTS */

                // extract 2D keypoints from current image
                vector<cv::KeyPoint> keypoints = {}; // create empty feature list for current image
                //string detectorType = "SHITOMASI";

                //// STUDENT ASSIGNMENT
                //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
                //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT

                if (detectorType.compare("SHITOMASI") == 0)
                {
                    detKeypointsShiTomasi(keypoints, imgGray, false, total_time);
                }
                else if(detectorType.compare("FAST") == 0)
                {
                    detKeypointsModern(keypoints, imgGray, "FAST", false, total_time);
                }
                else if(detectorType.compare("HARRIS") == 0)
                {
                    detKeypointsModern(keypoints, imgGray, "HARRIS", false, total_time);
                }
                else if(detectorType.compare("BRISK") == 0)
                {
                    detKeypointsModern(keypoints, imgGray, "BRISK", false, total_time);
                }
                else if(detectorType.compare("ORB") == 0)
                {
                    detKeypointsModern(keypoints, imgGray, "ORB", false, total_time);
                }
                else if(detectorType.compare("AKAZE") == 0)
                {
                    detKeypointsModern(keypoints, imgGray, "AKAZE", false, total_time);
                }
                else if(detectorType.compare("SIFT") == 0)
                {
                    detKeypointsModern(keypoints, imgGray, "SIFT", false, total_time);
                }
                //else
                //{
                //    cout<< "No detect type matches";
                //   exit(1);
                //}
                //// EOF STUDENT ASSIGNMENT

                //// STUDENT ASSIGNMENT
                //// TASK MP.3 -> only keep keypoints on the preceding vehicle

                // only keep keypoints on the preceding vehicle
                bool bFocusOnVehicle = true; 
                cv::Rect vehicleRect(535, 180, 180, 150);
                if (bFocusOnVehicle)
                {   
                    int count = 0;
                    cv::KeyPoint roi_point; 
                    std::vector<cv::KeyPoint> roi_kpts;
                    for (auto it = keypoints.begin(); it != keypoints.end();++it) {
                        if(vehicleRect.contains(it->pt)) {
                            //contains return pt.x >= x && pt.x < x + width && pt.y >= y && pt.y < y + height;
                            //keypoints.erase(it);  !!! not work
                            roi_point.pt = cv::Point2f(it->pt);
                            roi_point.size = it->size;
                            roi_point.response = it->response;
                            roi_kpts.push_back(roi_point);
                            count++;
                        }
                    }
                    cout<<"Rect filtered: " << count << " Points"<< endl;
                    keypoints = roi_kpts;
                }

                //// EOF STUDENT ASSIGNMENT

                // optional : limit number of keypoints (helpful for debugging and learning)
                bool bLimitKpts = false;
                if (bLimitKpts)
                {
                    int maxKeypoints = 50;

                    if (detectorType.compare("SHITOMASI") == 0)
                    { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                        keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
                    }
                    cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
                    cout << " NOTE: Keypoints have been limited!" << endl;
                }
                cout<<"# of kpt in ROI Rect: " << keypoints.size() << endl;

                // distance for between of all the keypoints; Task MP.7
                for (auto it=keypoints.begin();it!=keypoints.end();++it){
                    for (auto ij=it+1;ij!=keypoints.end();++ij){
                        float temp_dis = std::sqrt(std::pow((it->pt.x - ij->pt.x), 2) + std::pow((it->pt.y - ij->pt.y), 2));
                        toal_dis += temp_dis;
                    }           
                }

                // push keypoints and descriptor for current frame to end of data buffer
                (dataBuffer.end() - 1)->keypoints = keypoints;
                cout << "#2 : DETECT KEYPOINTS done" << endl;

                /* EXTRACT KEYPOINT DESCRIPTORS */

                //// STUDENT ASSIGNMENT
                //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
                //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

                cv::Mat descriptors;
                //string descriptorType = "BRISK"; // BRIEF, ORB, FREAK, AKAZE, SIFT
                descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType, total_time, des_type, d_norm);
                //// EOF STUDENT ASSIGNMENT

                // push descriptors for current frame to end of data buffer
                (dataBuffer.end() - 1)->descriptors = descriptors;

                cout << "#3 : EXTRACT DESCRIPTORS done" << endl;

                if (dataBuffer.size() > 1) // wait until at least two images have been processed
                {

                    /* MATCH KEYPOINT DESCRIPTORS */

                    vector<cv::DMatch> matches;
                    string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN
                    //string descriptorType = "DES_BINARY"; // DES_BINARY, DES_HOG
                    string selectorType = "SEL_KNN";       // SEL_NN, SEL_KNN

                    //// STUDENT ASSIGNMENT
                    //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
                    //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp

                    matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                                    (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                                    matches, /* descriptorType,*/ matcherType, selectorType);

                    //// EOF STUDENT ASSIGNMENT

                    // store matches in current data frame
                    (dataBuffer.end() - 1)->kptMatches = matches;

                    //Task MP.7 count the matches number

                    //std::cout<<"# of matched KeyPoints is: " << matches.size()<< endl;
                    total_matched += matches.size();
                    cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << endl;

                    // visualize matches between current and previous image
                    bVis = false;
                    if (bVis)
                    {
                        cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                        cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                        (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                        matches, matchImg,
                                        cv::Scalar::all(-1), cv::Scalar::all(-1),
                                        vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                        string windowName = "Matching keypoints between two camera images";
                        cv::namedWindow(windowName, 7);
                        cv::imshow(windowName, matchImg);
                        cout << "Press key to continue to next image" << endl;
                        cv::waitKey(0); // wait for key to be pressed
                    }
                    bVis = false;
                }
            

            } // eof loop over all images
            std::cout<< "Detect and Extractor time: " << total_time << endl;
            std::cout<<"SSD of the keypoints are: " << toal_dis << std::endl;
            std::cout<<"# of matched KeyPoints is: " << total_matched<< endl;


            
            //write summary(time/ssd/n_matched) to excel

            MyExcelFile << detectorType <<","<< descriptorType<<","<<total_time<<","<< toal_dis<<","<< total_matched<<"," <<des_type <<","<<d_norm<< std::endl;
            total_time = 0;
            toal_dis = 0;
            total_matched = 0;    
    
        }
    }
    MyExcelFile.close();
    return 0;
}
