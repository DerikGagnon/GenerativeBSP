//
//  world.cpp
//  generativeBSP
//
//  Created by Derik Gagnon on 1/30/19.
//  Copyright © 2019 Derik Gagnon. All rights reserved.
//

#include "world.hpp"

/* Node Class Functions */
World::World() {
    // stack<std::string> emojis;
    for (int i = 0; i < NUM_EMOJIS; i++) {
        emojis.push(EMOJIS[i]);
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[j][i] = "#";
        }
    }
}

void World::populate(Node* node) {
    if (node->isLeaf()) {
        std::string emoji = "💞";
        if (!emojis.empty()) {
            emoji = emojis.top();
            emojis.pop();
        }
        std::cout << "Node:" << emoji <<
            " bottom left: (" << node->getBottomLeftX() << ", " << node->getBottomLeftY() << ")" <<
            " top right: (" << node->getTopRightX() << ", " << node->getTopRightY() << ")" <<
            std::endl;
        for (int h = node->getBottomLeftY(); h < node->getTopRightY(); h++) {
            for (int w = node->getBottomLeftX(); w < node->getTopRightX(); w++) {
                map[w][h] = emoji;
            }
        }
        node->createRoom();

        return;
    }
    populate(node->mLChild);
    populate(node->mRChild);
}

int matcher(int topStart, int topEnd, int botStart, int botEnd) {
    int start = 0, end = 0, delta = 0;
    for (int i = topStart; i < topEnd; i++ ) {
        for (int j = botStart; j < botEnd; j++) {
            if ((i == j) && (start == 0)) {
                start = i;
                while ((i == j) && (i < topEnd) && (j < botEnd)) {
                    i++;
                    j++;
                }
                end = i;
                delta = end - start;
                return (start + (rand() % delta));
            }
        }
    }
    return -1;
}

void World::populateBridges(Node* root) {
    int i = 0;
    while (!root->isConnected() && i < 10) {
        connectRooms(root, NULL);
        i++;
    }
}

void World::connectRooms(Node* node, Node* parent) {
    
    if (node->isLeaf() || node->isConnected()) {
        return;
    }
    
    connectRooms(node->mRChild, node);
    connectRooms(node->mLChild, node);
    // is not leaf or connected
    // check if either children are leafs
    if (node->mLChild->isLeaf() && node->mRChild->isLeaf()) {
        std::cout << "connecting l " << node->mLChild->isLeaf() << " r " << node->mRChild->isLeaf() << std::endl;
        // create path connecting child rooms

        if (node->horizontal) {
            // find matching x coords
            // for ( int lx = node->mLChild->getBottomLeftX(); lx < node -> )
            // left is top, right is bottom
            int topStart = node->mLChild->getRoomBLX();
            int topEnd = node->mLChild->getRoomTRX();
            int botStart = node->mRChild->getRoomBLX();
            int botEnd = node->mRChild->getRoomTRX();
            int topY = node->mLChild->getRoomBLY();
            int botY = node->mRChild->getRoomTRY();
            int bridgeX = matcher(topStart, topEnd, botStart, botEnd);
            if (bridgeX == -1) {
                std::cout << "DO NOT LINE UP "<< topStart <<" "<< topEnd <<" "<< botStart<<" "<< botEnd<< "\n";
            } else {
                std::cout << "they line up at "<< bridgeX << " " << topY << " to " << botY <<" \n";
                for (int i = botY; i < topY; i++) {
                    charMap[bridgeX][i] = "O";
                }
            }
        } else {
            // find matching y coords bottom to top
            int leftStart = node->mLChild->getRoomBLY();
            int leftEnd = node->mLChild->getRoomTRY();
            int rightStart = node->mRChild->getRoomBLY();
            int rightEnd = node->mRChild->getRoomTRY();
            int topX = node->mLChild->getRoomBLX();
            int botX = node->mRChild->getRoomTRX();
            int bridgeY = matcher(leftStart, leftEnd, rightStart, rightEnd);
            if (bridgeY == -1) {
                std::cout << "DO NOT LINE UP "<< leftStart <<" "<< leftEnd <<" "<< rightStart<<" "<< rightEnd<< "\n";
            } else {
                std::cout << "they line up at "<< bridgeY << " " << topX << " to " << botX <<" \n";
                for (int i = botX; i < topX; i++) {
                    charMap[i][bridgeY] = "O";
                }
            }
        }
        node->setRoomBLX(std::min(node->mLChild->getRoomBLX(), node->mRChild->getRoomBLX()));
        node->setRoomBLY(std::min(node->mLChild->getRoomBLY(), node->mRChild->getRoomBLY()));
        node->setRoomTRX(std::max(node->mLChild->getRoomTRX(), node->mRChild->getRoomTRX()));
        node->setRoomTRY(std::max(node->mLChild->getRoomTRY(), node->mRChild->getRoomTRY()));
        node->connect();
        return;
    }
    
}


void World::draw() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << map[j][i];
        }
        std::cout << "\n";
    }
}

void World::fillCharMap() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            charMap[i][j] = "-";
        }
    }
}

void World::drawCharMap() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << charMap[j][i] << " ";
        }
        std::cout << "\n";
    }
}

void World::populateRooms(Node* node) {
    if (node->isLeaf()) {
        for (int h = node->getRoomBLY(); h < node->getRoomTRY(); h++) {
            for (int w = node->getRoomBLX(); w < node->getRoomTRX(); w++) {
                charMap[w][h] = "O";
            }
        }
        return;
    }
    populateRooms(node->mLChild);
    populateRooms(node->mRChild);
}
