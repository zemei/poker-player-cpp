#include "player.h"
#include "strategy.h"

#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>


//Continous delivery poker

const char* Player::VERSION = "Default C++ folding player";

//////////////////////////////////
//START of Code section for Laja

//PUBLIC interface
bool HandEvaluator::selfTest(){

    std::cout << "Running HandEvaluator self Test" << std::endl;

    bool testResult=true;

    //create Device Under Test
    HandEvaluator DUT;

    //init test input
    //TC 0
    {
        GameState testState;
        testState.hand_cards.push_back({CardType::A, CardColor::HEARTS});
        testState.hand_cards.push_back({CardType::A, CardColor::SPADES});
        std::vector<CardType> testRange;
        testRange.push_back(CardType::A);
        testRange.push_back(CardType::_2);
        testRange.push_back(CardType::SUITED);

        if( !DUT.isHigherOrEqual( testState, testRange ) ) {
			std::cout << "Range Test 0 failed " << std::endl;
			testResult = false;
		}
    }

    //TC 1
    {
        GameState testState;
        testState.hand_cards.push_back({CardType::A, CardColor::HEARTS});
        testState.hand_cards.push_back({CardType::J, CardColor::SPADES});
        std::vector<CardType> testRange;
        testRange.push_back(CardType::A);
        testRange.push_back(CardType::_2);
        testRange.push_back(CardType::SUITED);

        if( DUT.isHigherOrEqual( testState, testRange ) ) {
			std::cout << "Range Test 1 failed " << std::endl;
			testResult = false;
		}
    }

    //TC 2
    {
        GameState testState;
        testState.hand_cards.push_back({CardType::A, CardColor::HEARTS});
        testState.hand_cards.push_back({CardType::J, CardColor::HEARTS});
        std::vector<CardType> testRange;
        testRange.push_back(CardType::A);
        testRange.push_back(CardType::_2);
        testRange.push_back(CardType::SUITED);

		if( !DUT.isHigherOrEqual( testState, testRange ) ) {
			std::cout << "Range Test 2 failed " << std::endl;
			testResult = false;
		}
    }

    //TC 3
    {
        GameState testState;
        testState.hand_cards.push_back({CardType::K, CardColor::HEARTS});
        testState.hand_cards.push_back({CardType::_2, CardColor::SPADES});
        std::vector<CardType> testRange;
        testRange.push_back(CardType::K);
        testRange.push_back(CardType::_10);

        if( DUT.isHigherOrEqual( testState, testRange ) ) {
			std::cout << "Range Test 3 failed " << std::endl;
			testResult = false;
		}
    }

    //TC 3
    {
        GameState testState;
        testState.hand_cards.push_back({CardType::K, CardColor::HEARTS});
        testState.hand_cards.push_back({CardType::K, CardColor::SPADES});
        std::vector<CardType> testRange;
        testRange.push_back(CardType::_10);
        testRange.push_back(CardType::_10);

        if( !DUT.isHigherOrEqual( testState, testRange ) ) {
            std::cout << "Range Test 4 failed " << std::endl;
            testResult = false;
        }
    }

    if(testResult){
        std::cout << "Self Test OK" << std::endl;
    } else {
        std::cout << "Self Test FAILED" << std::endl;
    }

    return testResult;
};

bool HandEvaluator::isHigherOrEqual(const GameState &currentState, std::vector<CardType> rangeVec){

    //init a vector for the current hand
    std::vector<CardType> handVec = {currentState.hand_cards[0].type, currentState.hand_cards[1].type};
    //sorting the input vectors
    std::sort(rangeVec.begin(), rangeVec.end());
    std::sort(handVec.begin(), handVec.end());


    switch (rangeVec.size()) {
    case 1:
        //TODO determine hand
        return false;
        break;

    case 2:
        //if the range to be checked is unsuited
        return HandEvaluator::checkInRange(handVec, rangeVec);
        break;

    case 3:
        //if the range to be checked is suited
        if ((currentState.hand_cards[0].color == currentState.hand_cards[1].color) || (currentState.hand_cards[0].type==currentState.hand_cards[1].type)){
            return HandEvaluator::checkInRange(handVec, rangeVec);
        } else {
            return false;
        }

    default:
        //by default return false
        return false;
        break;
    }

}

//PRIVATE interface
bool HandEvaluator::checkInRange(std::vector<CardType> handVec, std::vector<CardType> rangeVec){
    if(rangeVec[0]==rangeVec[1]){
        return ((handVec[0]>=rangeVec[0]));
    } else {
        return ((rangeVec[1]==handVec[1]) && (handVec[0]>=rangeVec[0]));
    }
};
//END of Code section for Laja
//////////////////////////////////






//////////////////////////////////
//START of Code section for Gabor


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

