#include "Rank.h"

const int Rank::STATEMENTS_PER_LEVEL = 15;
const char* Rank::RANK_KEY = "rank_key";

bool Rank::hasMoreRanks() {
	return getIndex() + 1 < RANK_COUNT;
}

bool Rank::shouldUpgradeRank(int levelNumber, int rankMargin) {
	return levelNumber % rankMargin == 0;
}

void Rank::onNewLevel() {

	int levelNumber = Level::getCurrentLevel()->getNumber();
	int statementCount = StatementList::getInstance()->getStatementCount();
	int levelCount = statementCount / STATEMENTS_PER_LEVEL;
	int rankMargin = levelCount / RANK_COUNT;

	if (shouldUpgradeRank(levelNumber, rankMargin) && hasMoreRanks()) {
		int rankIndex = getIndex();
		auto db = CCUserDefault::sharedUserDefault();
		db->setIntegerForKey(RANK_KEY, rankIndex + 1);
		db->flush();
	}
}

const char* Rank::getText() {
	return RANKS[getIndex()];
}

int Rank::getIndex() {
	auto db = CCUserDefault::sharedUserDefault();
	return db->getIntegerForKey(RANK_KEY, 0);
}

Rank::~Rank() {
}
