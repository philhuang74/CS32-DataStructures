//
//  Game.hpp
//  CS32_Project1
//
//  Created by Philip Huang on 1/5/22.
//

#ifndef Game_hpp
#define Game_hpp

class Mesa;

int decodeDirection(char dir);

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

#endif /* Game_hpp */
