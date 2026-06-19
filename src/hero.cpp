#include "hero.h"
#include <iostream>
using namespace std;

string hero::getName()
{
    return name;
}

int hero::getHp()
{
    return hp;
}

void hero::setHp(int hp)
{
    this->hp = hp;
}

void hero::takeDamage(int damage)
{
    if (isInvisible)
    {
        cout << "\n** " << name << " IS INVISIBLE! SINGLE-TARGET ATTACK MISSES!\n";
        return;
    }

    if (shieldAmount > 0)
    {
        reduceShield(damage);
    }
    else
    {
        hp -= damage;
        if (hp < 0)
            hp = 0;
    }
}

void hero::takeAreaDamage(int damage)
{
    if (shieldAmount > 0)
    {
        reduceShield(damage);
    }
    else
    {
        hp -= damage;
        if (hp < 0)
            hp = 0;
    }
}

int hero::getAbility1Cost()
{
    return ability1Cost;
}

int hero::getAbility2Cost()
{
    return ability2Cost;
}

int hero::getSpecialCost()
{
    return specialCost;
}

void hero::heal(int amount)
{
    if (hp > 0)
        hp += amount;
}

void hero::addDamageBuff(int percent, int duration)
{
    damagePercent = percent;
    damageDuration = duration;
}

int hero::getDamagePercent()
{
    return damagePercent;
}

void hero::decreaseDuration()
{
    if (damageDuration > 0)
    {
        damageDuration--;
        if (damageDuration == 0)
        {
            damagePercent = 0;
        }
    }
}

bool hero::hasDamageBuff()
{
    return damagePercent > 0 && damageDuration > 0;
}

void hero::revive(int newHp)
{
    dead = false;
    hp = newHp;
    clearNegativeEffects();
}

bool hero::isDead()
{
    return hp <= 0;
}

void hero::clearNegativeEffects()
{
    damagePercent = 0;
    damageDuration = 0;
}

void hero::setDead(bool dead)
{
    this->dead = dead;
    if (dead)
    {
        hp = 0;
        isInvisible = false;
        shieldAmount = 0;
    }
}

void hero::addHealOverTime(int amount, int duration)
{
    healAmount = amount;
    healDuration = duration;
}

void hero::applyHealOverTime()
{
    if (healDuration > 0 && hp > 0)
    {
        heal(healAmount);
        cout << "\n-> " << name << " IS HEALED " << healAmount << " HP \n   New HP : " << hp;
        healDuration--;
        if (healDuration == 0)
        {
            healAmount = 0;
        }
    }
}

void hero::setShield(int amount, int duration)
{
    shieldAmount = amount;
    shieldDuration = duration;
}

void hero::reduceShield(int damage)
{
    if (shieldAmount > 0)
    {
        if (damage >= shieldAmount)
        {
            int remainingDamage = damage - shieldAmount;
            shieldAmount = 0;
            if (remainingDamage > 0)
            {
                takeDamage(remainingDamage);
            }
        }
        else
        {
            shieldAmount -= damage;
            cout << "\n-> SHIELD ABSORBED " << damage << " DAMAGE!\n   REMAINING POWER OF SHIELD : " << shieldAmount << '\n';
        }
    }
    else
    {
        takeDamage(damage);
    }
}

void hero::reduceShieldDuration()
{
    if (shieldDuration > 0)
    {
        shieldDuration--;
        if (shieldDuration == 0)
        {
            shieldAmount = 0;
        }
    }
}

void hero::setInvisible(int duration)
{
    isInvisible = true;
    invisibleDuration = duration;
    cout << "\n-> " << name << " BECOMES INVISIBLE FOR " << duration << " ROUND!\n";
}

bool hero::getInvisible()
{
    return isInvisible;
}

void hero::reduceInvisibleDuration()
{
    if (invisibleDuration > 0)
    {
        invisibleDuration--;
        if (invisibleDuration == 0)
        {
            isInvisible = false;
            cout << "\n** " << name << " IS NO LONGER INVISIBLE!\n";
        }
    }
}

void hero::applyInvisibility()
{
    if (isInvisible)
    {
        reduceInvisibleDuration();
    }
}