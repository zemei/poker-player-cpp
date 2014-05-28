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
    BB_HIGHER,
    BB_LOWER,
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
    B,
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
    BET_HALF_POT,
    ALL_IN,
};

//END of Enums
//////////////////////////////////


struct Card {
    CardType type;
    CardColor color;
};

struct GameState {
    int small_blind;
    int stack;
    int player_num;

    bool has_A;
    bool has_pair;

    ActionType action;

    PositionType position;
    RoundType round;

    std::vector<Card> hand_cards;
    std::vector<Card> comm_cards;
};

class HandEvaluator{
  public:
    bool isHigherOrEqual(const GameState &currentState, std::vector<CardType> rangeVec);
    static bool selfTest();
  private:
    bool checkInRange(std::vector<CardType> handVec, std::vector<CardType> rangeVec);

};


class Player
{
    public:
        static const char* VERSION;

        static int betRequest(json::Value game_state);

        static void showdown(json::Value game_state);
        static bool fillState(GameState& gs, json::Value game_state);
};

#endif
