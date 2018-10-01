#ifndef GCOMBOHANDLER_H
#define GCOMBOHANDLER_H
class GComboHandler
{
public:
	GComboHandler();
	~GComboHandler();

	static void AddKill();
	static void AddScore(int score);

	void UpdateCombos(float updateStep);

	static int playerScore;
	static int killCounter;
	static int killMultiplier; //goes up if a kill is made within kill timer > 0

	int prevCounter = 0;

	int killTimer = 60; //60 ticks between each kill minimum

	bool shakeCamera = false;
};
#endif
