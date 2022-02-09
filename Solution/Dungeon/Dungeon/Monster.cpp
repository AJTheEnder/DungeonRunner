#include "Monster.h"
#include <iostream>

CMonster::CMonster() //constructeur par défaut
{
	m_bIsMonsterAttacked = false;
	m_bIsMonsterAttacking = false;
	m_bIsMonsterDead = false;
	m_nMonsterAD = 0;
	m_nMonsterHealth = 0;
	m_nGoldValue = 0;
	
}

void CMonster::setType(int type) //Initialisation du type de monstre
{
	switch (type)
	{
	case(0): //Slime (6pv, 1dmg, 2gold)
		m_nType = type;
		m_nMonsterHealth = 6;
		m_nMonsterAD = 1;
		m_nGoldValue = 2;
		break;

	case(1): //Bat (3pv, 2dmg, 3gold)
		m_nType = type;
		m_nMonsterHealth = 3; 
		m_nMonsterAD = 2;
		m_nGoldValue = 3;
		break;

	case(2): //Skeleton (9pv, 5dmg, 5gold)
		m_nType = type;
		m_nMonsterHealth = 10; 
		m_nMonsterAD = 3;
		m_nGoldValue = 5;
		break;
	}
}

int CMonster::getType() const //Getter du type
{
	return m_nType;
}

int CMonster::getMonsterHealth() const //Getter de la vie
{
	return m_nMonsterHealth;
}

int CMonster::getMonsterAD() const //Gette de l'attaque
{
	return m_nMonsterAD;
}

int CMonster::getMonsterValue() const //Getter de la valeur en gold
{
	return m_nGoldValue;
}

bool CMonster::isMonsterDead() const //Getter du statut de mort
{
	return m_bIsMonsterDead;
}

bool CMonster::isMonsterAttacking() const //Getter si le monstre attaque
{
	return m_bIsMonsterAttacking;
}

bool CMonster::isMonsterAttacked() const //Getter si le monstre est attaqué
{
	return m_bIsMonsterAttacked;
}

void CMonster::MonsterDamaged(int damages) //Prise de dommages du monstre
{
	m_nMonsterHealth -= damages;
	if (m_nMonsterHealth <= 0) {
		Die();
	}
}

void CMonster::monsterAttacking() //Met le monstre en attaque
{
	m_bIsMonsterAttacked = false;
	m_bIsMonsterAttacking = true;
}

void CMonster::monsterAttacked() //Met le monstre attaqué
{
	m_bIsMonsterAttacking = false;
	m_bIsMonsterAttacked = true;
}

void CMonster::monsterStopAttacking() //Le monstre arrête d'attaquer
{
	m_bIsMonsterAttacking = false;
}

void CMonster::monsterStopAttacked() //Le monstre arrêtre d'être attaqué
{
	m_bIsMonsterAttacked = false;
}

void CMonster::Die() //Le monstre meurt
{
	m_bIsMonsterDead = true;
}