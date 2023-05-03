#include "SyntacticalAnalyzer.h"

#include "AST/StatementNodes.h"
#include "AST/Expressions/BinaryOperationNode.h"
#include "AST/Expressions/ConditionNode.h"
#include "AST/Expressions/ConstantNode.h"
#include "AST/Expressions/ForNode.h"
#include "AST/Expressions/IndentificatiorNode.h"
#include "AST/Expressions/NothingNode.h"
#include "AST/Expressions/PostfixUnaryOperationNode.h"
#include "AST/Expressions/PrefixUnaryOperationNode.h"
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
    InitializeToString();
}


string SyntacticalAnalyzer::GetKeyWordValue(int lineNumber)
{
    return _stringTables[0].GetElemByLine(lineNumber);
}

ExpressionNode* SyntacticalAnalyzer::ParseVariableOrNumber()
{
    if (Match(NUMBER, {INITIALIZED}) != -1)
    {
        return new ConstantNode(_tokenTable.GetElemByLine(_tokenPos - 1));
    }
    else
    {
        if (Match(NUMBER, {NOTINITIALIZED}) != -1)
        {
            _errorManager->Exception("Using not initialized number");
        }
    }

    if (Match(IDENTIFIER, {INITIALIZED}) != -1)
    {
        return new IndentificatiorNode(_tokenTable.GetElemByLine(_tokenPos - 1));
    }
    else
    {
        if (Match(IDENTIFIER, {NOTINITIALIZED}) != -1)
        {
            string message;
            message += "Using not initialized indentificator: ";
            message += _idTable.GetElemByLine(_tokenTable.GetElemByLine(_tokenPos - 1).LineNumber).name;
            _errorManager->Exception(message);
        }
    }

    _errorManager->Exception("Expected identification or number");
}

ExpressionNode* SyntacticalAnalyzer::ParseParentheses()
{
    if (Match(RAZDELITEL, {LPAREN}) != -1)
    {
        ExpressionNode* expression = ParseFormula();
        require_lexem1(RAZDELITEL, RPAREN);
        return expression;
    }
    else
    {
        return ParseVariableOrNumber();
    }
}

ExpressionNode* SyntacticalAnalyzer::ParseFormula()
{
    ExpressionNode* leftNode = ParseParentheses();
    int sign = Match(ZNAK, {PLUS, MINUS, MULTIPLY});
    while(sign != -1)
    {
        ExpressionNode* rightNode = ParseParentheses();
        leftNode = new BinaryOperationNode(_tokenTable.GetElemByLine(sign), leftNode, rightNode);
        sign = Match(ZNAK, {PLUS, MINUS, MULTIPLY});
    }

    return leftNode;
}

ExpressionNode* SyntacticalAnalyzer::ParsePrefixUnar()
{
    if (_tokenPos - 2 >= 0)
    {
        if (Match(ZNAK, {INCREMENT, DECREMENT}) != -1)
        {
            if (Match(IDENTIFIER, {INITIALIZED, NOTINITIALIZED}) != -1)
            {                
                return new PostfixUnaryOperationNode(_tokenTable.GetElemByLine(_tokenPos - 2), new IndentificatiorNode(_tokenTable.GetElemByLine(_tokenPos - 1)));
            }
        }
    }
    
    _errorManager->Exception("Can't parse prefix unar operation");
}

ExpressionNode* SyntacticalAnalyzer::ParsePostfixUnar()
{
    if (_tokenPos - 2 >= 0)
    {
        if (Match(IDENTIFIER, {INITIALIZED, NOTINITIALIZED}) != -1)
        {
            if (Match(ZNAK, {INCREMENT, DECREMENT}) != -1)
            {
                return new PostfixUnaryOperationNode(_tokenTable.GetElemByLine(_tokenPos - 1), new IndentificatiorNode(_tokenTable.GetElemByLine(_tokenPos - 2)));
            }
        }
    }
    _errorManager->Exception("Can't parse postfix unar operation");
}

