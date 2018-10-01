#ifndef ELOG_H
#define ELOG_H
class ELog
{
public:
	static void Print(const char* string);
	static void Print(int var);
	static void Print(float var);
	static void ShowFPS(int var);
	static void DebugOn();
	static void DebugOff();
};
#endif

