//
//  BSP.hpp
//  generativeBSP
//
//  Created by Derik Gagnon on 1/30/19.
//  Copyright © 2019 Derik Gagnon. All rights reserved.
//

#ifndef BSP_hpp
#define BSP_hpp

#include <stdio.h>

class Node {
private:
    int mHeight, mWidth;
    Node * mLChild = NULL, * mRChild = NULL;
    
public:
    int getHeight(){return mHeight;}
    int getWidth(){return mWidth;}
    void setHeight(int height);
    void setWidth(int width);
};

class BspTree {
    
};

#endif /* BSP_hpp */
