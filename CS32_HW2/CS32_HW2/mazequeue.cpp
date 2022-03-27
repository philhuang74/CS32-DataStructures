//
//  mazestack.cpp
//  CS32_HW2
//
//  Created by Philip Huang on 1/29/22.
//

//#include <queue>
//#include <iostream>
//using namespace std;
//
//class Coord
//{
//  public:
//    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//  private:
//    int m_r;
//    int m_c;
//};
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
////Assumptions that can be made for this function according to spec.
////the maze array contains nRows rows (you couldn't check for this anyway);
////each string in the maze is of length nCols;
////the maze contains only Xs and dots when passed in to the function;
////the top and bottom rows of the maze contain only Xs, as do the left and right columns;
////sr and er are between 0 and nRows-1, and sc and ec are between 0 and nCols-1;
////maze[sr][sc] and maze[er][ec] are '.' (i.e., not walls)
//
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
//    queue<Coord> coordQueue;
//    Coord start(sr,sc);
//    coordQueue.push(start);
//    maze[sr][sc] = 'P'; //P to signify a Path that we have already walked
////    int count = 1;
//    while (!coordQueue.empty()){
//        Coord cur = coordQueue.front();
////        cerr << count << " " << cur.r() << " " << cur.c() << '\n';
////        count++;
//        Coord north(cur.r()-1,cur.c());
//        Coord south(cur.r()+1,cur.c());
//        Coord east(cur.r(),cur.c()+1);
//        Coord west(cur.r(),cur.c()-1);
//        coordQueue.pop();// pop does not return anything, that is why we need to use front to gather the info before we pop
//        if (cur.r() == er && cur.c() == ec){
//            return true;
//        }
//        if (maze[west.r()][west.c()] == '.'){
//            coordQueue.push(west);
//            maze[west.r()][west.c()] = 'P';
//        }
//        if (maze[south.r()][south.c()] == '.'){
//            coordQueue.push(south);
//            maze[south.r()][south.c()] = 'P';
//        }
//        if (maze[east.r()][east.c()] == '.'){
//            coordQueue.push(east);
//            maze[east.r()][east.c()] = 'P';
//        }
//        if (maze[north.r()][north.c()] == '.'){
//            coordQueue.push(north);
//            maze[north.r()][north.c()] = 'P';
//        }
//    }
//    return false;
//}
//       // Return true if there is a path from (sr,sc) to (er,ec)
//       // through the maze; return false otherwise
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
//
////    const char a = 'c';
////    cout << isalpha(a) << endl;
////    switch(a){
////        case ('a'):
////        case ('c'):
////            cout << "hi there, I am a character." << endl;
////    }
//    char b = '#';
//    cout << (char) tolower(b) << endl;
//    cout << isalpha(b) << endl;
//
//}

