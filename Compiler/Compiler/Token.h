#pragma once

struct Token
{
	int TableNumber;
	int LineNumber;

	bool operator==(Token const& otherToken) const { return (LineNumber == otherToken.LineNumber) && (TableNumber == otherToken.TableNumber); }
};