bool Player::fillState(GameState& gs, json::Value game_state)
{
    gs.small_blind = game_state["small_blind"].ToInt();
    gs.call_value = game_state["current_buy_in"].ToInt();

    const int players_length = game_state["players"].ToArray().size();
    const int dealer_index = game_state["dealer"].ToInt();
    const int me_index = game_state["in_action"].ToInt();
    json::Value me = game_state["players"].ToArray()[me_index];
    gs.stack = me["stack"];

    gs.call_value -= me["bet"].ToInt();

    gs.has_A = me["hole_cards"].ToArray()[0]["rank"].ToString() == "A" || me["hole_cards"].ToArray()[1]["rank"].ToString() == "A";
    gs.has_pair = me["hole_cards"].ToArray()[0]["rank"].ToString() == me["hole_cards"].ToArray()[1]["rank"].ToString();

    gs.hand_cards.push_back({decodeCardType(me["hole_cards"].ToArray()[0]["rank"].ToString()), decodeCardColor(me["hole_cards"].ToArray()[0]["suit"].ToString())});
    gs.hand_cards.push_back({decodeCardType(me["hole_cards"].ToArray()[1]["rank"].ToString()), decodeCardColor(me["hole_cards"].ToArray()[1]["suit"].ToString())});

    const int comm_card_num = game_state["community_cards"].size();
    for (int i = 0; i < comm_card_num; ++i)
        gs.comm_cards.push_back({decodeCardType(game_state["community_cards"].ToArray()[i]["rank"].ToString()), decodeCardColor(game_state["community_cards"].ToArray()[1]["suit"].ToString())});

    // Action
    {
        gs.action = ActionType::FOLD;
        int index = dealer_index;
        int counter = players_length;
        int raise = 0;
        int prev_bet = gs.small_blind * 2;
        for (;counter--;index=(index+1)%players_length) {
            json::Value p = game_state["players"].ToArray()[index];
            if (p["status"] != "out") {
                if (p["bet"].ToInt() > prev_bet) {
                    raise++;
                    prev_bet = p["bet"].ToInt();
                }
            }
        }
        switch (raise) {
            case 1: gs.action = ActionType::RAISE_1;
            case 2: gs.action = ActionType::RAISE_2;
            case 3: gs.action = ActionType::RAISE_3;
            case 4: gs.action = ActionType::RAISE_4;
        }
    }

    // Position

    {
        gs.player_num = 0;
        int index = dealer_index;
        int counter = players_length;
        int pos = static_cast<int>(PositionType::D);
        for (;counter--;index=(index+1)%players_length) {
            json::Value p = game_state["players"].ToArray()[index];
            if (p["status"] != "out") {
                gs.player_num++;
                pos++;
                if (index == me_index) {
                    gs.position = static_cast<PositionType>(pos);
                }
            }
        }
        if (gs.player_num == 2) {
            if (gs.position == PositionType::D) {
                gs.position = PositionType::SB;
            } else {
                gs.position = PositionType::BB;
            }
        }
    }
    return true;
}