ExpressionNode* SyntacticalAnalyzer::ParseFor()
{
    require_lexem1(RAZDELITEL, LPAREN);

    ExpressionNode* initialization = nullptr;
    if (!TryParseForInitializing(initialization))
    {
        _errorManager->Exception("for initialization error");
    }

    ExpressionNode* condition = nullptr;
    if (!TryParseForCondition(condition))
    {
        _errorManager->Exception("for condition error");
    }

    ExpressionNode* action  = nullptr;
    if (!TryParseForAction(action))
    {
        _errorManager->Exception("for action error");
    }

    require_lexem1(RAZDELITEL, LBRACE);
    StatementNodes nodes;

    if (Match(RAZDELITEL, {RBRACE}) == -1)
    {
        while(Match(RAZDELITEL, {RBRACE}) == -1)
        {
            nodes.Add(ParseStatements());
        }
    }
    else
    {
        nodes.Add(new NothingNode());
    }
    
    return new ForNode(initialization, condition, nodes, action);
}

bool SyntacticalAnalyzer::TryParseForCondition(ExpressionNode*& action)
{
    if (Match(IDENTIFIER, {INITIALIZED, NOTINITIALIZED}) != -1)
    {
        if (Match(ZNAK, {MORE, LESS, LESSEQUAL, MOREEQUAL, DOUBLEEQUAL, AND, OR}) != -1)
        {
            _tokenPos -= 2;
            ExpressionNode* variableNode = ParseVariableOrNumber();
            Token Sign = _tokenTable.GetElemByLine(_tokenPos++);
            ExpressionNode* rightFormulaNode = ParseFormula();
            require_lexem1(RAZDELITEL, SEMICOLON);
            action = new ConditionNode(variableNode, Sign, rightFormulaNode);
            return true;
        }
    }

    return false;
}

bool SyntacticalAnalyzer::TryParseForAction(ExpressionNode*& condition)
{
    if (Match(RAZDELITEL, {RPAREN}) != -1)
    {
        condition = new NothingNode();
        return true;
    }
    
    if(TryParseIndentificatorWithInitialization(condition))
    {
        require_lexem1(RAZDELITEL, RPAREN);
        return true;
    }

    if (TryParseUnarPrefix(condition))
    {
        require_lexem1(RAZDELITEL, RPAREN);
        return true;
    }

    if (TryParseUnarPostfix(condition))
    {
        require_lexem1(RAZDELITEL, RPAREN);
        return true;
    }

    if (TryParseIndentificator(condition))
    {
        require_lexem1(RAZDELITEL, RPAREN);
        return true;
    }

    return false;
}

bool SyntacticalAnalyzer::TryParseForInitializing(ExpressionNode*& initialization)
{
    if (Match(RAZDELITEL, {SEMICOLON}) != -1)
    {
        initialization = new NothingNode();
        return true;
    }
    
    if(TryParseIndentificatorWithInitialization(initialization))
    {
        require_lexem1(RAZDELITEL, SEMICOLON);
        return true;
    }

    if (TryParseUnarPrefix(initialization))
    {
        require_lexem1(RAZDELITEL, SEMICOLON);
        return true;
    }

    if (TryParseUnarPostfix(initialization))
    {
        require_lexem1(RAZDELITEL, SEMICOLON);
        return true;
    }

    if (TryParseIndentificator(initialization))
    {
        require_lexem1(RAZDELITEL, SEMICOLON);
        return true;
    }
    
    return false;
}

bool SyntacticalAnalyzer::TryParseIndentificatorWithInitialization(ExpressionNode*& value1)
{
    const int tokenPos = _tokenPos;
    if (Match(KEYWORD, {INT}) != -1)
    {
        if (Match(IDENTIFIER, {NOTINITIALIZED}) != -1)
        {
            if (Match(ZNAK, {EQUAL}) != -1)
            {
                _tokenPos -= 2;
                _idTable.ChangeValue(_tokenTable.GetElemByLine(_tokenPos).LineNumber, 0);
                ExpressionNode* variableNode = ParseVariableOrNumber();
                Token Sign = _tokenTable.GetElemByLine(_tokenPos++);
                ExpressionNode* rightFormulaNode = ParseFormula();
                value1 = new BinaryOperationNode(Sign, variableNode, rightFormulaNode);
                return true;
            }
        }
        else
        {
            if (Match(IDENTIFIER, {INITIALIZED}) != -1)
            {
                string message;
                message += "Trying to reinitialize indentificator: ";
                message += _idTable.GetElemByLine(_tokenTable.GetElemByLine(_tokenPos - 1).LineNumber).name;
                _errorManager->Exception(message);
            }
        }
    }
    _tokenPos = tokenPos;
    return false;
}

