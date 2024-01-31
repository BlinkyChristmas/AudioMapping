//
//  main.cpp
//  AudioMapping
//
//  Created by Charles Kerr on 1/30/24.
//

#include <iostream>
#include "MusicController.hpp"
int main(int argc, const char * argv[]) {
    
    auto devices = MusicController::getSoundDevices() ;
    for (const auto &[number,name]:devices) {
        std::cout << "Device# " << number << " Name: "<<name << std::endl;
    }
    return 0;
}
