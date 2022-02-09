#include <Windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <LibGraph2.h>
#include "maze.h"
#include "Events.h"
#include "HeroOnMap.h"
#include "Hero.h"
#include <iostream>

using namespace std;
using namespace LibGraph2;

//Procédure d'affichage des cases
void drawCase(CCase& cs, bool bBackOrFront);

//Procédure de traitement d'évenement des cases
void CaseEvent(CCase& currCase, CHero& hero);

//Taille d'affichage des cases
const CSize g_szCase{ 30, 30 };

ILibGraph2* libgraph = GetLibGraph2();

int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmdLine,
  int nCmdShow)
{
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

  //Récupération de l'objet principal de LibGraph 2
  ILibGraph2* libgraph = GetLibGraph2();
  
  //Création de l'objet maze et de son nombre de cases
  CMaze maze;
  size_t nNbCasesX = maze.getMaze().size();
  size_t nNbCasesY = maze.getMaze()[0].size();

  //Création de l'objet hero dans le labyrinthe et de l'objet hero possédant les stats
  CHeroOnMap heroPicture{ 4,0 };
  CHero hero;

  //Affiche un message d'aide
  libgraph->guiMessageBox("Aide", "Utilisez les touches directionnelles pour vous déplacer", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnInformation);
  //Affiche la fenêtre graphique avec une taille par défaut
  libgraph->show(CSize{ nNbCasesX*g_szCase.m_fWidth, nNbCasesY*g_szCase.m_fHeight });

  evt e;  //Evénement LibGraph 2
  //Boucle principale d'événements
  while (libgraph->waitForEvent(e))
  {
    switch (e.type)  //En fonction du type d'événement
    {
    case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
      //Utilisation des fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
      libgraph->beginPaint();
      {
          
        //Trace les fonds des cases
        for (auto& col : maze.getMaze())
          for (auto cs : col)
            drawCase(cs, true);
        //Trace les bordures des cases
        for (auto& col : maze.getMaze())
          for (auto cs : col)
            drawCase(cs, false);
        //Affichage hero
        libgraph->drawBitmap("img/neutral_hero.png", CPoint{ heroPicture.getPosX() * g_szCase.m_fWidth, heroPicture.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10 / 640.0f);
      }
      libgraph->endPaint();
      break;
    case evt_type::evtKeyDown:  //Enfoncement d'une touche
      switch (e.vkKeyCode) //En fonction de la touche enfoncée
      {
      //Bouton flèche de droite
      case VK_RIGHT:
          if (maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()].getRightCase() != nullptr) //si les cases sont connectées
          {
              heroPicture.setPosX(heroPicture.getPosX() + 1); //le héro avance de 1 vers la droite
              CaseEvent(maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()], hero); //Détection d'un event sur la case
          }
          libgraph->askForRefresh(); //Rafraichissement de la fenêtre
          break;
      //Bouton flèche du haut
      case VK_UP:
          if (maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()].getTopCase() != nullptr)//si les cases sont connectées
          {
              heroPicture.setPosY(heroPicture.getPosY() - 1); //le héro avance de 1 vers le haut
              CaseEvent(maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()], hero);//Détection d'un event sur la case
          }
          libgraph->askForRefresh(); //Rafraichissement de la fenêtre
          break;
      //Bouton flèche de gauche
      case VK_LEFT:
          if (maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()].getLeftCase() != nullptr)//si les cases sont connectées
          {
              heroPicture.setPosX(heroPicture.getPosX() - 1); //le héro avance de 1 vers la gauche
              CaseEvent(maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()], hero);//Détection d'un event sur la case
          }
          libgraph->askForRefresh(); //Rafraichissement de la fenêtre
          break;
      //Bouton flèche du bas
      case VK_DOWN:
          if (maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()].getBottomCase() != nullptr)//si les cases sont connectées
          {
              heroPicture.setPosY(heroPicture.getPosY() + 1); //le héro avance de 1 vers le bas
              CaseEvent(maze.getMaze()[heroPicture.getPosX()][heroPicture.getPosY()], hero);//Détection d'un event sur la case
              
          }
          libgraph->askForRefresh(); //Rafraichissement de la fenêtre
          break;
      }
      break;
    }
  }
  //Libération de l'objet principal de LibGraph 2
  ReleaseLibGraph2();
  return 0;
}

void drawCase(CCase& cs, bool bBackOrFront)
{
  

  //Affichage du fond de la case
  if (bBackOrFront)
  {
    //Affichage graphique en fonction du type de la case
      switch (cs.getStatut())
    {
    //Case de lave 
      case('0'):
        libgraph->drawBitmap("img/tiles/lava.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
        break;
    //Case de base
      case('1'):
        libgraph->drawBitmap("img/tiles/default.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
        break;
    //Case de départ
      case('2'):
        libgraph->drawBitmap("img/tiles/start.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
        break;
    //Case de combat
      case('3'):
        libgraph->drawBitmap("img/tiles/mob.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
        break;
    //Case de magasin
      case('4'):
        libgraph->drawBitmap("img/tiles/shop.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
        break;
    //Case de drop
      case('5'):
        libgraph->drawBitmap("img/tiles/drop.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
        break;
    //Case de combat de boss et de fin
      case('6'):
        libgraph->drawBitmap("img/tiles/end.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
        break;
    }

    //Si la case est terminé alors la transformé en default case
    if (cs.isCaseFinished() == true)
        libgraph->drawBitmap("img/tiles/default.png", CPoint{ cs.getPosX() * g_szCase.m_fWidth, cs.getPosY() * g_szCase.m_fHeight }, g_szCase.m_fWidth*10.5 / 640.0f);
  }
  else
  {
    //Trace les bordures de la case
    CPoint p1, p2;

    if (!cs.getRightCase()) //si la case n'est pas connectée
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f); //trace une bordure noir
    else //trace une bordure grise
      libgraph->setPen(MakeARGB(20, 70, 70, 70), 0.5f);
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

    if (!cs.getTopCase()) //si la case n'est pas connectée
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f); //trace une bordure noir
    else //trace une bordure grise
      libgraph->setPen(MakeARGB(20, 70, 70, 70), 0.5f); //trace une bordure noir
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

    if (!cs.getLeftCase()) //si la case n'est pas connectée
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f); //trace une bordure noir
    else //trace une bordure grise
      libgraph->setPen(MakeARGB(20, 70, 70, 70), 0.5f);
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

    if (!cs.getBottomCase()) //si la case n'est pas connectée
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f); //trace une bordure noir
    else //trace une bordure grise
      libgraph->setPen(MakeARGB(20, 70, 70, 70), 0.5f);
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

  }
}
//Fin Solution

//Procédure se lançant lors de l'arrivée sur une case qui définit l'action à lancer en fonction du statut de la case
void CaseEvent(CCase& currCase, CHero& hero)
{  
    switch(currCase.getStatut())
    { 
    //Lance l'évenement de combat
    case('3'):
        FightEvent(hero, currCase);
        currCase.statut('1');
        break;
    //Lance l'évenement du shop

    case('4'):
        ShopEvent(hero);
        break;
    //Lance l'évenement du drop
    case('5'):
        DropEvent(hero);
        currCase.statut('1');
        break;
    //Lance l'évenement du combat de boss
    case('6'):
        BossFightEvent(hero, currCase);
        break;
    }
}