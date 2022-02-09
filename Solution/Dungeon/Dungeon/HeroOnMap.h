#pragma once

class CHeroOnMap {
	int m_nHeroX = -1;  //!<\brief	Abscisse du Hero
	int m_nHeroY = -1;  //!<\brief	Ordonnée du Hero
	
public:
	CHeroOnMap(int x, int y) { m_nHeroX = x; m_nHeroY = y; }  //!<\brief	constructeur du Hero on map
	
	void setPosX(int x) { m_nHeroX = x; }  //!<\brief	affecte une nouvelle abscisse au Hero
	int& getPosX() { return m_nHeroX; }  //!<\brief	retourne l'abscisse du Hero
	
	void setPosY(int y) { m_nHeroY = y; }  //!<\brief	affecte une nouvelle ordonnée au Hero
	int& getPosY() { return m_nHeroY; }  //!<\brief	retourne l'ordonnée du Hero

};