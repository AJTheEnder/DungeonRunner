#pragma once

#include "Hero.h"

class CBoss {
	int m_nBossType = -1;
	int m_nBossHealth;
	int m_nBossAD;
	bool m_bIsBossAttacking;
	bool m_bIsBossAttacked;
	bool m_bIsBossDead;
public:
	CBoss();
	void setBossType(int type);
	void bossDamaged(int damages,CHero& hero);
	void WinTheGame(CHero& hero);
	void bossAttacking();
	void bossAttacked();
	void bossStopAttacking();
	void bossStopAttacked();

	int getBossType() const;
	int getBossAD() const;
	int getBossHealth() const;
	bool isBossDead() const;
	bool isBossAttacking() const;
	bool isBossAttacked() const;

};
