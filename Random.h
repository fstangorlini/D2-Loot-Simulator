#pragma once
#include <iostream>

class Random
{
public:
	Random(const Random&) = delete;

	static Random& getInstance();

	int getRandomNumber(int until);

private:
	Random();
	
	static Random s_Instance;

};

