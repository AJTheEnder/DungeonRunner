#include "Events.h"
#include "Monster.h"
#include "Boss.h"
#include <iostream>
#include <LibGraph2.h>
#include <time.h>
#include <random>
using namespace LibGraph2;
using namespace std;


//Procédure de l'évenement magasin
void ShopEvent(CHero& hero)
{
	ILibGraph2* libgraph = GetLibGraph2();
	int choice;
	hero.getStats();
	cin.clear();
	cout << "Upgrade : \n 1. Sword\n 2. Armor\n 3. Exit\n\n Choice : ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		if (hero.getGold() >= 15 && hero.getSwordLvl() < 5) {
			hero.swordLvlUp();
			hero.setGold(-15);
			hero.getStats();
		}
		else if (hero.getSwordLvl() >= 5) {
			cout << "Epee deja au niveau max\n";
			hero.getStats();
			}
			else {
			cout << "Vous n'avez pas assez de gold\n";
			hero.getStats();
			}
		break;
	case 2:
		if (hero.getGold() >= 15 && hero.getArmorLvl() < 5) {
			hero.armorLvlUp();
			hero.setGold(-15);
			hero.getStats();
		}
		else if (hero.getArmorLvl() >= 5) {
			cout << "Armure deja au niveau max\n";
			hero.getStats();
		}
		else {
			cout << "Vous n'avez pas assez de gold\n";
			hero.getStats();
		}
		break;
	case 3:
		hero.getStats();
		break;
	default:
		cout << "Mauvais choix, le shop se ferme\n";
		break;
	}
}

//Procédure de l'évenement de drop
void DropEvent(CHero& hero)
{
	hero.setHealth(2);
	hero.setGold(5);
	hero.getStats();
}

//Procédure de l'évenement combat
void FightEvent(CHero& hero, CCase& monsterCase)
{
	srand(time(0));
	ILibGraph2* libgraph = GetLibGraph2();
	//Aspect graphique (A FAIRE)
	//Création du monstre avec un type en fonction de la position de la case dans le labyrinthe
	libgraph->drawBitmap("img/tiles/background.png", CPoint{ 0, 0 }, 30 * 110 / 640.0f);
	CMonster ennemy;
	if (monsterCase.getPosY() <= 1)
		ennemy.setType(0);
	if (monsterCase.getPosY() > 1 && monsterCase.getPosY() <= 4)
	{
		if (rand() % 2 == 0)
			ennemy.setType(1);
		else
			ennemy.setType(3);
	}
	if (monsterCase.getPosY() > 4)
	{
		if (rand() % 2 == 0)
			ennemy.setType(2);
		else
			ennemy.setType(4);
	}
	switch (ennemy.getType())
	{
	case(0):
		libgraph->drawBitmap("img/tiles/Monster/neutral_slime.png", CPoint{ 10, 60 }, 30 * 40 / 640.0f);
		break;
	case(1):
		libgraph->drawBitmap("img/tiles/Monster/neutral_bat.png", CPoint{ 10, 60 }, 30 * 40 / 640.0f);
		break;
	case(2):
		libgraph->drawBitmap("img/tiles/Monster/neutral_skeleton.png", CPoint{ 10, 60 }, 30 * 40 / 640.0f);
		break;
	case(3):
		libgraph->drawBitmap("img/tiles/Monster/neutral_ghost.png", CPoint{ 10, 60 }, 30 * 40 / 640.0f);
		break;
	case(4):
		libgraph->drawBitmap("img/tiles/Monster/neutral_unknown.png", CPoint{ 10, 60 }, 30 * 40 / 640.0f);
		break;
	}
	libgraph->drawBitmap("img/neutral_hero.png", CPoint{ 165, 60 }, 30 * 40 / 640.0f);
	Sleep(1500);
	int monsterHealth = ennemy.getMonsterHealth();
	bool fightIsOn = true;
	//Affichage et boucle de combat
	while (fightIsOn == true)
	{
		//Tour du hero
		if (fightIsOn == true)
		{
			//L'ennemie prend des dégats du hero
			monsterHealth -= hero.getSwordLvl();
			//Si les pv de l'ennemie tombe à zéro 
			if (monsterHealth <= 0)
			{
				//L'ennemie meurt, le hero gagne de l'or et le combat est terminé
				monsterHealth = 0;
				ennemy.Die();
				hero.setGold(ennemy.getMonsterValue());
				fightIsOn = false;
				hero.getStats();
			}
		}

		//Tour de l'ennemie
		if (fightIsOn == true)
		{
			//Le hero prend des dégats de l'ennemie
			hero.setHealth(-(ennemy.getMonsterAD() - hero.getArmorLvl()));
			//Si les pv de l'ennemie tombe à zéro 
			if (hero.getHealth() <= 0)
			{
				//Le hero meurt, le combat est terminé, GameOver
				fightIsOn = false;
				hero.getStats();
				hero.gameOver();
			}
		}
	}
}

void BossFightEvent(CHero& hero, CCase& bossCase)
{
	srand(time(0));
	ILibGraph2* libgraph = GetLibGraph2();
	//Aspect graphqie (A FAIRE)
	//Création du boss (soit dragon, soit golem)
	libgraph->drawBitmap("img/tiles/background.png", CPoint{ 0, 0 }, 30 * 110 / 640.0f);
	CBoss ennemy;
	if (bossCase.getPosX() == 0)
		ennemy.setBossType(0);
	if (bossCase.getPosX() == 8)
		ennemy.setBossType(1);
	switch (ennemy.getBossType())
	{
	case(0):
		libgraph->drawBitmap("img/tiles/Monster/neutral_golem.png", CPoint{ 10, 40 }, 30 * 45 / 640.0f);
		break;
	case(1):
		libgraph->drawBitmap("img/tiles/Monster/neutral_dragon.png", CPoint{ 10, 40 }, 30 * 45 / 640.0f);
		break;
	}
	libgraph->drawBitmap("img/neutral_hero.png", CPoint{ 165, 60 }, 30 * 40 / 640.0f);
	Sleep(1500);
	int bossHealth = ennemy.getBossHealth();
	int heroHealth = hero.getHealth();
	bool fightIsOn = true;
	//Affichage et boucle de combat
	while (fightIsOn == true)
	{
		//Tour du hero
		if (fightIsOn == true)
		{
			//Le boss prend des dégats du hero
			bossHealth -= hero.getSwordLvl();
			//Si les pv de l'ennemie tombe à zéro 
			if (bossHealth <= 0)
			{
				//Le boss meurt, le combat s'arrete, le hero gagne la partie
				bossHealth = 0;
				fightIsOn = false;
				ennemy.WinTheGame(hero);
			}
		}

		//Tour de l'ennemie
		if (fightIsOn == true)
		{
			//Le hero prend des dégats de l'ennemie
			hero.setHealth(-(ennemy.getBossAD() - hero.getArmorLvl()));
			//Si les pv de l'ennemie tombe à zéro 
			if (hero.getHealth() <= 0)
			{
				//Le hero meurt, le combat est terminé, GameOver
				fightIsOn = false;
				hero.gameOver();
			}
		}
	}
}

