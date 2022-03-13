#include "Boss.h"

#include <iostream>
#include <windows.h>
#include <LibGraph2.h>
#include <ctime>
#include <string>

using namespace LibGraph2;

CBoss::CBoss()
{
	m_nBossHealth = 0;
	m_nBossAD = 0;
	m_bIsBossAttacked = false;
	m_bIsBossAttacking = false;
	m_bIsBossDead = false;
}

void CBoss::setBossType(int type)
{
	switch (type)
	{

	case(0):
		m_nBossType = type;
		m_nBossHealth = 60;
		m_nBossAD = 4;
		break;
	case(1):
		m_nBossType = type;
		m_nBossHealth = 35;
		m_nBossAD = 6;
		break;
	case(2):
		m_nBossType = type;
		m_nBossHealth = 25;
		m_nBossAD = 7;
		break;
	case(3):
		m_nBossType = type;
		m_nBossHealth = 50;
		m_nBossAD = 5;
		break;
	}
}

void CBoss::bossDamaged(int damages, CHero& hero)
{
	m_nBossHealth -= damages;
	if (m_nBossHealth <= 0) {
		WinTheGame(hero);
	}
}

void CBoss::WinTheGame(CHero& hero)
{
	ILibGraph2* libgraph = GetLibGraph2();
	float endtime = (std::clock() - hero.getBeginTime())/1000;
	std::string endStr = "Vous avez gagne en " + std::to_string(endtime) + " Secondes";
	libgraph->guiMessageBox("Congratulations !", endStr, msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnInformation);
	Sleep(3000);
	exit(1);
}

void CBoss::bossAttacking()
{
	m_bIsBossAttacking = true;
}

void CBoss::bossAttacked()
{
	m_bIsBossAttacked = true;
}

void CBoss::bossStopAttacking()
{
	m_bIsBossAttacking = false;
}

void CBoss::bossStopAttacked()
{
	m_bIsBossAttacked = false;
}

int CBoss::getBossType() const
{
	return m_nBossType;
}

int CBoss::getBossAD() const
{
	return m_nBossAD;
}

int CBoss::getBossHealth() const
{
	return m_nBossHealth;
}

bool CBoss::isBossDead() const
{
	return m_bIsBossDead;
}

bool CBoss::isBossAttacking() const
{
	return m_bIsBossAttacking;
}

bool CBoss::isBossAttacked() const
{
	return m_bIsBossAttacked;
}