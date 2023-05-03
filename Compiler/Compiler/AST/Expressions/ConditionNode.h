#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"

class ConditionNode : public ExpressionNode
{
public:
    ConditionNode(ExpressionNode* leftExpression, Token sign, ExpressionNode* rightExpression): left_expression_(leftExpression), sign_(sign), right_expression_(rightExpression)
    {
        
    }

    ExpressionNode* left_expression_;
    Token sign_;
    ExpressionNode* right_expression_;
};
