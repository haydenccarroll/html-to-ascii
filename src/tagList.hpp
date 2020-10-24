#pragma once

#include <vector>

class Tag; // forward declaration of Tag (located in tag.h)

class TagList
{
public:

TagList();
TagList(std::vector<Tag> tagVec);
~TagList();

std::vector<Tag>::iterator begin();
std::vector<Tag>::iterator end();

void nestAllTags();
void pushBack(const Tag& tag);
bool isEmpty();


private:
std::vector<Tag> m_vec;

void nestTag(unsigned tagIndex);
int getMatchingTagIndex(unsigned tagIndex);

};