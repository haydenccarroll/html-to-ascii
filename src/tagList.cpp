#include "tagList.hpp"
#include <vector>
#include <string>
#include "tag.hpp"

TagList::TagList()
{
}

TagList::TagList(std::vector<Tag> tagVec)
{
    m_vec = tagVec;
}

TagList::~TagList()
{
}

std::vector<Tag>::iterator TagList::begin()
{
    return m_vec.begin();
}

std::vector<Tag>::iterator TagList::end()
{
    return m_vec.end();
}


bool TagList::isEmpty()
{
    return m_vec.size();
}


void TagList::nestAllTags()
{
    for (std::size_t i= 0; i < m_vec.size(); i++)
        nestTag(i);
}

void TagList::nestTag(unsigned tagIndex)
{
    int matchingTagIndex = getMatchingTagIndex(tagIndex);
    if (matchingTagIndex == -1)
        return;
    
    // copies inner tags between the start/end tags to the child tag vector
    *(m_vec[tagIndex].childTags) = std::vector<Tag>(m_vec.begin() + tagIndex + 1,
                                                  m_vec.begin() + matchingTagIndex);
    // erases child tags
    m_vec.erase(m_vec.begin() + tagIndex+1, m_vec.begin() + matchingTagIndex+1);

    m_vec[tagIndex].childTags->nestAllTags();
}

int TagList::getMatchingTagIndex(unsigned tagIndex)
{
    if (m_vec.size() <= tagIndex) return -1;

    // Useful for parsing the following: <div> <div></div> </div>
    int openTagCount = 0; // num of unresolved tags.


    std::string currentTagName = m_vec[tagIndex].tagName;
    int endIndex = -1; // index of matching tag
    for (unsigned i = tagIndex+1; i < m_vec.size(); i++)
    {
        if (m_vec[i].tagName == currentTagName && 
            m_vec[i].tagType == TagType::OpenTag)
        {
            openTagCount++;
        }

        if (m_vec[i].tagName == currentTagName && 
            m_vec[i].tagType == TagType::CloseTag)
        {
            if (openTagCount == 0)
                return i; // end index
            openTagCount--;
        }
    }
    return -1;
}

void TagList::pushBack(const Tag& tag)
{
    m_vec.push_back(tag);
}