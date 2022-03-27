////
////  maze.cpp
////  CS32_HW3
////
////  Created by Philip Huang on 2/5/22.
////
//
#include <iostream>
using namespace std;

class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};

//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
//Assumptions that can be made for this function according to spec.
//the maze array contains nRows rows (you couldn't check for this anyway);
//each string in the maze is of length nCols;
//the maze contains only Xs and dots when passed in to the function;
//the top and bottom rows of the maze contain only Xs, as do the left and right columns;
//sr and er are between 0 and nRows-1, and sc and ec are between 0 and nCols-1;
//maze[sr][sc] and maze[er][ec] are '.' (i.e., not walls)


//If the start location is equal to the ending location, then we've
//    solved the maze, so return true.
//Mark the start location as visted.
//For each of the four directions,
//    If the location one step in that direction (from the start
//        location) is unvisited, and there is a path starting from that
//        location (and ending at the same ending location as in the
//        current call),
//            then return true.
//Return false.
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    if (sr == er and sc == ec){ //if current point equals our destination, return true
        return true;
    }
    maze[sr][sc] = 'v'; //mark the current point as visited so we don't accidently go back
    //West
    if (maze[sr][sc-1] == '.' and pathExists(maze,nRows,nCols,sr,sc-1,er,ec)){
        return true;
    }
    //South
    if (maze[sr+1][sc]=='.' and pathExists(maze, nRows,nCols,sr+1,sc,er,ec)){
        return true;
    }
    //East
    if (maze[sr][sc+1] == '.' and pathExists(maze,nRows,nCols,sr,sc+1,er,ec)){
        return true;
    }
    //North
    if (maze[sr-1][sc] == '.' and pathExists(maze,nRows,nCols,sr-1,sc,er,ec)){
        return true;
    }

    return false;
}
       // Return true if there is a path from (sr,sc) to (er,ec)
       // through the maze; return false otherwise

//
//
//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X.X..X...X",
//        "X....XXX.X",
//        "X.XXXX.X.X",
//        "X......XXX",
//        "X.XX.X...X",
//        "X.X..X.X.X",
//        "X.X.XXXX.X",
//        "X.X...X..X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 4,6, 1,1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
//
