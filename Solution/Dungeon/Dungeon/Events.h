#pragma once

#include "Maze.h"
#include "Hero.h"


//Magasin
void ShopEvent(CHero& hero);

//Dropcde potion
void DropEvent(CHero& hero);

//Combat contre des ennemis normaux
void FightEvent(CHero& hero, CCase& monsterCase);

//Combat contre les boss
void BossFightEvent(CHero& hero, CCase& bossCase);


