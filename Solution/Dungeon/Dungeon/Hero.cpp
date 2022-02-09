#include "Hero.h"
#include <iostream>
#include<windows.h>
#include <LibGraph2.h>


using namespace LibGraph2;

CHero::CHero() //constructeur
{
	m_nHealth = 10;
	m_nSwordLvl = 1; 
	m_nArmorLvl = 1;
	m_nConsumable = -1;
	m_nGold = 0;

	m_bIsAttacked = false;
	m_bIsAttacking = false;
	m_bIsDead = false;
}

int CHero::getHealth() const
{
	return m_nHealth;
}

void CHero::setHealth(int damagedOrHealed)
{
	m_nHealth += damagedOrHealed;
	if (m_nHealth <= 0) {
		m_nHealth = 0;
	}
	else if (m_nHealth >= 10) {
		m_nHealth = 10;
	}
}

void CHero::useConsumable(int potionToUse)
{
	switch (potionToUse)
	{
	case 0:
		setHealth(4);
		m_nConsumable = -1;
		break;
	case 1:
		std::cout << "Cas pas encore effectué \n";
		m_nConsumable = -1;
		break;
	case 2:
		std::cout << "Cas pas encore effectué \n";
		m_nConsumable = -1;
		break;
	default:
		std::cout << "Vous n'avez pas de potion \n";
		break;
	}
}

void CHero::gameOver()
{
	ILibGraph2* libgraph = GetLibGraph2();
	libgraph->guiMessageBox("Game Over", "Vous etes mort...", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnInformation);
	Sleep(3000);
	exit(1);
}

bool CHero::isDead() const
{
	return m_bIsDead;
}

bool CHero::isAttacking() const
{
	return m_bIsAttacking;
}

bool CHero::isAttacked() const
{
	return m_bIsAttacked;
}


clock_t CHero::getBeginTime() const
{
	return m_cBeginTime;
}

void CHero::getStats() const
{
	std::cout << "Life : " << m_nHealth << "\n";
	std::cout << "Gold : " << m_nGold << "\n";
	std::cout << "Armor level : " << m_nArmorLvl << "\n";
	std::cout << "Sword level : " << m_nSwordLvl << "\n";
}

int CHero::getArmorLvl() const
{
	return m_nArmorLvl;
}

void CHero::armorLvlUp()
{
	if (m_nArmorLvl >= 5) {
		m_nArmorLvl = 5;
	}
	else {
		m_nArmorLvl += 1;
	}

}

int CHero::getSwordLvl() const
{
	return m_nSwordLvl;
}

int CHero::getConsumable() const
{
	return m_nConsumable;
}

int CHero::getGold() const
{
	return m_nGold;
}

void CHero::swordLvlUp()
{
	if (m_nSwordLvl >= 5)
	{
		m_nSwordLvl = 5;
	}
	else {
		m_nSwordLvl += 1;
	}

}

void CHero::setConsumable(int potionType)
{
	m_nConsumable = potionType;
}

void CHero::setGold(int EarnOrSpend)
{
	m_nGold += EarnOrSpend;
	if (m_nGold <= 0) {
		std::cout << "Vous n'avez plus d'or ! \n";
	}
}

void CHero::attacking()
{
	m_bIsAttacking = true;
}

void CHero::attacked()
{
	m_bIsAttacked = true;
}

void CHero::stopAttacking()
{
	m_bIsAttacking = false;
}

void CHero::stopAttacked()
{
	m_bIsAttacked = false;
}