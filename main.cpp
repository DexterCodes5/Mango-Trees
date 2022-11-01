#include <iostream>
#include <vector>
#include <algorithm>

void print(std::vector<std::vector<char>> &arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr.at(i).size(); j++) {
            std::cout << arr.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n\n";
}

void drawLines(std::vector<std::vector<char>> &arr, int n, int vertical, int horizontal) {
    for (int i = 0; i < n; i++) {
        std::vector<char>::iterator it = arr.at(i).begin();
        for (int i = 0; i < vertical; i++) {
            it++;
        }
        arr.at(i).insert(it,'|');
    }
    
    std::vector<char> v{'-','-','-','-','-','-','-'};
    std::vector<std::vector<char>>::iterator it = arr.begin();
    for (int i = 0; i < horizontal; i++) {
        it++;
    }
    arr.insert(it,v);
}

int countTrees(std::vector<std::vector<char>> &arr, int quadrant, size_t vertical, size_t horizontal) {
    int trees{};
    if (quadrant == 1) {
        for (size_t i = 0; i < vertical; i++) {
            for (size_t j = 0; j < horizontal; j++) {
                char curr = arr.at(i).at(j);
                if (curr == '#') {
                    trees++;
                }
            }
        }
    }
    else if (quadrant == 2) {
        for (size_t i = 0; i < vertical; i++) {
            for (size_t j = horizontal+1; j < arr.at(i).size(); j++) {
                char curr = arr.at(i).at(j);
                if (curr == '#') {
                    trees++;
                }
            }
        }
    }
    else if (quadrant == 3) {
        for (size_t i = vertical+1; i < arr.size(); i++) {
            for (size_t j = horizontal+1; j < arr.at(i).size(); j++) {
                char curr = arr.at(i).at(j);
                if (curr == '#') {
                    trees++;
                }
            }
        }
    }
    else if (quadrant == 4) {
        for (size_t i = vertical+1; i < arr.size(); i++) {
            for (size_t j = 0; j < horizontal; j++) {
                char curr = arr.at(i).at(j);
                if (curr == '#') {
                    trees++;
                }
            }
        }
    }
    return trees;
}

int smallestField(int q1, int q2, int q3, int q4) {
    std::vector<int> v{q1,q2,q3,q4};
    std::sort(v.begin(),v.end());
    return v.at(0);
}

int mangoTrees(std::vector<std::vector<char>> &arr, int n) {
    std::vector<std::vector<char>> orig = arr;
    int max_trees{};
    
    for (int i = 1; i < n; i++) {
    
        for (int j = 1; j < n; j++) {
        // Draw Lines
            arr = orig;
            drawLines(arr,n,i,j);
            print(arr);
            
            // Calc Quadrants
            int quadrant1 = countTrees(arr,1,j,i);
            int quadrant2 = countTrees(arr,2,j,i);
            int quadrant3 = countTrees(arr,3,j,i);
            int quadrant4 = countTrees(arr,4,j,i);
            max_trees = std::max(max_trees, smallestField(quadrant1, quadrant2, quadrant3, quadrant1));
        }
    }
    return max_trees;
}

int main(){
    std::vector<std::vector<char>> arr{
        {'.','#','#','.','.','.'},
        {'#','.','.','#','#','.'},
        {'.','#','.','.','.','.'},
        {'.','#','#','.','.','#'},
        {'#','.','.','#','#','.'},
        {'.','#','.','.','.','.'}
    };
    std::cout << mangoTrees(arr,6);
    //print(arr);
    
    return 0;
}
