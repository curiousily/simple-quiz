#ifndef FORMATTER_H_
#define FORMATTER_H_

#include "cocos2d.h"

USING_NS_CC;

class Formatter {
public:

	static const char* toString(const char* format, int param);
	static const char* toString(const char* format, const char* param);
	static const char* toString(const char* format, int param1, int param2);

	virtual ~Formatter();
};

#endif /* FORMATTER_H_ */
