
#pragma once

#include "Case.h"
#include <array>

class CMaze
{
public:
  using maze_t = std::array<std::array<CCase, 10>, 9>; //Type du tableau 2D

private:
  maze_t m_maze;                //Tableau 2D des cases.

  void connectToRightCase(CCase& cs) { cs.setRightCase(&m_maze[cs.getPosX() + 1L][cs.getPosY()]); }

  void connectToBottomCase(CCase& cs) { cs.setBottomCase(&m_maze[cs.getPosX()][cs.getPosY() + 1L]); };

public:
  CMaze();  //Initialise le labyrinthe

  maze_t& getMaze() { return m_maze; }        //Retourne le tableau 2D des cases du labyrinthe
};
