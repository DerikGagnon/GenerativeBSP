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

/* Binary Space Partition Tree Class Functions */
BspTree::BspTree() {
    root = Node();
}

void Split(Node* node) {
    int delta, split;
    if (rand() % 2 == 0) {
            // Vertical Slice
            int left_bound = node->getTopRightX();
            int right_bound = node->getBottomLeftX();
            // std::cout << right_bound << " " << left_bound << std::endl;
            delta = right_bound - left_bound;
            split = rand() % delta;
            if (split < 10) {
                split = 11;
            }
            std::cout << "splitting vertically on " << split << std::endl;
            node->mLChild = new Node(node->getTopRightX(), node->getTopRightY(), split, node->getBottomLeftY());
            node->mRChild = new Node(split, node->getTopRightY(), node->getBottomLeftX(), node->getBottomLeftY());
    } else {
            // Horizontal Slice
            int upper_bound = node->getTopRightY();
            int lower_bound = node->getBottomLeftY();
            delta = upper_bound - lower_bound;
            split = rand() % delta;
            if (split < 10 ) {
                split = 11;
            }
            std::cout << "splitting horizontally on " << split << std::endl;
            node->mLChild = new Node(node->getTopRightX(), node->getTopRightY(), node->getBottomLeftX(), split);
            node->mRChild = new Node(node->getTopRightX(), split, node->getBottomLeftX(), node->getBottomLeftY());
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
