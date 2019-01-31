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
const int MINIMUM_WIDTH= (WIDTH / 4);
const int MINIMUM_HEIGHT= (HEIGHT / 4);

/* Node Class */
class Node {
private:
    int mTopLeftX, mTopLeftY, mBottomRightX, mBottomRightY;
    
public:
    Node * mLChild, * mRChild;
    Node();
    Node(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
    int getHeight(){return std::abs(mTopLeftY - mBottomRightY);}
    int getWidth(){return std::abs(mTopLeftX - mBottomRightX);}
    bool isTooSmall(){return getHeight() < MINIMUM_HEIGHT && getWidth() < MINIMUM_WIDTH;}
    int getTopLeftX(){return mTopLeftX;}
    int getTopLeftY(){return mTopLeftY;}
    int getBottomRightX(){return mBottomRightX;}
    int getBottomRightY(){return mBottomRightY;}
    void setTopLeftX(int topLeftX);
    void setTopLeftY(int topLeftY);
    void setBottomRightX(int bottomRightX);
    void setBottomRightY(int bottomRightY);
    bool isLeaf(){return mLChild == NULL;};
};

/* Binary Space Partition Tree Class */
class BspTree {
private:
    Node root;
public:
    BspTree();
    Node* getRoot(){return &root;};
    void expand(int depth);
    void visualize();
    void draw(std::string map[HEIGHT][WIDTH]);
};

#endif /* BSP_hpp */
