#include "parser.hpp"
#include "tagList.hpp"
#include "tag.hpp"

#include <regex>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>

Parser::Parser(std::string fileName)
{
    std::ifstream f(fileName); //taking file as inputstream
    if(f)
    {
        std::ostringstream ss;
        ss << f.rdbuf(); // reading data
        m_inputString = ss.str();
    }
    else 
    {
        std::cout << "Could not open " << fileName << '\n';
        exit(1);
    }
    addTags();
    m_tags.nestAllTags();
}

Parser::~Parser(){}

void Parser::addTags()
{
    while (addNextTag())
        continue;
}

bool Parser::addNextTag()
{

    std::smatch currentMatch;
    std::smatch firstMatch;

    std::regex startTag("<[a-zA-Z0-0]+>");
    std::regex endTag("</[a-zA-Z0-9]+>");
    std::regex singleTag("<[a-zA-Z0-0]+/>");

    std::vector<std::regex> regexVec;
    regexVec.push_back(startTag);
    regexVec.push_back(endTag);
    regexVec.push_back(singleTag);


    bool foundMatch = false;
    std::regex_search(m_inputString, firstMatch, regexVec[0]);
    for (auto& currentRegex: regexVec)
    {
        if (!std::regex_search(m_inputString, currentMatch, currentRegex))
            continue;
        if (currentMatch.position(0) < firstMatch.position(0))
            firstMatch = currentMatch;
        foundMatch = true;
    }

    if (foundMatch)
    {
        m_tags.pushBack(Tag(firstMatch.str()));
        m_inputString = firstMatch.suffix();
    }

    return foundMatch;

}