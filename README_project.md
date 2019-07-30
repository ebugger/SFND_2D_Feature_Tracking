# Main routine

1. In the main() in MidTermProject_Camera_Student.cpp
line30-38
```
    string detectorType;
    string descriptorType;
    //BRISK,BRIEF, ORB, FREAK, AKAZE are binary hamming class descriptors(type=0,CV_8U),others are float descriptor(type=5  CV_32F)
    std::vector<std::string> detectorT = { "SHITOMASI", "FAST", "HARRIS", "BRISK", "ORB", "SIFT","AKAZE"};//"SHITOMASI", "FAST", "HARRIS", "BRISK", "ORB", "SIFT","AKAZE" 
    std::vector<std::string> descriptorT = {"BRISK", "BRIEF", "ORB", "FREAK", "SIFT","AKAZE"};//"BRISK", "BRIEF", "ORB", "FREAK", "SIFT","AKAZE",
    for(auto it=detectorT.begin();it!=detectorT.end();++it) {
        for(auto ij=descriptorT.begin();ij!=descriptorT.end();++ij) {
            detectorType = *it;
            descriptorType = *ij;
```            
we make a nested for loop to make all possible combination of detector and descriptor and then run detect, compute and match method to track object

2.In matching2D_Student.cpp, Line 22 to switch BF match norm method by the descriptor type
```
int normType = descSource.type() == 0 ? cv::NORM_HAMMING : cv::NORM_L2;
```

3.In the main() in MidTermProject_Camera_Student.cpp

we initial 3 variable for logging process time(detector and extractor), number of matched points, neibhour distance, all will be write to a file called summary.csv 
```
    double total_time = 0;
    static float toal_dis = 0;
    static int total_matched = 0;
```
we pass total_time to both detector and extractor to update the total time for processing all 10 images.

Line180-185,compute the neighbour distance for the KeyPoints
```
                for (auto it=keypoints.begin();it!=keypoints.end();++it){
                    for (auto ij=it+1;ij!=keypoints.end();++ij){
                        float temp_dis = std::sqrt(std::pow((it->pt.x - ij->pt.x), 2) + std::pow((it->pt.y - ij->pt.y), 2));
                        toal_dis += temp_dis;
                    }           
                }
```
## Task MP.1
```
                DataFrame frame;
                frame.cameraImg = imgGray;
                if(dataBuffer.size() == dataBufferSize) {
                    dataBuffer.erase(dataBuffer.begin());
                }       
                dataBuffer.push_back(frame);
```
Line81 -86 in 'matching2D_student.cpp' will check if the buffer size is equal to 2, if so, we will remove the front element of the buffer and then add new one to the back.


## TASK MP.2
```
                if (detectorType.compare("SHITOMASI") == 0)
                {
                    detKeypointsShiTomasi(keypoints, imgGray, false, total_time);
                }
```                
Line101-128 in 'matching2D_student.cpp'  to check the detectorType string and run the related detector, we also pass the total_time variable to log the process time

in the body of detKeypointsModern() function in matching2D_Student.cpp line183-209 is the process of NMS for HARRIS detector. All other detector is created in related if statment.

## TASK MP.3

Line142-157 in 'matching2D_student.cpp' use cv::Rect.contains method to filter the points inside the cv::Rect Box.also the number of KeyPoints is logged.

## TASK MP.4

in the body of descKeypoints() function in matching2D_Student.cpp, Line67-122 we define every descriptor in the if...else if statment.

## TASK MP.5

Line28-40 in matching2D_Student.cpp we first to check the data type of the descriptor and convert it to CV_32F if is not. then we create FALNN descriptor.

## TASK MP.6

Line47-62 in matching2D_Student.cpp is the implementation of KNN with k =2,Line55-60 we check the distance ratio between the 2 neariest neibhourh and keep the first if the distance to the second is below the threshold.

## TASK MP.7
we pass the variable "total_time" from the main to detKeypointsModern, detKeypointsShiTomasi and descKeypoints function and update/add it after processing it.such as:
```
total_time += 1000 * t / 1.0;
```
in all of the detector and descriptor call.

## TASK MP.8

Line213 , Line215 in MidTermProject_Camera_Student.cpp we set to use BF approach and KNN with k=2.

Line233 , we sum up the size of matched points in all the images as the number of matched keypoints. 
```
total_matched += matches.size();
```

Line25,26,266,273 to log the detector name, with descriptor, total process time, number of matched keypoints to a comma separated excel file "summary.csv" 
```
            ofstream MyExcelFile;
            MyExcelFile.open("./summary.csv");
            MyExcelFile << "Detector, Extractor, Process Time,neibhour diatance, n_matched, descriptor_dtype, des_norm" << endl;
            MyExcelFile << detectorType <<","<< descriptorType<<","<<total_time<<","<< total_matched<<","<< toal_dis<<"," <<des_type <<","<<d_norm<< std::endl;
            MyExcelFile.close();