bool SyntacticalAnalyzer::TryParseFor(ExpressionNode*& expression)
{
    if (Match(KEYWORD, {FOR}) != -1)
    {
        expression = ParseFor();
        return true;
    }
    return false;
}

bool SyntacticalAnalyzer::TryParseUnarPrefix(ExpressionNode*& expression)
{
    const int tokenPos = _tokenPos;
    if (Match(ZNAK, {INCREMENT, DECREMENT}) != -1)
    {
        _tokenPos -= 1;
        expression = ParsePrefixUnar();
        return true;
    }
    
    _tokenPos = tokenPos;
    return false;
}

bool SyntacticalAnalyzer::TryParseUnarPostfix(ExpressionNode*& expression)
{
    const int tokenPos = _tokenPos;
    if (Match(IDENTIFIER, {INITIALIZED, NOTINITIALIZED}) != -1)
    {
        if (Match(ZNAK, {INCREMENT, DECREMENT}) != -1)
        {
            _tokenPos -= 2;
            expression = ParsePostfixUnar();
            return true;
        }
    }
    
    _tokenPos = tokenPos;
    return false;
}

bool SyntacticalAnalyzer::TryParseIndentificator(ExpressionNode*& expression)
{
    const int tokenPos = _tokenPos;
    if (Match(IDENTIFIER, {INITIALIZED}) != -1)
    {
        if (Match(ZNAK, {ALL}) != -1)
        {
            _tokenPos -= 2;
            ExpressionNode* variableNode = ParseVariableOrNumber();
            Token Sign = _tokenTable.GetElemByLine(_tokenPos++);
            ExpressionNode* rightFormulaNode = ParseFormula();
            expression = new BinaryOperationNode(Sign, variableNode, rightFormulaNode);
            return true;
        }
    }
    else
    {
        if(Match(IDENTIFIER, {NOTINITIALIZED}) != -1)
        {
            string message;
            message += "Trying to use not initialized indentificator: ";
            message += _idTable.GetElemByLine(_tokenTable.GetElemByLine(_tokenPos - 1).LineNumber).name;
            _errorManager->Exception(message);
        }
    }
    _tokenPos = tokenPos;
    return false;
}

ExpressionNode* SyntacticalAnalyzer::ParseStatements()
{
    try
    {
        ExpressionNode* expression = nullptr;

        if (TryParseFor(expression))
        {
            return expression;
        }

        if(TryParseIndentificatorWithInitialization(expression))
        {
            require_lexem1(RAZDELITEL, SEMICOLON);
            return expression;
        }

        if (TryParseUnarPrefix(expression))
        {
            require_lexem1(RAZDELITEL, SEMICOLON);
            return expression;
        }

        if (TryParseUnarPostfix(expression))
        {
            require_lexem1(RAZDELITEL, SEMICOLON);
            return expression;
        }

        if (TryParseIndentificator(expression))
        {
            require_lexem1(RAZDELITEL, SEMICOLON);
            return expression;
        }
        
        _errorManager->Exception("Can't resolve expressions");

    } catch (const std::exception& e)
    {
        exit(-1);
    }
    
}

void SyntacticalAnalyzer::Analyze()
{
    require_lexem1(KEYWORD, INT);
    require_lexem1(KEYWORD, MAIN);
    require_lexem1(RAZDELITEL, LPAREN);
    require_lexem1(RAZDELITEL, RPAREN);
    require_lexem1(RAZDELITEL, LBRACE);
    
    // Parce main here
    StatementNodes nodes;
    while(_tokenPos < _tokenTable.Size() - 1)
    {
        nodes.Add(ParseStatements());
    }

    require_lexem1(RAZDELITEL, RBRACE);

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

    if (tokenType == KEYWORD && token.TableNumber == tokenType + 1)
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
    else if (tokenType == RAZDELITEL && token.TableNumber == tokenType + 1)
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
    else if (tokenType == ZNAK && token.TableNumber == tokenType + 1)
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
        case INCREMENT: return value == "++";
        case DECREMENT: return value == "--";
        case DOUBLEEQUAL: return value == "==";
        case ALL: return _stringTables[tokenType].Find(value) != -1;
            
        default: _errorManager->Exception("non existing token value");
        }
    }
    else if (tokenType == NUMBER && token.TableNumber == tokenType + 1)
    {
        Constant value = _constantTable.GetElemByLine(token.LineNumber);
        switch (token_value)
        {
        case INITIALIZED: return value.value != INT_MAX;
        case NOTINITIALIZED: return value.value == INT_MAX;
        }
        return false;
    }
    else if (tokenType == IDENTIFIER && token.TableNumber == tokenType + 1)
    {
        Identificator value = _idTable.GetElemByLine(token.LineNumber);

        switch (token_value)
        {
        case INITIALIZED: return value.value != INT_MAX;
        case NOTINITIALIZED: return value.value == INT_MAX;
        }
        return false;
    }

    return false;
}

