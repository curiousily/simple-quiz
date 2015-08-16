#ifndef RANK_H_
#define RANK_H_

#include "cocos2d.h"
#include "../Constants.h"
#include "../Model/Level.h"
#include "StatementList.h"

USING_NS_CC;

class Rank {
public:
	static void onNewLevel();
	static const char* getText();
	virtual ~Rank();

private:

	static const int STATEMENTS_PER_LEVEL;
	static const char* RANK_KEY;

	static int getIndex();
	static bool hasMoreRanks();
	static bool shouldUpgradeRank(int levelNumber, int rankMargin);
};

#endif /* RANK_H_ */
