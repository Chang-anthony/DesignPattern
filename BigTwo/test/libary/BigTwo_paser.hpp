#ifndef _BIGTWO_PASER_H_
#define _BIGTWO_PASER_H_

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

class FileIterator;
class Card;

class BigTwo_paser
{
private:

public:
    BigTwo_paser();
    ~BigTwo_paser();

    static std::tuple<std::vector<Card*>, std::vector<std::string>, std::vector<std::vector<int>>> parser(const std::string& filepath);
protected:
    static std::vector<Card*> cardparser(std::string& str_);
    static std::vector<std::vector<int>> playparser(std::vector<std::string>& strs);
};

#endif /* _BIGTWO_PASER_H_ */
