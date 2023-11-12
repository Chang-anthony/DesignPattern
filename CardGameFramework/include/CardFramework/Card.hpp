#ifndef _CARD_H_
#define _CARD_H_

class Card
{
private:
    /* data */
public:
    Card(/* args */);
    ~Card();

    virtual void render() = 0;
};

#endif /* _CARD_H_ */
