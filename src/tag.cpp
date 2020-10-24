#include "tag.hpp"
#include "tagList.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

Tag::Tag(std::string tagStr)
{
    childTags = new TagList();
    this->tagStr = tagStr;
    analyzeTag();
}

void Tag::analyzeTag()
{
    setTagType();
    setTagName();
    childTags->nestAllTags();
}

bool Tag::hasChildren()
{
    return !(childTags->isEmpty());
}

void Tag::setTagName()
{

    
    if (tagType == TagType::CloseTag)
        tagName = std::string(tagStr.begin() + 2, tagStr.end()-1); // removes </ and >

    else if (tagType == TagType::OpenTag)
        tagName = std::string(tagStr.begin()+1, tagStr.end()-1); // removes < and >

    else if (tagType == TagType::SingleTag)
        tagName = std::string(tagStr.begin()+1, tagStr.end()-2); // removes < and />
}

void Tag::setTagType()
{
    if (std::count(tagStr.begin(), tagStr.end(), '/') == 0)
        tagType = TagType::OpenTag;

    else if (tagStr.find("</") == 0)
        tagType = TagType::CloseTag;

    else
        tagType = TagType::SingleTag;
}

void Tag::printTag()
{
    std::cout << "Tag name: " << tagName << '\n';
    std::cout << "Tag str: " << tagStr << '\n';
    std::cout << "Tag type: " << static_cast<int>(tagType) << '\n';
    
    for (auto& element: *childTags)
    {
        std::cout << "Child name: " << element.tagName << '\n';
    }
}