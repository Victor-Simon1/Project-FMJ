#include "scene.h"
#include <iostream>



int main(int argc, char* argv[])
{
    Scene scene;
    std::cout << "Init scene" << std::endl;
    if(argc >= 2)
    {
        for(int i=1;i< argc;i++)
        {
            std::cout << argv[i] << std::endl;
            scene.load_obj_file(argv[i]);
        }
    }
 
    scene.initialise();
    scene.run();

    scene.shutdown();

    return 0;
}