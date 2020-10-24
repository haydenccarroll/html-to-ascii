#pragma once

#include <string>
#include <vector>

class TagList; // forward declaration of TagList (located in tagList.cpp)

enum class TagType
{
    SingleTag=0,
    OpenTag=2,
    CloseTag=3
};

class Tag
{
public:
    Tag(std::string tagStr);
    ~Tag(){};
    void printTag();
    void analyzeTag();
    bool hasChildren();


    std::string tagStr;
    std::string tagName;
    TagType tagType;
    TagList* childTags;

private:

    void setTagType();
    void setTagName();
};