#include "ELog.h"
#include <iostream>

void ELog::Print(const char * string)
{
	std::cout << string << std::endl;
}

void ELog::Print(int var)
{
	std::cout << var << std::endl;
}

void ELog::Print(float var)
{
	std::cout << var << std::endl;
}

/*void ELog::PrintLong(const char * string)
{
	std::cout << string;
}*/


void ELog::ShowFPS(int var)
{
	std::cout << std::flush << "\r" << var << std::flush;
}

void ELog::DebugOn()
{
}

void ELog::DebugOff()
{
}
