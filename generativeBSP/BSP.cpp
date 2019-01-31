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
    mTopLeftY = HEIGHT;
    mTopLeftX = WIDTH;
    mBottomRightY = 0;
    mBottomRightX = 0;
}

Node::Node(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
    mLChild = NULL;
    mRChild = NULL;
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
BspTree::BspTree() {
    root = Node();
}

void Split(Node* node) {
    int delta, split;
    if (rand() % 2 == 0) {
            // Vertical Slice
            int left_bound = node->getTopLeftX();
            int right_bound = node->getBottomRightX();
            // std::cout << right_bound << " " << left_bound << std::endl;
            delta = right_bound - left_bound;
            split = rand() % delta;
            if (split < 3) {
                split = 4;
            }
            std::cout << "splitting vertically on " << split << std::endl;
            node->mLChild = new Node(node->getTopLeftX(), node->getTopLeftY(), split, node->getBottomRightY());
            node->mRChild = new Node(split, node->getTopLeftY(), node->getBottomRightX(), node->getBottomRightY());
    } else {
            // Horizontal Slice
            int upper_bound = node->getTopLeftY();
            int lower_bound = node->getBottomRightY();
            delta = upper_bound - lower_bound;
            split = rand() % delta;
            if (split < 3) {
                split = 4;
            }
            std::cout << "splitting horizontally on " << split << std::endl;
            node->mLChild = new Node(node->getTopLeftX(), node->getTopLeftY(), node->getBottomRightX(), split),
            node->mRChild = new Node(node->getTopLeftX(), split, node->getBottomRightX(), node->getBottomRightY());
    }
}

void SplitLeafs(Node* node) {
    if (node->isLeaf() && !node->isTooSmall()) {
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