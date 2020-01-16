#ifndef RESULT_H
#define RESULT_H

struct result{
    // Integer vector holding values related to distances
    std::vector<int> distances;
    // Char vector holding values related to headings {'N', 'S', 'E', 'W'}
    std::vector<char> headings;
};
#endif