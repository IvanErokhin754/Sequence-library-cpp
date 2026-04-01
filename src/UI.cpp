#include <iostream>
#include <limits>
#include "UI.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "ImmutableListSequence.hpp"

void ClearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename Seq>
void PrintSequence(const Seq& seq) {
    std::cout << "[ ";
    for (size_t i = 0; i < seq.GetLength(); i++) {
        std::cout << seq.Get(i) << ' ';
    }
    std::cout << "]\n";
}

template<typename Seq>
void PrintSequenceWithIterator(const Seq& seq)  {
    std::cout << "[ ";
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "]\n";
}

int DoubleValue(const int& value) {
    return value * 2;
}

bool IsEven(const int& value) {
    return value % 2 == 0;
}

int Sum(const int& value1, const int& value2) {
    return value1 + value2;
}

bool GreaterThanTen(const int& value) {
    return value > 10;
}

void RunMutableArray() {
    MutableArraySequence<int> seq;
    int choice = -1;
    while (choice) {
        std::cout << "\nMutableArraySequence menu: \n";
        std::cout << "1) Append\n";
        std::cout << "2) Prepend\n";
        std::cout << "3) InsertAt\n";
        std::cout << "4) Remove\n";
        std::cout << "5) Get\n";
        std::cout << "6) GetFirst\n";
        std::cout << "7) GetLast\n";
        std::cout << "8) GetSubsequence\n";
        std::cout << "9) Concat\n";
        std::cout << "10) Print\n";
        std::cout << "11) Print with iterator\n";
        std::cout << "12) Map (*2)\n";
        std::cout << "13) Where (even)\n";
        std::cout << "14) Reduce (sum)\n";
        std::cout << "15) FindFirst (>10)\n";
        std::cout << "0) Back\n";
        std::cout << "Your choice: ";
        if (!(std::cin >> choice)) {
            ClearInput();
            std::cout << "Invalid input\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    int value;
                    std::cout << "Value: ";
                    std::cin >> value;
                    seq.Append(value);
                    break;
                }

                case 2: {
                    int value;
                    std::cout << "Value: ";
                    std::cin >> value;
                    seq.Prepend(value);
                    break;
                }
                
                case 3: {
                    size_t index;
                    int value;
                    std::cout << "Index and value: ";
                    std::cin >> index >> value;
                    seq.InsertAt(index, value);
                    break;
                }

                case 4: {
                    size_t index;
                    std::cout << "Index: ";
                    std::cin >> index;
                    seq.Remove(index);
                    break;
                }

                case 5: {
                    size_t index;
                    std::cout << "Index: ";
                    std::cin >> index;
                    std::cout << "Element = " << seq.Get(index) << '\n';
                    break;
                }

                case 6: {
                    std::cout << "First = " << seq.GetFirst() << '\n';
                    break;
                }

                case 7: {
                    std::cout << "Last = " << seq.GetLast() << '\n';
                    break;
                }

                case 8: {
                    size_t left, right;
                    std::cout << "Start and end indices: ";
                    std::cin >> left >> right;
                    Sequence<int>* sub = seq.GetSubsequence(left, right);
                    std::cout << "Subsequence: [ ";
                    for (size_t i = 0; i < sub->GetLength(); i++) {
                        std::cout << sub->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete sub;
                    break;
                }

                case 9: {
                    int n, x;
                    std::cout << "How many elements in second sequence? ";
                    std::cin >> n;

                    MutableArraySequence<int> other;
                    std::cout << "Enter elements: ";
                    
                    for (int i = 0; i < n; i++) {
                        std::cin >> x;
                        other.Append(x);
                    }

                    Sequence<int>* result = seq.Concat(other);
                    std::cout << "Concatenation: [ ";
                    for (size_t i = 0; i < result->GetLength(); i++) {
                        std::cout << result->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete result;
                    break;
                }

                case 10: {
                    PrintSequence(seq);
                    break;
                }

                case 11: {
                    PrintSequenceWithIterator(seq);
                    break;
                }

                case 12: {
                    Sequence<int>* result = seq.Map(DoubleValue);
                    std::cout << "Mapped: [ ";
                    for (size_t i = 0; i < result->GetLength(); i++) {
                        std::cout << result->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete result;
                    break;
                }

                case 13: {
                    Sequence<int>* result = seq.Where(IsEven);
                    std::cout << "Filtered: [ ";
                    for (size_t i = 0; i < result->GetLength(); i++) {
                        std::cout << result->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete result;
                    break;
                }

                case 14: {
                    int result = seq.Reduce(Sum, 0);
                    std::cout << "Reduce result = " << result << '\n';
                    break;
                }
                
                case 15: {
                    long long pos = seq.FindFirst(GreaterThanTen);
                    std::cout << "FindFirst result = " << pos << '\n';
                    break;
                }

                case 0: 
                    break;
                
                default:
                    std::cout << "Unknown command\n";
                    break;

            } // switch
        } // try
        catch (const std::exception& e){
            std::cout << "Error: " << e.what() << '\n';
        }
    } // while
}

void RunImmutableArray() {   
    ImmutableArraySequence<int>* seq = new ImmutableArraySequence<int>();
    int choice = -1;
    while (choice) {
        std::cout << "\nImmutableArraySequence menu: \n";
        std::cout << "1) Append\n";
        std::cout << "2) Prepend\n";
        std::cout << "3) InsertAt\n";
        std::cout << "4) Remove\n";
        std::cout << "5) Get\n";
        std::cout << "6) GetFirst\n";
        std::cout << "7) GetLast\n";
        std::cout << "8) GetSubsequence\n";
        std::cout << "9) Concat\n";
        std::cout << "10) Print\n";
        std::cout << "11) Print with iterator\n";
        std::cout << "12) Map (*2)\n";
        std::cout << "13) Where (even)\n";
        std::cout << "14) Reduce (sum)\n";
        std::cout << "15) FindFirst (>10)\n";
        std::cout << "0) Back\n";
        std::cout << "Your choice: ";
        if (!(std::cin >> choice)) {
            ClearInput();
            std::cout << "Invalid input\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    int value;
                    std::cout << "Value: ";
                    std::cin >> value;
                    auto* newSeq = seq->Append(value);
                    delete seq;
                    seq = newSeq;
                    break;
                }

                case 2: {
                    int value;
                    std::cout << "Value: ";
                    std::cin >> value;
                    auto* newSeq = seq->Prepend(value);
                    delete seq;
                    seq = newSeq;
                    break;
                }
                
                case 3: {
                    size_t index;
                    int value;
                    std::cout << "Index and value: ";
                    std::cin >> index >> value;
                    auto* newSeq = seq->InsertAt(index, value);
                    delete seq;
                    seq = newSeq;
                    break;
                }

                case 4: {
                    size_t index;
                    std::cout << "Index: ";
                    std::cin >> index;
                    auto* newSeq = seq->Remove(index);
                    delete seq;
                    seq = newSeq;
                    break;
                }

                case 5: {
                    size_t index;
                    std::cout << "Index: ";
                    std::cin >> index;
                    std::cout << "Element = " << seq->Get(index) << '\n';
                    break;
                }

                case 6: {
                    std::cout << "First = " << seq->GetFirst() << '\n';
                    break;
                }

                case 7: {
                    std::cout << "Last = " << seq->GetLast() << '\n';
                    break;
                }

                case 8: {
                    size_t left, right;
                    std::cout << "Start and end indices: ";
                    std::cin >> left >> right;
                    Sequence<int>* sub = seq->GetSubsequence(left, right);
                    std::cout << "Subsequence: [ ";
                    for (size_t i = 0; i < sub->GetLength(); i++) {
                        std::cout << sub->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete sub;
                    break;
                }

                case 9: {
                    int n, x;
                    std::cout << "How many elements in second sequence? ";
                    std::cin >> n;

                    ImmutableArraySequence<int>* other = new ImmutableArraySequence<int>();
                    std::cout << "Enter elements: ";
                    
                    for (int i = 0; i < n; i++) {
                        std::cin >> x;
                        auto* newOther = other->Append(x);
                        delete other;
                        other = newOther;
                    }

                    Sequence<int>* result = seq->Concat(*other);
                    std::cout << "Concatenation: [ ";
                    for (size_t i = 0; i < result->GetLength(); i++) {
                        std::cout << result->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete other;
                    delete result;
                    break;
                }

                case 10: {
                    PrintSequence(*seq);
                    break;
                }

                case 11: {
                    PrintSequenceWithIterator(*seq);
                    break;
                }

                case 12: {
                    Sequence<int>* result = seq->Map(DoubleValue);
                    std::cout << "Mapped: [ ";
                    for (size_t i = 0; i < result->GetLength(); i++) {
                        std::cout << result->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete result;
                    break;
                }

                case 13: {
                    Sequence<int>* result = seq->Where(IsEven);
                    std::cout << "Filtered: [ ";
                    for (size_t i = 0; i < result->GetLength(); i++) {
                        std::cout << result->Get(i) << ' ';
                    }
                    std::cout << "]\n";
                    delete result;
                    break;
                }

                case 14: {
                    int result = seq->Reduce(Sum, 0);
                    std::cout << "Reduce result = " << result << '\n';
                    break;
                }
                
                case 15: {
                    long long pos = seq->FindFirst(GreaterThanTen);
                    std::cout << "FindFirst result = " << pos << '\n';
                    break;
                }

                case 0: 
                    break;
                
                default:
                    std::cout << "Unknown command\n";
                    break;
            } // switch
        } // try
        catch (const std::exception& e){
            std::cout << "Error: " << e.what() << '\n';
        }
    } // while
    delete seq;
}

void RunMutableList() {
    
}

void RunImmutableList()
{
    
}

void StartUi()
{  
    int choice = -1;
    while (choice) {
        std::cout << "\nChoose type of sequence: \n";
        std::cout << "1) MutableArraySequence\n";
        std::cout << "2) ImmutableArraySequence\n";
        std::cout << "3) MutableListSequence\n";
        std::cout << "4) ImmutableListSequence\n";
        std::cout << "0) Exit\n";
        std::cout << "Your choice: ";
        if (!(std::cin >> choice)){
            ClearInput();
            std::cout << "Invalid input\n";
            continue;
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
                break;
        }
    }
    

}