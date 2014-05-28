#ifndef PLAYER_H
#define PLAYER_H

#include "json.h"

//////////////////////////////////
//START

enum class ConditionType
{
    CARDS,
    POSITION,
    ROUND,
    ACTION,
};

enum class CardType
{
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _10,
    J,
    Q,
    K,
    A,
    HIGH_CARD,
    LOW_PAIR,
    MID_PAIR,
    TOP_PAIR,
    TWO_PAIRS,
    DRILL,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    POKER,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH,
    SUITED,
    SEPARATOR,
};

enum class CardColor
{
    SPADES,
    CLUBS,
    HEARTS,
    DIAMONDS,
};

enum class PositionType
{
    SB,
    BB,
    UTG,
    CO,
    D,
};

enum class RoundType
{
    PREFLOP,
    FLOP,
    TURN,
    RIVER,
};

enum class ActionType
{
    FOLD,
    CHECK,
    CALL,
    RAISE_1,
    RAISE_2,
    RAISE_3,
    RAISE_4,
};

//END of Enums
//////////////////////////////////

class Player
{
    public:
        static const char* VERSION;

        static int betRequest(json::Value game_state);

        static void showdown(json::Value game_state);
};

#endif
