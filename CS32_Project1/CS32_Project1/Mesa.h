//
//  Mesa.hpp
//  CS32_Project1
//
//  Created by Philip Huang on 1/5/22.
//

#ifndef Mesa_hpp
#define Mesa_hpp

#include "History.h"
#include "globals.h" //Might not need this, but its good to include.h files that this class implementation uses so users don't have to wonder where globals.h is

class Player;
class Gark;

class Mesa
{
  public:
        // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     garkCount() const;
    int     numGarksAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    History& history();

        // Mutators
    bool   addGark(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackGarkAt(int r, int c, int dir);
    bool   moveGarks();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Gark*   m_garks[MAXGARKS];
    int     m_nGarks;
    History m_History;
};

#endif /* Mesa_hpp */
