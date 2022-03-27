//
//  mazestack.cpp
//  CS32_HW2
//
//  Created by Philip Huang on 1/29/22.
//

#include <stack>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
//Assumptions that can be made for this function according to spec.
//the maze array contains nRows rows (you couldn't check for this anyway);
//each string in the maze is of length nCols;
//the maze contains only Xs and dots when passed in to the function;
//the top and bottom rows of the maze contain only Xs, as do the left and right columns;
//sr and er are between 0 and nRows-1, and sc and ec are between 0 and nCols-1;
//maze[sr][sc] and maze[er][ec] are '.' (i.e., not walls)


//Push the starting coordinate (sr,sc) onto the coordinate stack and
//    update maze[sr][sc] to indicate that the algorithm has encountered
//    it (i.e., set maze[sr][sc] to have a value other than '.').
//While the stack is not empty,
//{   Pop the top coordinate off the stack. This gives you the current
//        (r,c) location that your algorithm is exploring.
//    If the current (r,c) coordinate is equal to the ending coordinate,
//        then we've solved the maze so return true!
//    Check each place you can move from the current cell as follows:
//        If you can move WEST and haven't encountered that cell yet,
//            then push the coordinate (r,c-1) onto the stack and update
//            maze[r][c-1] to indicate the algorithm has encountered it.
//        If you can move SOUTH and haven't encountered that cell yet,
//            then push the coordinate (r+1,c) onto the stack and update
//            maze[r+1][c] to indicate the algorithm has encountered it.
//        If you can move EAST and haven't encountered that cell yet,
//            then push the coordinate (r,c+1) onto the stack and update
//            maze[r][c+1] to indicate the algorithm has encountered it.
//        If you can move NORTH and haven't encountered that cell yet,
//            then push the coordinate (r-1,c) onto the stack and update
//            maze[r-1][c] to indicate the algorithm has encountered it.
//}
//There was no solution, so return false
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack<Coord> coordStack;
    Coord start(sr,sc);
    coordStack.push(start);
    maze[sr][sc] = 'P'; //P to signify a Path that we have already walked
    //int count = 1;
    while (!coordStack.empty()){
        Coord cur = coordStack.top();
        //cerr << count << " " << cur.r() << " " << cur.c() << '\n';
        //count++;
        Coord north(cur.r()-1,cur.c());
        Coord south(cur.r()+1,cur.c());
        Coord east(cur.r(),cur.c()+1);
        Coord west(cur.r(),cur.c()-1);
        coordStack.pop();// pop does not return anything, that is why we need to use top to gather the info before we pop
        if (cur.r() == er && cur.c() == ec){
            return true;
        }
        if (maze[west.r()][west.c()] == '.'){
            coordStack.push(west);
            maze[west.r()][west.c()] = 'P';
        }
        if (maze[south.r()][south.c()] == '.'){
            coordStack.push(south);
            maze[south.r()][south.c()] = 'P';
        }
        if (maze[east.r()][east.c()] == '.'){
            coordStack.push(east);
            maze[east.r()][east.c()] = 'P';
        }
        if (maze[north.r()][north.c()] == '.'){
            coordStack.push(north);
            maze[north.r()][north.c()] = 'P';
        }
    }
    return false;
}
       // Return true if there is a path from (sr,sc) to (er,ec)
       // through the maze; return false otherwise

//Test stack library
//int main()
//{
//    stack<Coord> coordStack;  // declare a stack of Coords
//
//    Coord a(5,6);
//    coordStack.push(a);          // push the coordinate (5,6)
//    coordStack.push(Coord(3,4)); // push the coordinate (3,4)
//    Coord b = coordStack.top();  // look at top item in the stack
//    coordStack.pop();            // remove the top item from stack
//    if (coordStack.empty())      // Is the stack empty?
//        cout << "empty!" << endl;
//    cout << coordStack.size() << endl; // num of elements
//    cout << b.r() << endl;
//    cout << b.c() << endl;
//
//}

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
