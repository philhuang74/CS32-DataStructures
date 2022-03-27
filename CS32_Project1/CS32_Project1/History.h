//
//  History.hpp
//  CS32_Project1
//
//  Created by Philip Huang on 1/5/22.
//

#ifndef History_H
#define History_H

#include "globals.h"

class History
    {
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_rows;
        int m_cols;
        int m_grid[MAXROWS][MAXCOLS];
    };

#endif /* History_hpp */