int SyntacticalAnalyzer::require_lexem1(TokenType tokenType, TokenValue expected1)
{
    int MatchValue = Match(tokenType, {expected1});
    if (MatchValue == -1)
    {
        string message;
        message += "non existing token ";
        message += ToString[expected1];
        _errorManager->Exception(message);
    }
        
    return MatchValue;
}
int SyntacticalAnalyzer::require_lexem2(TokenType tokenType, TokenValue expected1, TokenValue expected2)
{
    int MatchValue = Match(tokenType, {expected1, expected2});
    if (MatchValue == -1)
    {
        string message;
        message += "non existing token ";
        message += ToString[expected1];
        message += " Or ";
        message += ToString[expected2];
        _errorManager->Exception(message);
    }
        
    return MatchValue;
}
int SyntacticalAnalyzer::require_lexem3(TokenType tokenType, TokenValue expected1, TokenValue expected2,
    TokenValue expected3)
{
    int MatchValue = Match(tokenType, {expected1, expected2, expected3});
    if (MatchValue == -1)
    {
        string message;
        message += "non existing token ";
        message += ToString[expected1];
        message += " Or ";
        message += ToString[expected2];
        message += " Or ";
        message += ToString[expected3];
        _errorManager->Exception(message);
    }

    return MatchValue;
}

void SyntacticalAnalyzer::InitializeToString()
{
    ToString.insert(std::pair<TokenValue,string>(FOR, "FOR"));
    ToString.insert(std::pair<TokenValue,string>(MAIN, "MAIN"));
    ToString.insert(std::pair<TokenValue,string>(INT, "INT"));
    ToString.insert(std::pair<TokenValue,string>(LPAREN, "LPAREN"));
    ToString.insert(std::pair<TokenValue,string>(RPAREN, "RPAREN"));
    ToString.insert(std::pair<TokenValue,string>(LBRACE, "LBRACE"));
    ToString.insert(std::pair<TokenValue,string>(RBRACE, "RBRACE"));
    ToString.insert(std::pair<TokenValue,string>(SEMICOLON, "SEMICOLON"));
    ToString.insert(std::pair<TokenValue,string>(PLUS, "PLUS"));
    ToString.insert(std::pair<TokenValue,string>(MINUS, "MINUS"));
    ToString.insert(std::pair<TokenValue,string>(EQUAL, "EQUAL"));
    ToString.insert(std::pair<TokenValue,string>(MULTIPLY, "MULTIPLY"));
    ToString.insert(std::pair<TokenValue,string>(AND, "AND"));
    ToString.insert(std::pair<TokenValue,string>(OR, "OR"));
    ToString.insert(std::pair<TokenValue,string>(LESS, "LESS"));
    ToString.insert(std::pair<TokenValue,string>(MORE, "MORE"));
    ToString.insert(std::pair<TokenValue,string>(LESSEQUAL, "LESSEQUAL"));
    ToString.insert(std::pair<TokenValue,string>(LESSEQUAL, "LESSEQUAL"));
    ToString.insert(std::pair<TokenValue,string>(MOREEQUAL, "MOREEQUAL"));
    ToString.insert(std::pair<TokenValue,string>(DOUBLEEQUAL, "DOUBLEEQUAL"));
    ToString.insert(std::pair<TokenValue,string>(INCREMENT, "INCREMENT"));
    ToString.insert(std::pair<TokenValue,string>(DECREMENT, "DECREMENT"));
    ToString.insert(std::pair<TokenValue,string>(INITIALIZED, "INITIALIZED"));
    ToString.insert(std::pair<TokenValue,string>(NOTINITIALIZED, "NOTINITIALIZED"));
}

