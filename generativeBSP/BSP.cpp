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
    mLChild = NULL;
    mRChild = NULL;
    mTopRightY = HEIGHT;
    mTopRightX = WIDTH;
    mBottomLeftY = 0;
    mBottomLeftX = 0;
}

Node::Node(int topRightX, int topRightY, int bottomLeftX, int bottomLeftY) {
    mLChild = NULL;
    mRChild = NULL;
    mTopRightY = topRightY;
    mTopRightX = topRightX;
    mBottomLeftY = bottomLeftY;
    mBottomLeftX = bottomLeftX;
}

void Node::setBottomLeftX(int topRightX) {
    mTopRightX = topRightX;
}

void Node::setBottomLeftY(int topRightY) {
    mTopRightY = topRightY;
}

void Node::setTopRightX(int bottomLeftX) {
    mBottomLeftX = bottomLeftX;
}

void Node::setTopRightY(int bottomLeftY) {
    mBottomLeftY = bottomLeftY;
}

void Node::createRoom() {
    int area = (MINIMUM_WIDTH - 3) * (MINIMUM_HEIGHT - 3);
    int deltaX = 0, deltaY = 0;
    do {
        deltaX = mTopRightX - (getWidth() / 2);
        mRoomTRX = mTopRightX - (rand() % (mTopRightX - deltaX));
        mRoomBLX = mBottomLeftX + (rand() % (deltaX - mBottomLeftX));
        deltaY = mTopRightY - (getHeight() / 2);
        mRoomTRY = mTopRightY - (rand() % (mTopRightY - deltaY));
        mRoomBLY = mBottomLeftY + (rand() % (deltaY - mBottomLeftY));
        std::cout << "Potential: " << mRoomBLX << ", " << mRoomBLY << "  " << mRoomTRX << ", " << mRoomTRY << "\n";
        
    } while (((mRoomTRX - mRoomBLX) * (mRoomTRY - mRoomBLY)) <= area);
    std::cout << "Node: Bottom Left (" << mRoomBLX << ", " << mRoomBLY << ")\n";
    std::cout << "Node: Top Right (" << mRoomTRX << ", " << mRoomTRY << ")\n";
}

/* Binary Space Partition Tree Class Functions */
BspTree::BspTree() {
    root = Node();
}

void Split(Node* node) {
    int split;
    int minSide = MINIMUM_HEIGHT / 2; // provided min height and min width are equal
    if (rand() % 2 == 0) {
            // Vertical Slice
            do {
                split = (rand() % node->getWidth()) + node->getBottomLeftX();
                std::cout << "split " << node->getTopRightX() - split << std::endl;
            } while (node->getTopRightX() - split < minSide || split - node->getBottomLeftX() < minSide);
            node->mLChild = new Node(node->getTopRightX(), node->getTopRightY(), split, node->getBottomLeftY());
            node->mRChild = new Node(split, node->getTopRightY(), node->getBottomLeftX(), node->getBottomLeftY());
            std::cout << "splitting vertically on " << split << std::endl;
    } else {
            // Horizontal Slice
            do {
                split = rand() % node->getHeight() + node->getBottomLeftY();
                std::cout << "split " << node->getTopRightY() - split << std::endl;
            } while (node->getTopRightY() - split < minSide || split - node->getBottomLeftY() < minSide);
            node->mLChild = new Node(node->getTopRightX(), node->getTopRightY(), node->getBottomLeftX(), split);
            node->mRChild = new Node(node->getTopRightX(), split, node->getBottomLeftX(), node->getBottomLeftY());
            std::cout << "splitting horizontally on " << split << std::endl;
    }
}

void SplitLeafs(Node* node) {
    if (node->isLeaf() && node->isTooBig()) {
        // std::cout << "here " << node->isTooSmall() << std::endl;
        Split(node);
        return;
    } else if (!node->isLeaf()) {
        SplitLeafs(node->mLChild);
        SplitLeafs(node->mRChild);
    }
}

void BspTree::expand(int depth) {
    for(int i = 0; i < depth; i++) {
        SplitLeafs(&root);
    }
}

void visualizeTree(Node* node) {
    if (node->isLeaf()) {
        return;
    }
    std::cout << "node: " << node << std::endl;
    std::cout << "left: " << node->mLChild << " right: " << node->mRChild << std::endl;
    visualizeTree(node->mLChild);
    visualizeTree(node->mRChild);
}

void BspTree::visualize() {
    std::cout << "visualizing" << std::endl;
    visualizeTree(&root);
}
