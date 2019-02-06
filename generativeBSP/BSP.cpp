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
    mBottomLeftY = HEIGHT;
    mBottomLeftX = WIDTH;
    mTopRightY = 0;
    mTopRightX = 0;
}

Node::Node(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) {
    mLChild = NULL;
    mRChild = NULL;
    mBottomLeftY = bottomLeftY;
    mBottomLeftX = bottomLeftX;
    mTopRightY = topRightY;
    mTopRightX = topRightX;
}

void Node::setBottomLeftX(int bottomLeftX) {
    mBottomLeftX = bottomLeftX;
}

void Node::setBottomLeftY(int bottomLeftY) {
    mBottomLeftY = bottomLeftY;
}

void Node::setTopRightX(int topRightX) {
    mTopRightX = topRightX;
}

void Node::setTopRightY(int topRightY) {
    mTopRightY = topRightY;
}

/* Binary Space Partition Tree Class Functions */
BspTree::BspTree() {
    root = Node();
}

void Split(Node* node) {
    int delta, split;
    if (rand() % 2 == 0) {
            // Vertical Slice
            int left_bound = node->getBottomLeftX();
            int right_bound = node->getTopRightX();
            // std::cout << right_bound << " " << left_bound << std::endl;
            delta = right_bound - left_bound;
            split = rand() % delta;
            if (split < 10) {
                split = 11;
            }
            std::cout << "splitting vertically on " << split << std::endl;
            node->mLChild = new Node(node->getBottomLeftX(), node->getBottomLeftY(), split, node->getTopRightY());
            node->mRChild = new Node(split, node->getBottomLeftY(), node->getTopRightX(), node->getTopRightY());
    } else {
            // Horizontal Slice
            int upper_bound = node->getBottomLeftY();
            int lower_bound = node->getTopRightY();
            delta = upper_bound - lower_bound;
            split = rand() % delta;
            if (split < 10 ) {
                split = 11;
            }
            std::cout << "splitting horizontally on " << split << std::endl;
            node->mLChild = new Node(node->getBottomLeftX(), node->getBottomLeftY(), node->getTopRightX(), split);
            node->mRChild = new Node(node->getBottomLeftX(), split, node->getTopRightX(), node->getTopRightY());
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
