#include "StatementNodes.h"

void StatementNodes::Add(ExpressionNode* node)
{
    _expressionNodes.push_back(node);
}
