#pragma once
#include <iostream>
/* Random implementation as singleton */

class Random
{
public:
	/* Copy constructor delete to avoid more instances
	Singleton approach */
	Random(const Random&) = delete;

	/* Returns singleton instance */
	static Random& getInstance();

	/* Returns a random number from 0 to "until" value */
	int getRandomNumber(int until);

private:

	/* Private constructor - singleton approach */
	Random();

	/* Private variable to store instance */
	static Random s_Instance;

};

