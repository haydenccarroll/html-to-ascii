#pragma once

#include <string>
#include "tagList.hpp"

class Parser
{
public:
Parser(std::string fileName);
~Parser();

void addTags();

private:
bool addNextTag();


TagList m_tags;
std::string m_inputString;


};