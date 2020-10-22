#include "tag.hpp"

Tag::Tag(std::string tagStr)
{
    this->tagStr = tagStr;
    analyzeTag();
}

void Tag::analyzeTag()
{
    setTagType();
    setTagName();
}

void Tag::setTagName()
{
    if (tagType == TagType::FullTag)
    {
        unsigned minIndex = tagStr.find('>');

        if (minIndex > tagStr.find(' '))
            minIndex = tagStr.find(' ');
        
        tagName = std::string(tagStr.begin() + 1, tagStr.begin() + minIndex);
    }
    
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

    else if (std::count(tagStr.begin(), tagStr.end(), '<') >= 2)
        tagType = TagType::FullTag;
    
    else
        tagType = TagType::SingleTag;
}


void Tag::printTag()
{
    std::cout << "Tag name: " << tagName << '\n';
    std::cout << "Tag str: " << tagStr << '\n';
    std::cout << "Tag type: " << static_cast<int>(tagType) << '\n';
    
    for (auto& element: childTags)
    {
        std::cout << "Child name: " << element.tagName << '\n';
    }
}

void Tag::nestAllTags()
{
    for (int i=0; i < childTags.size(); i++)
    {
        nestATag(i);
        childTags[i].childTags[0].printTag();
    }
}

void Tag::nestATag(unsigned tagIndex)
{
    int matchingTagIndex = getMatchingTagIndex(tagIndex);
    if (matchingTagIndex == -1)
        return;
    
    std::string totalTagStr = "";
    for (int i = tagIndex; i <= matchingTagIndex; i++)
        totalTagStr += childTags[i].tagStr;
    // copies inner tags between the start/end tags to the child tag vector
    childTags[tagIndex].childTags = std::vector<Tag>(childTags.begin() + tagIndex + 1,
                                                  childTags.begin() + matchingTagIndex);
    // erases child tags
    childTags.erase(childTags.begin() + tagIndex+1, childTags.begin() + matchingTagIndex+1);

    childTags[tagIndex] = Tag(totalTagStr);
}
