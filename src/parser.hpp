#pragma once

#include <string>
#include <fstream>
#include <regex>
#include <vector>

#include "tag.hpp"


class Parser
{
public:
Parser(std::string fileName);
~Parser();

void addTags();
void nestAllTags();

private:
bool addNextTag();
int getMatchingTagIndex(unsigned tagIndex);
void nestATag(unsigned tagIndex);

std::vector<Tag> m_tags;
std::string m_inputString;


};