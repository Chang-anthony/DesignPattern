#include "../include/UnoCard.hpp"

UnoCard::UnoCard(Color color,Number number):Card(),color(color),number(number)
{

}

void UnoCard::render()
{
    std::cout << ColorToName(this->color)[0]  
    << "[" << NumberToString(this->number) << "]";
}

bool UnoCard::IsSame(UnoCard* card)
{
    return this->color == card->GetColor() || this->number == card->GetNumber();
}

Number UnoCard::GetNumber()
{
    return this->number;
}

Color UnoCard::GetColor()
{
    return this->color;
}

void UnoCard::SetColor(Color color)
{
    this->color = color;
}

void UnoCard::SetNumber(Number number)
{
    this->number = number;
}

std::vector<Card*> UnoCard::GenCards()
{
    std::vector<Card*> cards = std::vector<Card*>();
    //1
    //A
    cards.push_back(new UnoCard(Color::Bule,Number::one));
    cards.push_back(new UnoCard(Color::Red,Number::one));
    cards.push_back(new UnoCard(Color::Yellow,Number::one));
    cards.push_back(new UnoCard(Color::Green,Number::one));
    //2
    cards.push_back(new UnoCard(Color::Bule,Number::Sec));
    cards.push_back(new UnoCard(Color::Red,Number::Sec));
    cards.push_back(new UnoCard(Color::Yellow,Number::Sec));
    cards.push_back(new UnoCard(Color::Green,Number::Sec));
    //3
    cards.push_back(new UnoCard(Color::Bule,Number::Thr));
    cards.push_back(new UnoCard(Color::Red,Number::Thr));
    cards.push_back(new UnoCard(Color::Yellow,Number::Thr));
    cards.push_back(new UnoCard(Color::Green,Number::Thr));
    //4
    cards.push_back(new UnoCard(Color::Bule,Number::Four));
    cards.push_back(new UnoCard(Color::Red,Number::Four));
    cards.push_back(new UnoCard(Color::Yellow,Number::Four));
    cards.push_back(new UnoCard(Color::Green,Number::Four));
    //5
    cards.push_back(new UnoCard(Color::Bule,Number::Five));
    cards.push_back(new UnoCard(Color::Red,Number::Five));
    cards.push_back(new UnoCard(Color::Yellow,Number::Five));
    cards.push_back(new UnoCard(Color::Green,Number::Five));
    //6
    cards.push_back(new UnoCard(Color::Bule,Number::Six));
    cards.push_back(new UnoCard(Color::Red,Number::Six));
    cards.push_back(new UnoCard(Color::Yellow,Number::Six));
    cards.push_back(new UnoCard(Color::Green,Number::Six));
    //7
    cards.push_back(new UnoCard(Color::Bule,Number::Seven));
    cards.push_back(new UnoCard(Color::Red,Number::Seven));
    cards.push_back(new UnoCard(Color::Yellow,Number::Seven));
    cards.push_back(new UnoCard(Color::Green,Number::Seven));
    //8
    cards.push_back(new UnoCard(Color::Bule,Number::Eight));
    cards.push_back(new UnoCard(Color::Red,Number::Eight));
    cards.push_back(new UnoCard(Color::Yellow,Number::Eight));
    cards.push_back(new UnoCard(Color::Green,Number::Eight));
    //9
    cards.push_back(new UnoCard(Color::Bule,Number::Night));
    cards.push_back(new UnoCard(Color::Red,Number::Night));
    cards.push_back(new UnoCard(Color::Yellow,Number::Night));
    cards.push_back(new UnoCard(Color::Green,Number::Night));
    //10
    cards.push_back(new UnoCard(Color::Bule,Number::Ten));
    cards.push_back(new UnoCard(Color::Red,Number::Ten));
    cards.push_back(new UnoCard(Color::Yellow,Number::Ten));
    cards.push_back(new UnoCard(Color::Green,Number::Ten));
}

UnoCard::~UnoCard()
{
}