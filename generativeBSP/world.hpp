//
//  world.hpp
//  generativeBSP
//
//  Created by Derik Gagnon on 1/30/19.
//  Copyright © 2019 Derik Gagnon. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include "BSP.hpp"

const int NUM_EMOJIS = 20;
const std::string EMOJIS[NUM_EMOJIS] = {
    "🏈", "💮", "❌", "😩", "😡", "🚨", "🥁", "🎳", "🎸", "🎱",
    "✅", "🐳", "🆒", "🚺", "🚹", "🆘", "🔑", "💈", "💣", "💡"
};

/* World Class */
class World {
private:
    std::string map[WIDTH][HEIGHT];
    std::string charMap[WIDTH][HEIGHT];
    std::stack<std::string> emojis;
public:
    World();
    void populate(Node* node);
    void populateRooms(Node* node);
    void populateBridges(Node* node);
    void connectRooms(Node* node, Node* parent);
    void fillCharMap();
    void draw();
    void drawCharMap();
};

#endif /* world_hpp */
