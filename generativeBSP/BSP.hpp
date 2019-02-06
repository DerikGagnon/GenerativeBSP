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
const int MINIMUM_WIDTH= (WIDTH / 5);
const int MINIMUM_HEIGHT= (HEIGHT / 5);

/* Node Class */
class Node {
private:
    int mTopRightX, mTopRightY, mBottomLeftX, mBottomLeftY;
    
public:
    Node * mLChild, * mRChild;
    Node();
    Node(int topRightX, int topRightY, int TopRightX, int TopRightY);
    int getHeight(){return std::abs(mTopRightY - mBottomLeftY);}
    int getWidth(){return std::abs(mTopRightX - mBottomLeftX);}
    bool isTooBig(){return getHeight() > MINIMUM_HEIGHT && getWidth() > MINIMUM_WIDTH;}
    int getTopRightX(){return mTopRightX;}
    int getTopRightY(){return mTopRightY;}
    int getBottomLeftX(){return mBottomLeftX;}
    int getBottomLeftY(){return mBottomLeftY;}
    void setBottomLeftX(int topRightX);
    void setBottomLeftY(int topRightY);
    void setTopRightX(int TopRightX);
    void setTopRightY(int TopRightY);
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
