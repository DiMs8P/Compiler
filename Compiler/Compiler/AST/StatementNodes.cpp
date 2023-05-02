#include "StatementNodes.h"

void StatementNodes::Add(const ExpressionNode& node)
{
    _expressionNodes.push_back(node);
}
