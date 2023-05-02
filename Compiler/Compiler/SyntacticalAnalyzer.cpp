#include "SyntacticalAnalyzer.h"

#include "AST/StatementNodes.h"
#include "AST/Expressions/BinaryOperationNode.h"
#include "AST/Expressions/ConstantNode.h"
#include "AST/Expressions/IndentificatiorNode.h"
#include "DataTable/newPersistentTable.h"
#include "ExceptionManager/ExceptionManager.h"

void SyntacticalAnalyzer::Init(const newVolatileTable<Constant>& constantTable,
                               const newVolatileTable<Token>& tokenTable, const IndentificatorTable& idTable, const vector<newPersistentTable<string>>& stringTables)
{
    this->_constantTable = constantTable;
    this->_tokenTable = tokenTable;
    this->_idTable = idTable;
    _stringTables = stringTables;

    std::ofstream errorStream;
    errorStream.open("syntaxErrors.txt");
    _errorManager = new ExceptionManager (errorStream);
}


string SyntacticalAnalyzer::GetKeyWordValue(int lineNumber)
{
    return _stringTables[0].GetElemByLine(lineNumber);
}

ExpressionNode SyntacticalAnalyzer::ParseVariableOrNumber()
{
    if (Match(NUMBER, {INITIALIZED, NOTINITIALIZED}) != -1)
    {
        return ConstantNode(_tokenTable.GetElemByLine(_tokenPos - 1));
    }

    if (Match(IDENTIFIER, {INITIALIZED, NOTINITIALIZED}) != -1)
    {
        return IndentificatiorNode(_tokenTable.GetElemByLine(_tokenPos - 1));
    }

    _errorManager->Exception("Expected identification or number");
}

ExpressionNode SyntacticalAnalyzer::ParseParentheses()
{
    if (Match(RAZDELITEL, {LPAREN}) != -1)
    {
        ExpressionNode expression = ParseFormula();
        require_lexem1(RAZDELITEL, RPAREN);
        return expression;
    }
    else
    {
        return ParseVariableOrNumber();
    }
}

ExpressionNode SyntacticalAnalyzer::ParseFormula()
{
    ExpressionNode leftNode = ParseParentheses();
    int sign = Match(ZNAK, {PLUS, MINUS});
    while(sign != -1)
    {
        ExpressionNode rightNode = ParseParentheses();
        leftNode = BinaryOperationNode(_tokenTable.GetElemByLine(sign), leftNode, rightNode);
        int sign = Match(ZNAK, {PLUS, MINUS});
    }

    return leftNode;
}

ExpressionNode& SyntacticalAnalyzer::ParseUnar()
{
    Token sign = _tokenTable.GetElemByLine(_tokenPos);
    if (Match(IDENTIFIER, {INITIALIZED, NOTINITIALIZED}) != -1)
    {
        ExpressionNode indentificator = IndentificatiorNode(_tokenTable.GetElemByLine(_tokenPos - 1));
        require_lexem1(RAZDELITEL, SEMICOLON);
        return indentificator;
    }

    _errorManager->Exception("Expected identification after unar operator");
}

void SyntacticalAnalyzer::ParseStatements(StatementNodes& nodes)
{
    if (Match(KEYWORD, {FOR}) != -1)
    {
        //nodes.Add(ParseFor());
    }

    if (Match(ZNAK, {INCREMENT, DECREMENT}) != -1)
    {
        _tokenPos -= 1;
        nodes.Add(ParseUnar());
    }
    
    if (Match(IDENTIFIER, {INITIALIZED, NOTINITIALIZED}) != -1)
    {
        if (Match(ZNAK, {ALL}) != -1)
        {
            _tokenPos -= 2;
            ExpressionNode variableNode = ParseVariableOrNumber();
            Token Sign = _tokenTable.GetElemByLine(_tokenPos++);
            ExpressionNode rightFormulaNode = ParseFormula();
            nodes.Add(BinaryOperationNode(Sign, variableNode, rightFormulaNode));
        }
    }
    _errorManager->Exception("Can't resolve expressions");
}

