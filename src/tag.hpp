#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

enum class TagType
{
    SingleTag=0,
    FullTag=1,
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


    std::string tagStr;
    std::string tagName;
    TagType tagType;
    std::vector<Tag> childTags;

private:

    void setTagType();
    void setTagName();
    void nestAllTags();
    int nestATag();
};