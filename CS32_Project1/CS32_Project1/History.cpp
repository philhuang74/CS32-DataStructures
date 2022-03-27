//
//  History.cpp
//  CS32_Project1
//
//  Created by Philip Huang on 1/5/22.
//
#include<iostream>
using namespace std;
#include <cstdlib>

#include "History.h"

History::History(int nRows, int nCols){
    m_rows = nRows;
    m_cols = nCols;
    for (int row = 0; row < nRows; row++){
        for (int col = 0; col < nCols; col++){
            m_grid[row][col] = 0;
        }
    }
}

bool History::record(int r, int c){
    if (r<1 || r>m_rows || c<1 || c>m_cols){
        return false;
    }
    m_grid[r-1][c-1]++;
    return true;
    
}

void History::display() const {
    clearScreen();
    for (int row = 0; row < m_rows; row++){
        for (int col = 0; col < m_cols; col++){
            if (m_grid[row][col] >= 1 and m_grid[row][col] < 26){
                cout << (char)('A'+m_grid[row][col]-1);
            }
            else if (m_grid[row][col] >= 26){
                cout << 'Z';
            }
            else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    cout << '\n';
}


