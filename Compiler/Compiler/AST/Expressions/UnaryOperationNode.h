#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"

class UnaryOperationNode : ExpressionNode
{
public:
    UnaryOperationNode(const Token& token, const ExpressionNode& operand)
        : _token(token),
          _operand(operand)
    {
    }

private:
    Token _token;
    ExpressionNode _operand;
};
