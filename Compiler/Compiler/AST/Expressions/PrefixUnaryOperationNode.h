#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"

class PrefixUnaryOperationNode : public ExpressionNode
{
public:
    PrefixUnaryOperationNode(const Token& token, ExpressionNode* operand)
        : _sign(token),
          _operand(operand)
    {
    }

private:
    Token _sign;
    ExpressionNode* _operand;
};