int Player::betRequest(json::Value game_state)
{
    GameState gs;
    fillState(gs, game_state);

    /*StrategyManager manager;
    initStrategies(manager);
    Action action = manager.execute(gs);
    switch (action.mType) {
        case ActionType::ALL_IN:
            return 1000;
        case ActionType::CALL:
            return gs.call_value;
        case ActionType::FOLD:
            return 0;
    }*/

    //return (gs.has_A || gs.has_pair )? 1000 : 0;
    if (gs.player_num == 5 && gs.action >= ActionType::RAISE_1 &&
            (
                (gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type >= CardType::Q) ||
                (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type >= CardType::Q) ||
                (gs.has_pair && gs.hand_cards[0].type >= CardType::J)
            )
        )
    {
        return 1000;
    }
    if (gs.player_num == 3 && gs.action >= ActionType::RAISE_1 &&
            (
                (gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type >= CardType::_9) ||
                (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type >= CardType::_9) ||
                (gs.hand_cards[0].type == CardType::K && gs.hand_cards[1].type >= CardType::J) ||
                (gs.hand_cards[1].type == CardType::K && gs.hand_cards[0].type >= CardType::J) ||
                (gs.has_pair && gs.hand_cards[0].type >= CardType::_2)
            )
        )
    {
        return 1000;
    }

    if (gs.player_num < 3 && gs.action >= ActionType::RAISE_1 &&
            (
                (gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type >= CardType::_2) ||
                (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type >= CardType::_2) ||
                (gs.hand_cards[0].type == CardType::K && gs.hand_cards[1].type >= CardType::_6) ||
                (gs.hand_cards[1].type == CardType::K && gs.hand_cards[0].type >= CardType::_6) ||
                (gs.hand_cards[0].type == CardType::Q && gs.hand_cards[1].type >= CardType::_8) ||
                (gs.hand_cards[1].type == CardType::Q && gs.hand_cards[0].type >= CardType::_8) ||
                (gs.hand_cards[0].type == CardType::J && gs.hand_cards[1].type >= CardType::_9) ||
                (gs.hand_cards[1].type == CardType::J && gs.hand_cards[0].type >= CardType::_9) ||
                (gs.hand_cards[0].type == CardType::_10 && gs.hand_cards[1].type >= CardType::_9) ||
                (gs.hand_cards[1].type == CardType::_10 && gs.hand_cards[0].type >= CardType::_9) ||
                (gs.has_pair && gs.hand_cards[0].type >= CardType::_2)
            )
        )
    {
        return 1000;
    }

    if (gs.player_num < 3 &&
            (
                (gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type >= CardType::_2) ||
                (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type >= CardType::_2) ||
                (gs.hand_cards[0].type == CardType::K && gs.hand_cards[1].type >= CardType::_6) ||
                (gs.hand_cards[1].type == CardType::K && gs.hand_cards[0].type >= CardType::_6) ||
                (gs.hand_cards[0].type == CardType::Q && gs.hand_cards[1].type >= CardType::_8) ||
                (gs.hand_cards[1].type == CardType::Q && gs.hand_cards[0].type >= CardType::_8) ||
                (gs.hand_cards[0].type == CardType::J && gs.hand_cards[1].type >= CardType::_9) ||
                (gs.hand_cards[1].type == CardType::J && gs.hand_cards[0].type >= CardType::_9) ||
                (gs.hand_cards[0].type == CardType::_10 && gs.hand_cards[1].type >= CardType::_9) ||
                (gs.hand_cards[1].type == CardType::_10 && gs.hand_cards[0].type >= CardType::_9) ||
                (gs.hand_cards[0].type == CardType::_9 && gs.hand_cards[1].type >= CardType::_8) ||
                (gs.hand_cards[1].type == CardType::_9 && gs.hand_cards[0].type >= CardType::_8) ||
                (gs.hand_cards[0].type == CardType::_8 && gs.hand_cards[1].type >= CardType::_7) ||
                (gs.hand_cards[1].type == CardType::_8 && gs.hand_cards[0].type >= CardType::_7) ||
                (gs.hand_cards[0].type == CardType::_7 && gs.hand_cards[1].type >= CardType::_6) ||
                (gs.hand_cards[1].type == CardType::_7 && gs.hand_cards[0].type >= CardType::_6) ||
                (gs.has_pair && gs.hand_cards[0].type >= CardType::_2)
            )
        )
    {
        return 1000;
    }

    return ((gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type >= CardType::J) ||
            (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type >= CardType::J) ||
            (gs.hand_cards[0].type == CardType::K && gs.hand_cards[1].type >= CardType::Q && gs.hand_cards[0].color == gs.hand_cards[1].color) ||
            (gs.hand_cards[1].type == CardType::K && gs.hand_cards[0].type >= CardType::Q && gs.hand_cards[0].color == gs.hand_cards[1].color) ||
            //(gs.hand_cards[0].type == CardType::Q && gs.hand_cards[1].type > CardType::J && gs.hand_cards[0].color == gs.hand_cards[1].color) ||
            //(gs.hand_cards[1].type == CardType::Q && gs.hand_cards[0].type > CardType::J && gs.hand_cards[0].color == gs.hand_cards[1].color) ||
            (gs.has_pair && gs.hand_cards[0].type >= CardType::_9)) ? 1000 :
            (
                (
                    (gs.position == PositionType::D) &&
                    (gs.action == ActionType::FOLD || gs.action == ActionType::CALL) &&
                    (
                        (gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type >= CardType::_6) ||
                        (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type >= CardType::_6) ||
                        (gs.hand_cards[0].type == CardType::K && gs.hand_cards[1].type >= CardType::_10 && gs.hand_cards[0].color == gs.hand_cards[1].color) ||
                        (gs.hand_cards[1].type == CardType::K && gs.hand_cards[0].type >= CardType::_10 && gs.hand_cards[0].color == gs.hand_cards[1].color) ||
                        (gs.has_pair && gs.hand_cards[0].type >= CardType::_5)
                    )
                ) ||
                (
                    (gs.position == PositionType::SB || gs.position == PositionType::BB) &&
                    (gs.action == ActionType::FOLD || gs.action == ActionType::CALL) &&
                    (
                        (gs.hand_cards[0].type == CardType::A && gs.hand_cards[1].type >= CardType::_2) ||
                        (gs.hand_cards[1].type == CardType::A && gs.hand_cards[0].type >= CardType::_2) ||
                        (gs.hand_cards[0].type == CardType::K && gs.hand_cards[1].type >= CardType::_9) ||
                        (gs.hand_cards[1].type == CardType::K && gs.hand_cards[0].type >= CardType::_9) ||
                        (gs.has_pair && gs.hand_cards[0].type >= CardType::_2)
                    )
                )? 1000 : 0
            );
}

void Player::showdown(json::Value game_state)
{
}
//END of Code section for Tibi
//////////////////////////////////
