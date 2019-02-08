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
const int MINIMUM_WIDTH= (WIDTH / 6);
const int MINIMUM_HEIGHT= (HEIGHT / 6);

/* Node Class */
class Node {
private:
    //members
    int mTopRightX, mTopRightY, mBottomLeftX, mBottomLeftY;
    int mRoomTRX, mRoomTRY, mRoomBLX, mRoomBLY;
    bool connected;
public:
    Node * mLChild, * mRChild;
    bool horizontal;
    int mbridgeStartX, mbridgeStartY, mbridgeEndX, mbridgeEndY;
    
    //Constructors
    Node();
    Node(int topRightX, int topRightY, int TopRightX, int TopRightY);
    
    //getters
    int getTopRightX(){return mTopRightX;}
    int getTopRightY(){return mTopRightY;}
    int getBottomLeftX(){return mBottomLeftX;}
    int getBottomLeftY(){return mBottomLeftY;}
    int getRoomTRX(){return mRoomTRX;}
    int getRoomTRY(){return mRoomTRY;}
    int getRoomBLX(){return mRoomBLX;}
    int getRoomBLY(){return mRoomBLY;}
    int getHeight(){return std::abs(mTopRightY - mBottomLeftY);}
    int getWidth(){return std::abs(mTopRightX - mBottomLeftX);}
    bool isConnected() { return connected; };
    
    //setters
    void setBottomLeftX(int topRightX);
    void setBottomLeftY(int topRightY);
    void setTopRightX(int TopRightX);
    void setTopRightY(int TopRightY);
    void setRoomTRX(int roomTRX);
    void setRoomTRY(int roomTRY);
    void setRoomBLX(int roomBLX);
    void setRoomBLY(int roomBLY);
    
    //utilities
    bool isTooBig(){return getHeight() > MINIMUM_HEIGHT && getWidth() > MINIMUM_WIDTH;}
    bool isLeaf(){return mLChild == NULL && mRChild == NULL;};
    void connect() { connected = true; };
    void createRoom();
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
