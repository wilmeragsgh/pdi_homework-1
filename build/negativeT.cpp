#include <Rcpp.h>
#include <fstream>
#include <string>
#include <stdlib.h>  
#include <stdio.h>  
#include <math.h>  
#include <opencv2/opencv.hpp>  
//#include <highgui.h> 
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

RcppExport SEXP readData(SEXP f1) {
    std::string fname = Rcpp::as<std::string>(f1); 
    std::ifstream fi;
    fi.open(fname.c_str(),std::ios::in);
    IplImage* img = 0;   
    int height,width,step,channels;  
    uchar *data;  
    int i,j,k;  
    // Load image   
    img=cvLoadImage(fname.c_str(),-1);  
    if(!img)  
    {  
        printf("Could not load image file\n");  
        exit(0);  
    }  
    // acquire image info  
    height    = img->height;    
    width     = img->width;    
    step      = img->widthStep;    
    channels  = img->nChannels;  
    data      = (uchar *)img->imageData;  
    // reverse image 
    for(i=0;i<height;i++)   
        for(j=0;j<width;j++)   
            for(k=0;k<channels;k++)  
                data[i*step+j*channels+k]=255-data[i*step+j*channels+k];  
    //imwrite("test.bmp", &img);    
    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", img);
    waitKey(30);
    Rcpp::CharacterVector rline = Rcpp::wrap("test.bmp");
    return rline;
}
