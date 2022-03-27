//
//  main.cpp
//  CS32_Project1
//
//  Created by Philip Huang on 1/5/22.
//

// garks.cpp

//#include <iostream>
//#include <string>
//#include <random>
//#include <utility>
//#include <cstdlib>
//using namespace std;

//#include "Game.h"

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

#include "Game.h"
//This is a pair
int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

//PASSED
//#include "Gark.h"
//int main()
//{}

//PASSED
//#include "Player.h"
//int main()
//{}

//PASSED
//#include "History.h"
//int main()
//{}

//PASSED
//#include "globals.h"
//int main()
//{}

//PASSED
//#include "Game.h"
//int main()
//{}

//PASSED
//#include "Mesa.h"
//int main()
//{}

//PASSED
//#include "Game.h"
//#include "Game.h"
//#include "Mesa.h"
//#include "Mesa.h"
//#include "History.h"
//#include "History.h"
//#include "Player.h"
//#include "Player.h"
//#include "Gark.h"
//#include "Gark.h"
//#include "globals.h"
//#include "globals.h"
//int main()
//{}

//PASSED
//#include "History.h"
//int main()
//{
//    History h(2, 2);
//    h.record(1, 1);
//    h.display();
//}

//PASSED
//#include "Gark.h"
//int main()
//{
//    Gark g(nullptr, 1, 1);
//}

//PASSED
//#include "Player.h"
//int main()
//{
//    Player p(nullptr, 1, 1);
//}

//PASSED
//#include "Mesa.h"
//int main()
//{
//    Mesa m(10, 20);
//    m.addPlayer(2, 2);
//}

//PASSED
//#include "globals.h"
//#include "Player.h"
//#include "Mesa.h"
//int main()
//{
//    Mesa m(10, 20);
//    Player p(&m, 2, 3);
//}

//PASSED
//#include "Mesa.h"
//#include "Player.h"
//int main()
//{
//    Mesa m(10, 20);
//    Player p(&m, 2, 3);
//}

//PASSED
//#include "Player.h"
//#include "Mesa.h"
//int main()
//{
//    Mesa m(10, 20);
//    Player p(&m, 2, 3);
//}

//PASSED
//#include "History.h"
//#include "Mesa.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    Mesa m(1, 3);
//    m.history().record(1, 2);
//    Mesa m2(1, 2);
//    m2.history().record(1, 1);
//    m.history().display();
//    cout << "===" << endl;
//}

//PASSED
//#include "Mesa.h"
//#include "Player.h"
//#include "History.h"
//#include "globals.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    Mesa m(3, 4);
//    m.addPlayer(2, 4);
//    m.addGark(2, 3);
//    m.addGark(3, 4);
//    m.player()->moveOrAttack(LEFT);
//    m.player()->moveOrAttack(DOWN);
//    m.player()->moveOrAttack(LEFT);
//    m.player()->moveOrAttack(UP);
//    m.player()->moveOrAttack(LEFT);
//    m.player()->moveOrAttack(DOWN);
//    m.history().display();
//    cout << "====" << endl;
//}

//Passed Fail
//#include "Gark.h"
//#include "Mesa.h"
//int main()
//{
//    Mesa m(10, 20);
//    Player p(&m, 2, 3);
//    Gark g(&m, 1, 1);
//}

//Passed Fail
//#include "Player.h"
//#include "Mesa.h"
//int main()
//{
//    Mesa m(10, 20);
//    Player p(&m, 2, 3);
//    Gark g(&m, 1, 1);
//}

//Passed Fail
//#include "globals.h"
//#include "Gark.h"
//#include "Player.h"
//int main()
//{
//    Mesa m(10, 10);
//}

//Passed Fail
//#include "History.h"
//int main()
//{
//    History h;
//}
