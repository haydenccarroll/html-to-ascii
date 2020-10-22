#include "parser.hpp"
#include <regex>
#include <iostream>
#include <string>
#include <stdlib.h>
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
}

Parser::~Parser(){}

void Parser::addTags()
{
    while (addNextTag())
        continue;
}

void Parser::nestAllTags()
{
    for (int i=0; i < m_tags.size(); i++)
    {
        nestATag(i);
        m_tags[i].childTags[0].printTag();
    }
}

int Parser::getMatchingTagIndex(unsigned tagIndex)
{
    if (m_tags.size() <= tagIndex) return -1;

    // Useful for parsing the following: <div> <div></div> </div>
    int openTagCount = 0; // num of unresolved tags.


    std::string currentTagName = m_tags[tagIndex].tagName;
    int endIndex = -1; // index of matching tag
    for (unsigned i = 1; i < m_tags.size(); i++)
    {
        if (m_tags[i].tagName == currentTagName && 
            m_tags[i].tagType == TagType::OpenTag)
        {
            openTagCount++;
        }

        if (m_tags[i].tagName == currentTagName && 
            m_tags[i].tagType == TagType::CloseTag)
        {
            if (openTagCount == 0)
                return i; // end index
            openTagCount--;
        }
    }
    return -1;
}

void Parser::nestATag(unsigned tagIndex)
{
    int matchingTagIndex = getMatchingTagIndex(tagIndex);
    if (matchingTagIndex == -1)
        return;
    
    std::string totalTagStr = "";
    for (int i = tagIndex; i <= matchingTagIndex; i++)
        totalTagStr += m_tags[i].tagStr;
    // copies inner tags between the start/end tags to the child tag vector
    m_tags[tagIndex].childTags = std::vector<Tag>(m_tags.begin() + tagIndex + 1,
                                                  m_tags.begin() + matchingTagIndex);
    // erases child tags
    m_tags.erase(m_tags.begin() + tagIndex+1, m_tags.begin() + matchingTagIndex+1);

    m_tags[tagIndex] = Tag(totalTagStr);
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
        m_tags.push_back(Tag(firstMatch.str()));
        m_inputString = firstMatch.suffix();
    }

    return foundMatch;

}