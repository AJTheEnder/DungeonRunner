#pragma once

#include <ctime>

class CHero {

	int m_nHealth;
	int m_nSwordLvl;
	int m_nArmorLvl;
	int m_nConsumable;
	int m_nGold;

	bool m_bIsAttacking;
	bool m_bIsAttacked;
	bool m_bIsDead;
	clock_t m_cBeginTime = std::clock();

public:
	CHero();


	void setHealth(int damagedOrHealed);
	void armorLvlUp();
	void swordLvlUp();
	void setConsumable(int potionType);
	void setGold(int EarnOrSpend);
	void attacking();
	void attacked();
	void stopAttacking();
	void stopAttacked();
	
	clock_t getBeginTime() const;
	void getStats() const;
	int getArmorLvl() const;
	int getSwordLvl() const;
	int getConsumable() const;
	int getGold() const;
	int getHealth() const;
	bool isDead() const;
	bool isAttacking() const;
	bool isAttacked() const;


	void useConsumable(int potionToUse);
	void gameOver();

};
