#pragma once
#include "../ExpressionNode.h"
#include "../StatementNodes.h"

class ForNode : public ExpressionNode
{
public:
    ForNode(ExpressionNode* initialization, ExpressionNode* condition, StatementNodes statements, ExpressionNode* action): initialization_(initialization), condition_(condition), statements_(
        std::move(statements)), action_(action)
    {
        
    }

    ExpressionNode* initialization_;
    ExpressionNode* condition_;
    StatementNodes statements_;
    ExpressionNode* action_;
};
