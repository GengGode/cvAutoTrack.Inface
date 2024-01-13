#ifndef __STRING_MATCH_H__
#define __STRING_MATCH_H__

#include <string>
#include <regex>

bool match(const std::string &context, const std::string &patten)
{
    std::regex reg(patten);
    return std::regex_match(context, reg);
}

#endif // __STRING_MATCH_H__