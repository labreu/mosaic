//
//  main.cpp
//  video
//
//  Created by Lucas Ribeiro de Abreu on 28/06/2015.
//  Copyright (c) 2015 Lucas Ribeiro de Abreu. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <string.h>

using namespace cv;
using namespace std;

string path = "/Users/Lucas/Desktop/uscan/20x20_2/";
int order = 20;

int convertImg(){
   
    printf("Convertendo imagens\n");
    for(int i = 0; i< order*order; i++)
    {
        
        Mat img = imread(path+"-"+to_string(i)+".png", 0); //read gray
        if(img.empty()){
            cout <<i<<endl;
            return 0;
        }
        cvtColor(img, img, CV_BayerGR2RGB);
        imwrite(path+to_string(i)+"_c.png", img);
    }
    printf("OK\n");
    return 1;
}

int main(int argc, const char * argv[]) {
    
    vector <Mat> images;
    
    int k;
    int flag = 0;
    float borderWidth = 0.010;
    float borderHeight = 0.015;
    //float borderWidth = 0;  //no border
    //float borderHeight = 0;
    float letterSize = 6;
    Scalar fontColor = Scalar(0,0,255);  //BGR
    Size imageSize = Size(15000, 10000);
    //Size imageSize = Size(2560, 1440);
    Point posLabel = Point(1940*0.4,1080*0.4);
    string fileExtension = "_c.png";
    string outFile = "outNoBorder.png";
    string photoText = "";
    Mat img;
    bool debug = true;
    
    //convertImg();  descomenta se precisar converter imagens  
    
    for (int i = 0 ; i < order*order; i++) {
        
        if (i==0) {
            img = imread(path+to_string(i)+fileExtension);
            if (img.empty()) {
                cout << "image empty"<<endl;
                return 0 ;
            }
            putText(img, photoText+to_string(i), posLabel, FONT_HERSHEY_COMPLEX, letterSize, fontColor);
            
            copyMakeBorder(img, img, borderHeight*img.rows, borderHeight*img.rows, borderWidth*img.cols, borderWidth*img.cols, BORDER_CONSTANT);
            
            images.push_back(img);
            if(debug)
                cout << i<< " ";
            img.release();
            continue;
       
        }
        
        if(flag == 0){
            img = imread(path+to_string(i)+fileExtension);
            putText(img, photoText+to_string(i), posLabel, FONT_HERSHEY_COMPLEX, letterSize, fontColor);
            copyMakeBorder(img, img, borderHeight*img.rows, borderHeight*img.rows, borderWidth*img.cols, borderWidth*img.cols, BORDER_CONSTANT);
            images.push_back(img);
            img.release();
            if(debug)
                cout << i<< " ";
            
        }
        
        if(flag == 1){
            
            if(debug)
                cout << endl;
            for (k=i+order-1; k>=i; k--) {
                img = imread(path+to_string(k)+fileExtension);
                putText(img,photoText+to_string(k), posLabel, FONT_HERSHEY_COMPLEX, letterSize, fontColor);
                copyMakeBorder(img, img, borderHeight*img.rows, borderHeight*img.rows, borderWidth*img.cols, borderWidth*img.cols, BORDER_CONSTANT);
                images.push_back(img);
                if(debug)
                    cout << k<< " ";
            }
            i = k + order;
            flag = 0;
            if(debug)
                cout << endl;
            continue;
        }
        
        if( ((i+1)%order) == 0){
            flag = 1;
        }
        else
            flag = 0;
       
    }
    
    if(debug){
        cout<<endl;
        cout<<endl;
    }
    destroyAllWindows();
    Mat mosaic(imageSize, CV_8UC3);
    Mat tile;
    int n = 0;
    for (int i=0 ; i<order; i++) {
        for (int j=0; j<order; j++) {
            if(debug){
                cout << n << endl;
                cout<< i*(imageSize.width/order)<<" ";
                cout<< j*(imageSize.height/order)<<endl;
                cout<<endl;
            }
            resize(images[n], tile ,Size((int)imageSize.width/order, (int)imageSize.height/order));
            
            Rect region_of_interest = Rect(Point(j*imageSize.width/(1*order),
                                                 i*imageSize.height/(1*order)),
                                                 tile.size());
            
            tile.copyTo(mosaic(region_of_interest));
            tile.release();
        
            n++;
        }
    }
    
    imwrite(path+outFile, mosaic);
    cout << "Finished"<<endl;
    return 0;
    
}
