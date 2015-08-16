#include "StatementReader.h"

CCArray* StatementReader::read(const char* fileName) {
	auto statements = CCArray::create();
//	auto fileUtils = CCFileUtils::sharedFileUtils();
//	unsigned long filesize;
//	const char* data = reinterpret_cast<const char *>(fileUtils->getFileData(
//			fileName, "r", &filesize));
	Document document;

	CCString* dataStr = CCString::createWithContentsOfFile(fileName);
//	CCLog("%d %d", filesize, dataStr->length());
//	if (dataStr->length() > filesize) {
//		dataStr->m_sString.erase(filesize, dataStr->length());
//	}
//	CCLog("%d", dataStr->length());
	CCLog("%d", document.Parse<0>(dataStr->getCString()).HasParseError());
//
	const Value& statementsArray = document["statements"];
	for (SizeType i = 0; i < statementsArray.Size(); i++) {
		const Value& statementArray = statementsArray[i];
		SizeType first = 0;
		SizeType second = 1;

//		CCLog("%s, %d", statementArray[first].GetString(),
//				statementArray[second].GetBool());
		statements->addObject(
				Statement::create(statementArray[first].GetString(),
						statementArray[second].GetBool()));
	}
//
	return statements;
}

StatementReader::~StatementReader() {
}

