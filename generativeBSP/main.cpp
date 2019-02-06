//
//  main.cpp
//  generativeBSP
//
//  Created by Derik Gagnon on 1/30/19.
//  Copyright © 2019 Derik Gagnon. All rights reserved.
//

#include "BSP.hpp"
#include "world.hpp"

int main() {
    
    std::srand(time(NULL));
    

    World world = World();
 
    BspTree tree = BspTree();
    Node* root = tree.getRoot();
    std::cout << root->getHeight() << " " << root->getWidth() << " " << root->mLChild  << std::endl;
    tree.expand(4);
    std::cout << root->getHeight() << " " << root->getWidth() << " " << root->mLChild->getHeight() << std::endl;
    tree.visualize();
    world.populate(root);
    world.draw();


    // std::cin.get();
    return 0;
}
