#pragma once

class CMonster {
	int m_nType = -1;
	int m_nMonsterHealth;
	int m_nMonsterAD;
	int m_nGoldValue;

	bool m_bIsMonsterAttacking;
	bool m_bIsMonsterAttacked;
	bool m_bIsMonsterDead;

public:
	CMonster();

	int getType() const;
	int getMonsterHealth() const;
	int getMonsterAD() const;
	int getMonsterValue() const;

	bool isMonsterDead() const;
	bool isMonsterAttacking() const;
	bool isMonsterAttacked() const;

	void setType(int type);
	void MonsterDamaged(int damages);
	void monsterAttacking();
	void monsterAttacked();
	void monsterStopAttacking();
	void monsterStopAttacked();
	void Die();
};
