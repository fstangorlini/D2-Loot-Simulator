#pragma once

#include "Random.h"

Random Random::s_Instance;

Random::Random()
{
    srand((unsigned int)time(NULL));
};

Random& Random::getInstance()
{
    return s_Instance;
}

int Random::getRandomNumber(int until)
{
    return rand() % until;
}
