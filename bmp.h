#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
#include <iostream>
#include <ctype.h>
using namespace std;

float pot(float x, int y){
    if(y >= 0){
        // Se y >= 0, temos que y é positivo
        long double r = 1;
        for(int i = 1; i <= y; ++i){
            r = r*x;
        }
        return r;
    }
    else{
        // y é negativo logo será (1/x)^y
        long double r = 1;
        float f = 1/x;
        for(int i = 1; i <= -y; ++i){
            r = r*f;
        }
        return r;
    }
}

int hex(char c){
    if(c <= '9'){
        return c-48;
    }
    else{
        return c-55;
    }
}

string dectohex(int n){
    string r;
    int i = 0;
    int convert[256];
    int x = n;
    while(x > 0){
        convert[i] = x%16;
        x = x/16;
        ++i;
    }
    while(i >= 1){
        if(convert[i-1] >= 10){
            r += char(convert[i-1]+55);
        }
        else{
            r += char(convert[i-1]+48);
        }
        --i;
    }
    return r;
}

char hextodec(string x){
    int r = 0;
    for(int i = 0; i < x.size();++i){
        r += hex(x[i])*pot(16, x.size()-i-1);
    }
    return char(r);
}

string initImage(){
    string r;
    string q = "42 4D 4C 00 00 00 00 00 00 00 1A 00 00 00 0C 00 00 00 ";
    string token = "";
    for(int i = 0; i < q.size();++i){
        if(isspace(q[i])){
            r += hextodec(token);
            token = "";
        }
        else{
            token += q[i];
        }
    }
    r += hextodec("00");r += hextodec("04");
    r += hextodec("00");r += hextodec("04");
    r += hextodec("01");r += hextodec("00");r += hextodec("18");r += hextodec("00");
    return r;
}

string color(string hexValue){
    string a = ""; a += hexValue[4]; a += hexValue[5];
    string b = ""; b += hexValue[2]; b += hexValue[3];
    string c = ""; c += hexValue[0]; c += hexValue[1];
    string r;
    r += hextodec(a);
    r += hextodec(b);
    r += hextodec(c);
    return r;
}

string endImage(){
    string r;
    r += hextodec("00");
    r += hextodec("00");
    return r;
}

#endif