void SyntacticalAnalyzer::Analyze()
{
    if (require_lexem1(KEYWORD, INT) == -1)
    {
        _errorManager->Exception("Can't find main return type");
    }

    if (require_lexem1(KEYWORD, MAIN) == -1)
    {
        _errorManager->Exception("Can't find main function");
    }

    if (require_lexem1(RAZDELITEL, LPAREN) == -1)
    {
        _errorManager->Exception("Can't find main left open paran");
    }

    if (require_lexem1(RAZDELITEL, RPAREN) == -1)
    {
        _errorManager->Exception("Can't find main right open paran");
    }

    if (require_lexem1(RAZDELITEL, LBRACE) == -1)
    {
        _errorManager->Exception("Can't find main left open brace");
    }

    // Parce main here
    StatementNodes nodes;
    while(_tokenPos < _tokenTable.Size())
    {
        ParseStatements(nodes);
    }

    if (require_lexem1(RAZDELITEL, RBRACE) == -1)
    {
        _errorManager->Exception("Can't find main right open brace");
    }
}

int SyntacticalAnalyzer::Match(TokenType tokenType, const vector<TokenValue>& tokenValues)
{
    for (int i = 0; i < tokenValues.size(); i++)
    {
        if (Match_Internal(tokenType, tokenValues[i]))
        {
            _tokenPos++;
            return _tokenTable.GetElemByLine(_tokenPos - 1).LineNumber;
        }
    }

    return -1;
}

bool SyntacticalAnalyzer::Match_Internal(TokenType tokenType, TokenValue token_value)
{
    Token token = _tokenTable.GetElemByLine(_tokenPos);

    if (tokenType == KEYWORD)
    {
        string value = _stringTables[tokenType].GetElemByLine(token.LineNumber);
        switch (token_value)
        {
        case FOR: return value == "for";
        case MAIN: return value == "main";
        case INT: return value == "int";
            
        default: _errorManager->Exception("non existing token value");
        }
    }
    else if (tokenType == RAZDELITEL)
    {
        string value = _stringTables[tokenType].GetElemByLine(token.LineNumber);
        switch (token_value)
        {
        case LPAREN: return value == "(";
        case RPAREN: return value == ")";
        case LBRACE: return value == "{";
        case RBRACE: return value == "}";
        case SEMICOLON: return value == ";";
            
        default: _errorManager->Exception("non existing token value");
        }
        
    }
    else if (tokenType == ZNAK)
    {
        string value = _stringTables[tokenType].GetElemByLine(token.LineNumber);
        switch (token_value)
        {
        case PLUS: return value == "+";
        case MINUS: return value == "-";
        case EQUAL: return value == "=";
        case MULTIPLY: return value == "*";
        case AND: return value == "&&";
        case OR: return value == "||";
        case LESS: return value == "<";
        case MORE: return value == ">";
        case LESSEQUAL: return value == "<=";
        case MOREEQUAL: return value == ">=";
        case ALL: return _stringTables[tokenType].Find(value) != -1;
            
        default: _errorManager->Exception("non existing token value");
        }
    }
    else if (tokenType == NUMBER)
    {
        Constant value = _constantTable.GetElemByLine(token.LineNumber);
        switch (token_value)
        {
        case INITIALIZED: return value.value != INT_MAX;
        case NOTINITIALIZED: return value.value == INT_MAX;
        }
        return false;
    }
    else if (tokenType == IDENTIFIER)
    {
        Identificator value = _idTable.GetElemByLine(token.LineNumber);

        switch (token_value)
        {
        case INITIALIZED: return value.value != INT_MAX;
        case NOTINITIALIZED: return value.value == INT_MAX;
        }
        return false;
    }
    _errorManager->Exception("non existing token value");
    return false;
}

int SyntacticalAnalyzer::require_lexem1(TokenType tokenType, TokenValue expected1)
{
    return Match(tokenType, {expected1});
}

int SyntacticalAnalyzer::require_lexem2(TokenType tokenType, TokenValue expected1, TokenValue expected2)
{
    return Match(tokenType, {expected1, expected2});
}

int SyntacticalAnalyzer::require_lexem3(TokenType tokenType, TokenValue expected1, TokenValue expected2,
    TokenValue expected3)
{
    return Match(tokenType, {expected1, expected2, expected3});
}

