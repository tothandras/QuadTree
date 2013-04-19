//
//  main.cpp
//  NHF - QuadTree
//
//  Created by Tóth András on 2013.04.12..
//  Copyright (c) 2013 Tóth András. All rights reserved.
//

#include <iostream>
#include "QuadTree.hpp"

int main(int argc, const char * argv[])
{

    QuadTree<double> d(0);
    QuadTree<double>::pre_order_iterator iter;
    std::cout << d;
    return 0;
}
