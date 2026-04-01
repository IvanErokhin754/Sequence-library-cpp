#include <iostream>
#include <limits>
#include "UI.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "ImmutableListSequence.hpp"

void RunMutableArray()
{
    MutableArraySequence<int> seq;
    int choice = -1;

    while (choice) {
        std::cout << "MutableArraySequence menu: \n";
        std::cout << "1) Append\n";
        std::cout << "2) Prepend\n";
        std::cout << "3) InsertAt\n";
        std::cout << "4) Remove\n";
        std::cout << "5) Get\n";
        std::cout << "6) GetFirst\n";
        std::cout << "7) GetLast\n";
        std::cout << "8) GetSubsequence\n";
    }
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
        std::cout << "Choose type of sequence: \n";
        std::cout << "1) MutableArraySequence\n";
        std::cout << "2) ImmutableArraySequence\n";
        std::cout << "3) MutableListSequence\n";
        std::cout << "4) ImmutableListSequence\n";
        std::cout << "0) Exit\n";
        if (!(std::cin >> choice)){
            std::cout << "Invalid input\n";
            return;
        }
        
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
    

}