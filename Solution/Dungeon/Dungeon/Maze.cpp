
#include "Maze.h"
#include <LibGraph2.h>
#include <string>

using namespace LibGraph2;
using namespace std;

CMaze::CMaze()
{
  //Initialise les positions des cases
  for(size_t x = 0; x < m_maze.size(); ++x)
      for (size_t y = 0; y < m_maze[0].size(); ++y)
      {
          m_maze[x][y] = CCase{ (int)x, (int)y };
      }

  //Construction du labyrinthe
  string strMaze = " 1 _1 _5  3  2  3 _5  1  3|"
                   " 4 _1 _3| 1| 3| 1|_4  3  1|"
                   " 3  1|_5  3| 5| 1 _1 _3| 1|"
                   "_5 _3  4| 1| 1| 3  4|_0| 3|"
                   " 3 _4| 3| 3| 3| 1 _5 _3 _4|"
                   " 1|_0| 3|_5| 4| 1|_5 _3  3|"
                   " 1 _3 _1 _1 _1 _3 _1 _3  1|"
                   " 5 _1 _3 _1 _3 _1 _3 _1  5|"
                   " 4|_0|_0|_0|_0|_0|_0|_0| 4|"
                   "_6|_0|_0|_0|_0|_0|_0|_0|_6|";

  auto carIt = strMaze.begin();
  for (size_t y = 0; y < m_maze[0].size(); ++y)
    for (size_t x = 0; x < m_maze.size(); ++x)
    {
      char car = *carIt;
      
      if (*carIt == ' ')
        connectToBottomCase(m_maze[x][y]);
      carIt++;

      m_maze[x][y].statut(*carIt);
      carIt++;
      
      if (*carIt == ' ')
        connectToRightCase(m_maze[x][y]);
      carIt++;
    }
}



//Fin Solution