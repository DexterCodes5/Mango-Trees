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

void drawLines(std::vector<std::vector<char>> &arr, int n, int horizontal, int vertical) {
    // Horizontal Line
    std::vector<char> v{};
    for (int i = 0; i < n; i++) v.push_back('-');
    std::vector<std::vector<char>>::iterator it = arr.begin();
    for (int i = 0; i < horizontal; i++) {
        it++;
    }
    arr.insert(it,v);
    
    // Vertical Line
    for (int i = 0; i <= n; i++) {
        std::vector<char>::iterator it = arr.at(i).begin();
        for (int i = 0; i < vertical; i++) {
            it++;
        }
        if (i == horizontal) {
            arr.at(i).insert(it,'+');
        }
        else
            arr.at(i).insert(it,'|');
    }
}

int smallestField(int q1, int q2, int q3, int q4) {
    std::vector<int> v{q1,q2,q3,q4};
    std::sort(v.begin(),v.end());
    return v.at(0);
}

// 0(N^2)
std::vector<std::vector<int>> auxillaryMatrix(std::vector<std::vector<char>> arr) {
    std::vector<std::vector<int>> mat(arr.size());
    
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.at(i).size(); j++) { 
            if (arr.at(i).at(j) == '#')
                mat.at(i).push_back(1);
            else
                mat.at(i).push_back(0);
            
        }
    }
        
    // Fillin first row and column
    for (int i = 1; i < arr.size(); i++) {
        mat.at(0).at(i) += mat.at(0).at(i-1);
    }
    for (int i = 1; i < arr.size(); i++) {
        mat.at(i).at(0) += mat.at(i-1).at(0);
    }
    
    // updating the values of in the cells
    // as per the general formula
    for (int i = 1; i < mat.size(); i++) {
        for (int j = 1; j < mat.at(i).size(); j++) {
            
            // values in the cells of new array are updated
            if (arr.at(i).at(j) == '#')
                mat.at(i).at(j) = mat.at(i-1).at(j) + mat.at(i).at(j-1) - mat.at(i-1).at(j-1) + 1;
            else
                mat.at(i).at(j) = mat.at(i-1).at(j) + mat.at(i).at(j-1) - mat.at(i-1).at(j-1) + 0;
        }
    }
    
    return mat;
}

// 0(N^2)
int mangoTrees(std::vector<std::vector<char>> &arr, int n) {
    std::vector<std::vector<int>> matrix = auxillaryMatrix(arr);
    int max_trees{};
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // m[x,y] = 1 + m[x-1][y] + m[x][j-1] - m[i-1],[j-1] if tree at (x,y), else 1 will be 0. 0(1) formula
            int quadrant1 = matrix[i][j];
            int quadrant2 = matrix[i][n-1] - quadrant1;
            int quadrant3 = matrix[n-1][j] - quadrant1;
            int quadrant4 = matrix[n-1][n-1] - (quadrant1+quadrant2+quadrant3);
            max_trees = std::max(max_trees, smallestField(quadrant1, quadrant2, quadrant3, quadrant4));
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
    std::cout << mangoTrees(arr,6) << "\n";
    // propper field
    drawLines(arr,6,3,2);
    print(arr);
    
    return 0;
}
