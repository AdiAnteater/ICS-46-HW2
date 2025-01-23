#include "unordered_list.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string input_file = "src/random.txt";
    measure_lists(input_file);
    string file2 = "src/words.txt";
    measure_lists(file2);
    return 0;
}