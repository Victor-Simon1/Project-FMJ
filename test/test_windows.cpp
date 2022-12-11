#include "scene.h"
#include <iostream>



int main()
{
    
    Scene scene;
    std::cout << "Init scene" << std::endl;
    scene.initialise();
    scene.run();

    scene.shutdown();

    return 0;
}