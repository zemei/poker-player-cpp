#include "player.h"

#include <initializer_list>
#include <vector>

//Continous delivery poker

const char* Player::VERSION = "Default C++ folding player";

struct Card {
    CardType type;
    CardColor color;
};

struct GameState {
    int small_blind;
    int stack;

    bool has_A;
    bool has_pair;

    PositionType position;

    std::vector<Card> hand_cards;
    std::vector<Card> comm_cards;
};


//////////////////////////////////
//START of Code section for Laja


//END of Code section for Laja
//////////////////////////////////






//////////////////////////////////
//START of Code section for Gabor

class Action
{
    ActionType  mType;
    int         mValue;

public:
    Action(ActionType type, int value = 0) : mType(type), mValue(value) {}
};

class Condition
{
    ConditionType       mType;
    std::vector<int>    mArguments;

public:
    template <typename T>
    Condition(ConditionType type, std::initializer_list<T> arguments)
        : mType(type)
    {
        for (auto i: arguments)
            mArguments.push_back(i);

        if (type == ConditionType::CARDS && mArguments.size() > 0 && mArguments.back() != (int)CardType::SEPARATOR)
            mArguments.push_back((int)CardType::SEPARATOR);

    }

    bool evaluate(const GameState& state)
    {
        switch(mType)
        {
        case ConditionType::ACTION:
            {

            }
            break;
        case ConditionType::CARDS:
            {

            }
            break;
        case ConditionType::POSITION:
            {

            }
            break;
        case ConditionType::ROUND:
            {

            }
            break;
        }
        return true;
    }
};

class Trigger
{
    Action                  mAction;
    std::vector<Condition>  mConditions;

public:
    Trigger(Action action, std::initializer_list<Condition> conditions = {})
        : mAction(action), mConditions(conditions) {}

    bool evaluate(const GameState& state)
    {
        bool result = true;
        for (Condition i: mConditions)
        {
            result &= i.evaluate(state);
            if (!result)
                return false;
        }
        return true;
    }

    Action getAction() { return mAction; }
};

class Strategy
{
    Trigger                 mEnteringTrigger;
    std::vector<Trigger>    mTriggers;

public:
    Strategy(Trigger enteringTrigger) : mEnteringTrigger(enteringTrigger) {}

    void addTrigger(Trigger trigger) { mTriggers.push_back(trigger); }

    bool evaluate(const GameState& state)
    {
        return mEnteringTrigger.evaluate(state);
    }

    Action execute(const GameState& state)
    {
        for (Trigger i: mTriggers)
        {
            if (i.evaluate(state))
                return i.getAction();
        }

        return mEnteringTrigger.getAction();
    }
};

class StrategyManager
{
    std::vector<Strategy> mStrategies;

public:
    void addStrategy(Strategy strategy) { mStrategies.push_back(strategy); }

    Action execute(const GameState& state)
    {
        if (mStrategies.size() == 0)
            return Action(ActionType::FOLD);

        for (Strategy i: mStrategies)
        {
            if (i.evaluate(state))
                return i.execute(state);
        }

        return Action(ActionType::FOLD);
    }
};

//END of Code section for Gabor
//////////////////////////////////







//////////////////////////////////
//START of Code section for Andris


//END of Code section for Andris
//////////////////////////////////




//////////////////////////////////
//START of Code section for Tibi
CardType decodeCardType(std::string s)
{
    if (s == "2")
        return CardType::_2;
    if (s == "3")
        return CardType::_3;
    if (s == "4")
        return CardType::_4;
    if (s == "5")
        return CardType::_5;
    if (s == "6")
        return CardType::_6;
    if (s == "7")
        return CardType::_7;
    if (s == "8")
        return CardType::_8;
    if (s == "9")
        return CardType::_9;
    if (s == "10")
        return CardType::_10;
    if (s == "J")
        return CardType::J;
    if (s == "Q")
        return CardType::Q;
    if (s == "K")
        return CardType::K;
    if (s == "A")
        return CardType::A;

}
// Suit of the card. Possible values are: clubs,spades,hearts,diamonds
CardColor decodeCardColor(std::string s)
{
    if (s == "clubs")
        return CardColor::CLUBS;
    if (s == "spades")
        return CardColor::SPADES;
    if (s == "hearts")
        return CardColor::HEARTS;
    if (s == "diamonds")
        return CardColor::DIAMONDS;
}

void fillState(GameState& gs, json::Value game_state)
{
    gs.small_blind = game_state["small_blind"].ToInt();

    json::Value me = game_state["players"][game_state["in_action"].ToInt()];
    gs.stack = me["stack"];

    gs.has_A = me["hand"]["hole_cards"].ToArray()[0]["rank"].ToString() == "A" || me["hand"]["hole_cards"].ToArray()[1]["rank"].ToString() == "A";
    gs.has_pair = me["hand"]["hole_cards"].ToArray()[0]["rank"].ToString() == me["hand"]["hole_cards"].ToArray()[1]["rank"].ToString();

    gs.hand_cards.push_back({decodeCardType(me["hand"]["hole_cards"].ToArray()[0]["rank"].ToString()), decodeCardColor(me["hand"]["hole_cards"].ToArray()[0]["suit"].ToString())});
    gs.hand_cards.push_back({decodeCardType(me["hand"]["hole_cards"].ToArray()[1]["rank"].ToString()), decodeCardColor(me["hand"]["hole_cards"].ToArray()[1]["suit"].ToString())});
}

int Player::betRequest(json::Value game_state)
{
    GameState gs;
    fillState(gs, game_state);

    //return (gs.has_A || gs.has_pair )? 1000 : 0;
    return ((gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type > CardType::_8) ||
            (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type > CardType::_8) ||
            (gs.hand_cards[0].type == CardType::K && gs.hand_cards[1].type > CardType::J) ||
            (gs.hand_cards[1].type == CardType::K && gs.hand_cards[0].type > CardType::J) ||
            (gs.has_pair && gs.hand_cards[0].type > CardType::_8)) ? 1000 : 0;
}

void Player::showdown(json::Value game_state)
{
}
//END of Code section for Tibi
//////////////////////////////////
