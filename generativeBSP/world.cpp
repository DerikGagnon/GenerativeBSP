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
        return;
    }
    populate(node->mLChild);
    populate(node->mRChild);
}

void World::draw() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << map[j][i];
        }
        std::cout << "\n";
    }
}
