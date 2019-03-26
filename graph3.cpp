#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"
using namespace std;

ofstream file("function.bmp");
int image[4096][4096];
double aa[1024][1024];

double aafilter(int k, int l){
    double sum = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            sum += image[k+i][l+j];
        }
    }
    return sum/16;
}

void printpixel(int x, int y){
    for(int i = -4; i < 4; i++){
        for(int j = -4; j < 4; j++){
            int printx = x+i;
            int printy = y+j;
            if((printx >= 0 && printy >= 0) && (printx <= 4096 && printy <=4096)){
                image[printx][printy] = 1;
            }
        }
    }
}

double cof[256];
int grau;

double derivative(double x){
    double sum = 0;
    for(int i = grau; i > 0; i--){
        sum += i*cof[i]*pow(x, i-1);
    }
    return sum*0.0078125;
}

int main(){
    file << initImage();
    cin>>grau;
    for(int i = grau; i >= 0; i--){
        cin>>cof[i];
    }
    double px = -16, py = 0;
    for(int i = grau; i >= 0; i--){
        py += cof[i]*pow(-16, i);
    }
    double err = 0;
    if(grau > 1){
        double by = py;
        for(double x = -16+0.0078125; x < 16; x += 0.0078125){
            by += derivative(x);
            if(x == 0){
                break;
            }
        }
        err = cof[0] - by;
    }
    for(double x = -16+0.0078125; x < 16; x += 0.0078125){
        px = x;
        py += derivative(px);
        double wy = py;
        if(grau > 1){
            wy = wy + err;
        }
        if(py > -16 && wy < 16){
            printpixel((px+16)*128, (wy+16)*128);
        }
    }
    // 32 0.0078125

    int k = 0, l = 0;
    for(int i = 0; i < 1024; i++){
        for(int j = 0; j < 1024; j++){
            aa[i][j] = aafilter(k, l);
            l += 4;
        }
        l = 0;
        k += 4;
    }
    for(int y = 0; y < 1024; y++){
        for(int x = 0; x < 1024; x++){
            if(x == 512 || y == 512){
                file << color("000000");
            }
            else if(((x)%32 == 0 || (y)%32 == 0) && (1-aa[x][y])*255 > 124){
                file << color("7C7C7C");
            }
            else{
                int yey = (1-aa[x][y])*255;
                string s = dectohex(yey);
                file << hextodec(s);
                file << hextodec(s);
                file << hextodec(s);
            }
        }
    }
    file << endImage();
    file.close();
    system("function.bmp");
}
