#include <iostream>
#include "UI.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "ImmutableListSequence.hpp"

void RunMutableArray()
{

}

void RunImmutableArray()
{
    
}

void RunMutableList()
{
    
}

void RunImmutableList()
{
    
}

void StartUi()
{  
    int choice;
    while (choice != 0) {
        switch (choice) {
            case 1: 
                RunMutableArray();
                break;
            case 2:
                RunImmutableArray();
                break;
            case 3:
                RunMutableList();
                break;
            case 4:
                RunImmutableList();
                break;
            case 0:
                break;
            default:
                std::cout << "Unknown command\n";
        }
    }
    std::cout << "Choose type of sequence: \n";
    std::cout << "1) MutableArraySequence\n";
    std::cout << "2) ImmutableArraySequence\n";
    std::cout << "3) MutableListSequence\n";
    std::cout << "4) ImmutableListSequence\n";
    std::cout << "0) Exit\n";

}