//
//  mosaic.cpp
//  video
//
//  Created by Lucas Ribeiro de Abreu on 10/07/2015.
//  Copyright (c) 2015 Lucas Ribeiro de Abreu. All rights reserved.
//

#include "mosaic.h"


#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    vector <Mat> images;
    int order = 3; int k;
    int flag = 0;
    Size imageSize = Size(2560, 1440);
    
    Mat img;
    
    for (int i = 0 ; i < order*order; i++) {
        
        if (i==0) {
            img = imread("/Users/Lucas/Desktop/"+to_string(i)+".png");
            putText(img, "FOTO "+to_string(i), Point(70,70), FONT_HERSHEY_COMPLEX, 2.5, Scalar(0,255,128));
            images.push_back(img);
            imshow("", img);
            cout << i<< " ";
            img.release();
            continue;
            
        }
        
        if(flag == 0){
            img = imread("/Users/Lucas/Desktop/"+to_string(i)+".png");
            putText(img, "FOTO "+to_string(i), Point(70,70), FONT_HERSHEY_COMPLEX, 2.5, Scalar(0,255,128));
            images.push_back(img);
            img.release();
            cout << i<< " ";
            
        }
        if(flag == 1){
            cout << endl;
            for (k=i+order-1; k>=i; k--) {
                img = imread("/Users/Lucas/Desktop/"+to_string(k)+".png");
                putText(img, "FOTO "+to_string(k), Point(70,70), FONT_HERSHEY_COMPLEX, 2.5, Scalar(0,255,128));
                images.push_back(img);
                cout << k<< " ";
            }
            i = k + order;
            flag = 0;
            cout << endl;
            continue;
        }
        
        if( ((i+1)%order) == 0){
            flag = 1;
        }
        else
            flag = 0;
        
        
    }
    
    
    cout<<endl;
    cout<<endl;
    Mat mosaic(Size(2560, 1440), CV_8UC3);
    Mat tile;
    int n = 0;
    for (int i=0 ; i<order; i++) {
        for (int j=0; j<order; j++) {
            cout << n << endl;
            cout<< i*(imageSize.width/order)<<" ";
            cout<< j*(imageSize.height/order)<<endl;
            
            cout<<endl;
            
            resize(images[n], tile ,Size((int)imageSize.width/order, (int)imageSize.height/order));
            
            Rect region_of_interest = Rect(Point(j*imageSize.width/order,
                                                 i*imageSize.height/order),
                                           tile.size());
            
            tile.copyTo(mosaic(region_of_interest));
            tile.release();
            
            
            n++;
        }
        
    }
    
    imwrite("/Users/Lucas/Desktop/out.png", mosaic);
    
    return 0;
    
}
