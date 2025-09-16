//
//  Test2.cpp
//  test
//
//  Created by Nolan Jones on 2/26/23.
//

#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include "Wordle.hpp"

#define ScreenHeight 100
#define ScreenWidth 250

char screen[ScreenWidth][ScreenHeight];

struct Point3DNew{
    float x, y, z, c;
};

struct Triangle3DNew{
    Point3DNew p[3];
};
Triangle3DNew f;
int baryCentric(int x, int y){
    float uTemp, vTemp, wTemp, whole;
    float u, v, w;
    
    whole = f.p[0].x * (f.p[1].y - f.p[2].y) + f.p[1].x * (f.p[2].y - f.p[0].y) + f.p[2].x * (f.p[0].y - f.p[1].y);
    
    uTemp = x * (f.p[1].y - f.p[2].y) + f.p[1].x * (f.p[2].y - y) + f.p[2].x * (y - f.p[1].y);
    vTemp = f.p[0].x * (y - f.p[2].y) + x * (f.p[2].y - f.p[0].y) + f.p[2].x * (f.p[0].y - y);
    wTemp = f.p[0].x * (f.p[1].y - y) + f.p[1].x * (y - f.p[0].y) + x * (f.p[0].y - f.p[1].y);
    
    u = uTemp/whole;
    v = vTemp/whole;
    w = wTemp/whole;
    
    //std::cout << f.p[0].c << " " << f.p[1].c << " " << f.p[2].c << " ";
    //std::cout << " " << uTemp << " " << vTemp << " " << wTemp << " " << whole << " " << (f.p[0].c) * u + (f.p[1].c * v) + (f.p[2].c * w) << std::endl;;
    return (int)(f.p[0].c) * u + (f.p[1].c * v) + (f.p[2].c * w);
}
void LineNew(double x1, double x2, int y){
    x1 += .5;
    x2 += .5;
    
    std::string ValueOptions = "WH0OIio*+-,.";
    //std::string ValueOptions = "WH00OOIIIiiioooo****+++++-----,,,,,,......";
    char c;
    //if(x1 > x2) std::swap(x1, x2);
    //std::cout << "step: "<< cStep << " ";
    
    
    for(int x = x1; x < x2; x++){
        if(x < ScreenWidth && x > -1){
            if(y < ScreenHeight && y > -1){
                c = ValueOptions.at(baryCentric(x, y));
                screen[x][y] = c;
            }
        }
    }
    //std::cout << std::endl;
}

void DrawFBottom(Triangle3DNew Bottom){
    float slope3 = ((float)(Bottom.p[1].x-Bottom.p[2].x)/(Bottom.p[1].y-Bottom.p[2].y));
    float slope4 = ((float)(Bottom.p[0].x-Bottom.p[2].x)/(Bottom.p[0].y-Bottom.p[2].y));
    
    double b1, b2;
    
    b1 = Bottom.p[1].x;
    b2 = Bottom.p[0].x;

    if(Bottom.p[1].x > Bottom.p[0].x){
        std::swap(slope3, slope4);
        std::swap(b1, b2);
    }
    
    for(int y = Bottom.p[0].y; y < Bottom.p[2].y; y++){
        LineNew(b1, b2, y);
        b1 += slope3;
        b2 += slope4;
    }
}

void DrawFTop(Triangle3DNew Top){
    float slope1 = ((float)(Top.p[0].x-Top.p[1].x)/(Top.p[0].y-Top.p[1].y));
    float slope2 = ((float)(Top.p[0].x-Top.p[2].x)/(Top.p[0].y-Top.p[2].y));
    
    double t1, t2;
    
    t1 = Top.p[2].x;
    t2 = Top.p[1].x;

    if(Top.p[1].x < Top.p[2].x){
        std::swap(slope1, slope2);
        std::swap(t1, t2);
    }
    
    for(int y = Top.p[2].y ; y > Top.p[0].y; y--){
        LineNew(t1, t2, y);
        t1 += -slope2;
        t2 += -slope1;
    }
    //std::cout << std::endl;
}
void Draw(Triangle3DNew ySwap){
    if(ySwap.p[0].y > ySwap.p[1].y) std::swap(ySwap.p[0], ySwap.p[1]);
    if(ySwap.p[1].y > ySwap.p[2].y) std::swap(ySwap.p[1], ySwap.p[2]);
    if(ySwap.p[0].y > ySwap.p[1].y) std::swap(ySwap.p[0], ySwap.p[1]);
    
    f = ySwap;
    double slope02 = ((double)(ySwap.p[0].x-ySwap.p[2].x)/(ySwap.p[0].y-ySwap.p[2].y));
    
    Triangle3DNew Top;
    Triangle3DNew Bottom;
    
    if(ySwap.p[0].y == ySwap.p[1].y){
        DrawFBottom(ySwap);
    }else if(ySwap.p[2].y == ySwap.p[1].y){
        DrawFTop(ySwap);
    }else{
        int newX = slope02*(ySwap.p[1].y-ySwap.p[0].y)+ySwap.p[0].x;
        int newY = ySwap.p[1].y;
        
        Top = ySwap;
        Top.p[2].x = newX;
        Top.p[2].y = newY;
        DrawFTop(Top);
        
        Bottom = ySwap;
        Bottom.p[0].x = newX;
        Bottom.p[0].y = newY;
        DrawFBottom(Bottom);
    }
}

int main(){
   /*
    Triangle3DNew tri;
    srand(9);
    for(int c = 0; c < 100; c++){
        for(int i = 0; i < 3; i++){
            
            tri.p[i].x = rand() % 350-25;
            tri.p[i].y = rand() % 150-25;
            tri.p[i].z = rand() % 100;
            tri.p[i].c = rand() % 12;
            
            std::cout << tri.p[i].x << " " << tri.p[i].y << " " << tri.p[i].c << std::endl;
        }
        for(int x = 0; x < ScreenWidth; x++){
            for(int y = 0; y < ScreenHeight; y++){
                screen[x][y] = ' ';
            }
        }
        //DrawTriangleNew(tri);
        Draw(tri);
        for(int i = 0; i < 3; i++){
            if(tri.p[i].x < ScreenWidth && tri.p[i].x > -1){
                if(tri.p[i].y < ScreenHeight && tri.p[i].y > -1){
                    int z = tri.p[i].x;
                    int q = tri.p[i].y;
                    screen[z][q] = '*';
                }
            }
        }
        for(int y = ScreenHeight-1; y > -1; y--){
            for(int x = 0; x < ScreenWidth; x++){
                std::cout << screen[x][y];
            }
            std::cout << std::endl;
        }
        
    }*/
    
    Wordle();
    /*
    std::srand(time(NULL));
    std::cout << "Individual: " << std::rand() % 9 + 1 << std::endl << "Group: " << std::rand() % 6 + 1 << std::endl << "Wing: " << std::rand() % 8 + 1 << std::endl;
    */
}

