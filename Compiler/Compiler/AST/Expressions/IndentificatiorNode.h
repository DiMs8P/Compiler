#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"

class IndentificatiorNode : public ExpressionNode
{
public:
    IndentificatiorNode(const Token& token);
private:
    Token _token;
};
