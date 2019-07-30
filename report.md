| Detector  |  Extractor |  Process Time(ms) |  NN\_distance(SSD)   |  matched\_number |  descriptor\_dtype |  des\_norm |
|-----------|------------|---------------|------------|-------------|--------------------|------------|
| SHITOMASI | BRISK      | 197\.325      | 5\.54E\+06 | 767         | 0                  | 6          |
| SHITOMASI | BRIEF      | 166\.549      | 5\.54E\+06 | 944         | 0                  | 6          |
| SHITOMASI | ORB        | 172\.071      | 5\.54E\+06 | 908         | 0                  | 6          |
| SHITOMASI | FREAK      | 876\.224      | 5\.54E\+06 | 768         | 0                  | 6          |
| SHITOMASI | SIFT       | 303\.293      | 5\.54E\+06 | 927         | 5                  | 4          |
| SHITOMASI | AKAZE      | 2043\.57      | 5\.54E\+06 | 9213        | 0                  | 6          |
| FAST      | BRISK      | 41\.5455      | 8\.21E\+06 | 899         | 0                  | 6          |
| FAST      | BRIEF      | 22\.1156      | 8\.21E\+06 | 1099        | 0                  | 6          |
| FAST      | ORB        | 34\.0921      | 8\.21E\+06 | 1071        | 0                  | 6          |
| FAST      | FREAK      | 780\.605      | 8\.21E\+06 | 878         | 0                  | 6          |
| FAST      | SIFT       | 215\.767      | 8\.21E\+06 | 1046        | 5                  | 4          |
| FAST      | AKAZE      | 2071\.1       | 8\.21E\+06 | 9213        | 0                  | 6          |
| HARRIS    | BRISK      | 135\.453      | 2\.24E\+05 | 142         | 0                  | 6          |
| HARRIS    | BRIEF      | 122\.941      | 2\.24E\+05 | 173         | 0                  | 6          |
| HARRIS    | ORB        | 135\.141      | 2\.24E\+05 | 162         | 0                  | 6          |
| HARRIS    | FREAK      | 868\.867      | 2\.24E\+05 | 144         | 0                  | 6          |
| HARRIS    | SIFT       | 311\.499      | 2\.24E\+05 | 163         | 5                  | 4          |
| HARRIS    | AKAZE      | 2123\.19      | 2\.24E\+05 | 9213        | 0                  | 6          |
| BRISK     | BRISK      | 430\.001      | 2\.89E\+07 | 1570        | 0                  | 6          |
| BRISK     | BRIEF      | 375\.051      | 2\.89E\+07 | 1704        | 0                  | 6          |
| BRISK     | ORB        | 380\.707      | 2\.89E\+07 | 1675        | 0                  | 6          |
| BRISK     | FREAK      | 1144\.32      | 2\.89E\+07 | 1524        | 0                  | 6          |
| BRISK     | SIFT       | 1108\.47      | 2\.89E\+07 | 1747        | 5                  | 4          |
| BRISK     | AKAZE      | 2279\.48      | 2\.89E\+07 | 9213        | 0                  | 6          |
| ORB       | BRISK      | 101\.253      | 4\.90E\+06 | 751         | 0                  | 6          |
| ORB       | BRIEF      | 83\.5899      | 4\.90E\+06 | 545         | 0                  | 6          |
| ORB       | ORB        | 92\.1991      | 4\.90E\+06 | 562         | 0                  | 6          |
| ORB       | FREAK      | 832\.678      | 4\.90E\+06 | 420         | 0                  | 6          |
| ORB       | SIFT       | 1139\.23      | 4\.90E\+06 | 897         | 5                  | 4          |
| ORB       | AKAZE      | 1929\.61      | 4\.90E\+06 | 9213        | 0                  | 6          |
| SIFT      | BRISK      | 558\.691      | 8\.21E\+06 | 594         | 0                  | 6          |
| SIFT      | BRIEF      | 534\.565      | 8\.21E\+06 | 704         | 0                  | 6          |
| SIFT      | ORB        | 554\.086      | 8\.21E\+06 | 683         | 0                  | 6          |
| SIFT      | FREAK      | 1330\.97      | 8\.21E\+06 | 595         | 0                  | 6          |
| SIFT      | SIFT       | 842\.805      | 8\.21E\+06 | 669         | 5                  | 4          |
| SIFT      | AKAZE      | 2366\.78      | 8\.21E\+06 | 9213        | 0                  | 6          |
| AKAZE     | BRISK      | 523\.516      | 1\.14E\+07 | 1215        | 0                  | 6          |
| AKAZE     | BRIEF      | 506\.795      | 1\.14E\+07 | 1266        | 0                  | 6          |
| AKAZE     | ORB        | 520\.501      | 1\.14E\+07 | 1260        | 0                  | 6          |
| AKAZE     | FREAK      | 1310\.04      | 1\.14E\+07 | 1187        | 0                  | 6          |
| AKAZE     | SIFT       | 767\.706      | 1\.14E\+07 | 1334        | 5                  | 4          |
| AKAZE     | AKAZE      | 2419\.06      | 1\.14E\+07 | 9213        | 0                  | 6          |

The above table is gernerated by the loop for all combined detector and extractor, note the AKAZE is only paired with itslef.
The descriptor\_dtype and  des\_norm is the default descriptor data_type such as CV_32F CV_8U, and the norm type such as NORM_HAMMING or NORM_L2 for compute for matching.

Based on the processing time for detection and extraction for our vehicle project task we shall use below detector / extractor pair

| Detector |  Extractor |  Process Time |
|----------|------------|---------------|
| FAST     | BRIEF      | 22\.1156      |
| FAST     | ORB        | 34\.0921      |
| FAST     | BRISK      | 41\.5455      |

Finally as we not only focus on the real-time process but also the accuracy of the process result, based on our running time and roughly the out-put images, we will use a balanced solution such as ORB/HARRIS detector andpair with BRISK/BRIEF/ORB extractor, and you could see the HARRIS result is more clean and focused on object edeg/corner and ORB seemes moew nosiy as more other feature detected.


