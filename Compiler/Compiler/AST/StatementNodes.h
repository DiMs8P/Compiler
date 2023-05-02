#pragma once
#include "ExpressionNode.h"

class StatementNodes : public ExpressionNode
{
public:
    void Add(const ExpressionNode& node);
private:
    vector<ExpressionNode> _expressionNodes;
};
