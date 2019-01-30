//
//  BSP.hpp
//  generativeBSP
//
//  Created by Derik Gagnon on 1/30/19.
//  Copyright © 2019 Derik Gagnon. All rights reserved.
//

#ifndef BSP_hpp
#define BSP_hpp

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>

const int HEIGHT = 50, WIDTH = 50;
const int MINIMUM_SIZE = (HEIGHT / 4) * (WIDTH / 4);

/* Node Class */
class Node {
private:
    int mTopLeftX, mTopLeftY, mBottomRightX, mBottomRightY;
    Node * mLChild = NULL, * mRChild = NULL;
    
public:
    Node();
    Node(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
    int getHeight(){return std::abs(mTopLeftY - mBottomRightY);}
    int getWidth(){return std::abs(mTopLeftX - mBottomRightX);}
    int getTopLeftX(){return mTopLeftX;}
    int getTopLeftY(){return mTopLeftY;}
    int getBottomRightX(){return mBottomRightX;}
    int getBottomRightY(){return mBottomRightY;}
    void setTopLeftX(int topLeftX);
    void setTopLeftY(int topLeftY);
    void setBottomRightX(int bottomRightX);
    void setBottomRightY(int bottomRightY);
};

/* Binary Space Partition Tree Class */
class BspTree {
private:
    Node root;
public:
    void split(Node node);
};

#endif /* BSP_hpp */
