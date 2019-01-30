//
//  BSP.cpp
//  generativeBSP
//
//  Created by Derik Gagnon on 1/30/19.
//  Copyright © 2019 Derik Gagnon. All rights reserved.
//

#include "BSP.hpp"


/* Node Class Functions */
Node::Node() {
    mTopLeftY = HEIGHT;
    mTopLeftX = WIDTH;
    mBottomRightY = 0;
    mBottomRightX = 0;
}

Node::Node(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
    mTopLeftY = topLeftY;
    mTopLeftX = topLeftX;
    mBottomRightY = bottomRightY;
    mBottomRightX = bottomRightX;
}

void Node::setTopLeftX(int topLeftX) {
    mTopLeftX = topLeftX;
}

void Node::setTopLeftY(int topLeftY) {
    mTopLeftY = topLeftY;
}

void Node::setBottomRightX(int bottomRightX) {
    mBottomRightX = bottomRightX;
}

void Node::setBottomRightY(int bottomRightY) {
    mBottomRightY = bottomRightY;
}

/* Binary Space Partition Tree Class Functions */
void BspTree::split(Node node) {
    int random_num = rand() % 2;
//    int height = node.getHeight();
//    int width = node.getWidth();
    
    if (random_num == 0) {
            // Vertical Slice
            int left_bound = node.getTopLeftX();
            int right_bound = node.getBottomRightX();
    } else {
            // Horizontal Slice
            int upper_bound = node.getTopLeftY();
            int lower_bound = node.getBottomRightY();
    }
}
