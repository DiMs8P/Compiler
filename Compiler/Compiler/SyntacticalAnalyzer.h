#pragma once
#include "Constant.h"
#include "IndentificatorTable.h"
#include "Token.h"
#include "map"
#include "AST/StatementNodes.h"
#include "DataTable/newPersistentTable.h"
#include "DataTable/PersistentTable.h"
#include "ExceptionManager/ExceptionManager.h"

using namespace std;

enum TokenType
{
	KEYWORD = 0,
	RAZDELITEL = 1,
	ZNAK = 2,
	NUMBER = 3,
	IDENTIFIER = 4,
};

// YOU CAN"T CHANGE IT!!!! TYPE ME IF NEEDED
enum TokenValue
{
	FOR = 0,
	MAIN = 1,
	INT = 2,

	LPAREN = 20,
	RPAREN = 21,
	LBRACE = 22,
	RBRACE = 23,
	SEMICOLON = 24,

	PLUS = 40,
	MINUS = 41,
	EQUAL = 42,
	MULTIPLY = 43,
	AND = 44,
	OR = 45,
	LESS = 46,
	MORE = 47,
	LESSEQUAL = 48,
	MOREEQUAL = 49,
	INCREMENT = 50,
	DECREMENT = 51,
	ALL = 52,
	DOUBLEEQUAL = 53,

	INITIALIZED = 60,
	NOTINITIALIZED = 61
};

class SyntacticalAnalyzer
{
public:
	friend class Compiler;

protected:
	void Init(const newVolatileTable<Constant>& constantTable, const newVolatileTable <Token>& tokenTable,const  IndentificatorTable& idTable, const vector<newPersistentTable<string>>& stringTables);
	string GetKeyWordValue(int lineNumber);
	ExpressionNode* ParseVariableOrNumber();
	ExpressionNode* ParseParentheses();
	ExpressionNode* ParseFormula();
	ExpressionNode* ParsePrefixUnar();
	ExpressionNode* ParsePostfixUnar();
	ExpressionNode* ParseFor();
	ExpressionNode* ParseStatements();
	bool TryParseForAction(ExpressionNode*& action);
	bool TryParseForCondition(ExpressionNode*& condition);
	bool TryParseForInitializing(ExpressionNode*& initialization);
	bool TryParseIndentificatorWithInitialization(ExpressionNode*& value1);
	bool TryParseFor(ExpressionNode*& expression);
	bool TryParseUnarPrefix(ExpressionNode*& expression);
	bool TryParseUnarPostfix(ExpressionNode*& expression);
	bool TryParseIndentificator(ExpressionNode*& expression);
	void Analyze();

private:
	bool Match_Internal(TokenType tokenType, TokenValue token_value);
	int Match(TokenType tokenType, const vector<TokenValue>& tokenValues);
	// int Require(const vector<int>& tokenTypes);

	int require_lexem1(TokenType tokenType, TokenValue expected1);
	int require_lexem2(TokenType stream, TokenValue expected1, TokenValue expected2);
	int require_lexem3(TokenType stream, TokenValue expected1, TokenValue expected2, TokenValue expected3);

	void InitializeToString();

	int _tokenPos = 0;
	
private:
	newVolatileTable <Constant> _constantTable;
	newVolatileTable <Token> _tokenTable;
	IndentificatorTable _idTable;
	ExceptionManager* _errorManager;
	vector<newPersistentTable<string>> _stringTables;

	map<TokenValue, string> ToString;
};

