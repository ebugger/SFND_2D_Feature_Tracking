##

Point2f(x,y)
```
template<typename _Tp> inline
Point_<_Tp>::Point_()
    : x(0), y(0) {}
```

KeyPoint:
```
inline
KeyPoint::KeyPoint(Point2f _pt, float _size, float _angle, float _response, int _octave, int _class_id)
    : pt(_pt), size(_size), angle(_angle), response(_response), octave(_octave), class_id(_class_id) {}
```

DMatch:
```
inline
DMatch::DMatch(int _queryIdx, int _trainIdx, float _distance)
    : queryIdx(_queryIdx), trainIdx(_trainIdx), imgIdx(-1), distance(_distance) {}
```



## Manipulating Matrices

```
    for (int r = 230; r < 250; r++)
    {
        //loop over all columns and set matrix elements to 255
        for (int c=0;c<m1_8u.cols;c++) {
            m1_8u.at<unsigned char>(r, c) = 255;
        }

    }
```

## Loading sequences images
```
    std::vector<cv::Mat> imgList;
    for(int i=5;i<=7;i++) {
        //string cnncatenation
        ostringstream imgNumber; //include sstream
        imgNumber << setfill('0') << setw(5) <<i; //include iomanip, total width is 5
        string fileName = "./img" + imgNumber.str() + ".png";

        cv::Mat img;
        img =cv::imread(fileName);
        imgList.push_back(img);
    }
```
It is important to handle large amounts of data in a smart way so that images and other structures are not needlessly copied
```
    for (auto it = imgList.begin(); it != imgList.end();it++) { //auto == vector<cv::Mat>::iterator

        cv::imshow(windowname, *it);
        cv::waitKey(0); 
```
## 
