#ifndef _UNOCARD_H_
#define _UNOCARD_H_

#include "../include/CardFramework/Card.hpp"
#include "../include/Uno/Color.hpp"
#include "../include/Uno/Number.hpp"
#include <iostream>
#include <vector>


class UnoCard : public Card
{
private:
    /* data */
    Number number;
    Color color;
public:
    UnoCard(Color color,Number number);
    ~UnoCard();

    //Getter
    Color GetColor();
    Number GetNumber();
    static std::vector<Card*> GenCards();
    bool IsSame(UnoCard* card);

    //setter
    void SetNumber(Number number);
    void SetColor(Color color);

    void render() override;
};


#endif /* _UNOCARD_H_ */
