#ifndef __STRING_MATCH_H__
#define __STRING_MATCH_H__

#include <string>
#include <regex>

inline bool match(const std::string &context, const std::string &patten)
{
    std::regex reg(patten);
    return std::regex_match(context, reg);
}

inline int parse_major_version(const std::string &version)
{
    std::regex reg("^(\\d+)\\.\\d+\\.\\d+$");
    std::smatch match;
    if (!std::regex_match(version, match, reg))
        return -1;
    return std::stoi(match[1]);
}

#endif // __STRING_MATCH_H__