//
//  main.cpp
//  generativeBSP
//
//  Created by Derik Gagnon on 1/30/19.
//  Copyright © 2019 Derik Gagnon. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include "BSP.hpp"

const int HEIGHT = 50, WIDTH = 50;

int main() {
    
    std::string world[HEIGHT][WIDTH];
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            world[i][j] = "#";
        }
    }
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << world[i][j];
        }
        std::cout << "\n";
    }
    
    
    std::cin.get();
    return 0;
}
