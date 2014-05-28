#include "strategy.h"

bool Condition::evaluate(const GameState& state)
{
    switch(mType)
    {
    case ConditionType::ACTION:
        {
            if (mArguments.size() == 0)
                return false;

            for (int i: mArguments)
            {
                if ((ActionType)i == state.action)
                    return true;
            }

            return false;
        }
        break;
    case ConditionType::NOT_ACTION:
        {
            if (mArguments.size() == 0)
                return false;

            for (int i: mArguments)
            {
                if ((ActionType)i == state.action)
                    return false;
            }

            return true;
        }
        break;
    case ConditionType::CARDS:
        {
            if (mArguments.size() == 0)
                return false;

			std::vector<CardType> cardSet;

            //bool isSuited = false;
            for (int i: mArguments)
            {
                if (i == (int)CardType::SEPARATOR)
                {
                    if (cardSet.size() == 0)
                    {
                        //isSuited = false;
                        continue;
                    }

                    HandEvaluator evaluator;
                    if (evaluator.isHigherOrEqual(state, cardSet))
                        return true;

                    cardSet.clear();
                }
                else
                {
                    /*if (i == (int)CardType::SUITED)
                        isSuited = true;
                    else*/
                        cardSet.push_back((CardType)i);
                }
            }

            return false;
        }
        break;
    case ConditionType::POSITION:
        {
            if (mArguments.size() == 0)
                return false;

            PositionType pos = (PositionType)mArguments[0];
            if (pos == PositionType::B)
            {
                if (state.position == PositionType::SB || state.position == PositionType::BB)
                    return true;
                else
                    return false;
            }
            if (pos == state.position)
                return true;

            return false;
        }
        break;
    case ConditionType::ROUND:
        {
            if (mArguments.size() == 0)
                return false;

            if (state.round == (RoundType)mArguments[0])
                return true;

            return false;
        }
        break;
    case ConditionType::BB_HIGHER:
        {
            if (state.small_blind == 0 || mArguments.size() == 0)
                return false;

            int ratio = state.stack / state.small_blind / 2;
            if ((int)mArguments[0] > ratio)
                return true;

            return false;
        }
        break;
    case ConditionType::BB_LOWER:
        {
            if (state.small_blind == 0 || mArguments.size() == 0)
                return false;

            int ratio = state.stack / state.small_blind / 2;
            if ((int)mArguments[0] < ratio)
                return true;

            return false;
        }
        break;
    case ConditionType::MORE_PLAYER:
        {
            if (mArguments.size() == 0)
                return false;

            if ((int)mArguments[0] < state.player_num)
                return true;

            return false;
        }
        break;
    case ConditionType::LESS_PLAYER:
        {
            if (mArguments.size() == 0)
                return false;

            if ((int)mArguments[0] > state.player_num)
                return true;

            return false;
        }
        break;
    }

    return true;
}

void initStrategies(StrategyManager& manager)
{
    /*strategy_1.addTrigger({
        {}, {
            {},
            {}
        }
    });*/

//////////////////////////////////
//STRATEGY 1
    Strategy strategy_1({
        {ActionType::NO_ACTION}, {
            {ConditionType::BB_HIGHER, {15}},
            {ConditionType::ROUND, {RoundType::PREFLOP}}
        }
    });

//FIRST LINE
	strategy_1.addTrigger({
		{ActionType::ALL_IN}, {
            {ConditionType::POSITION, {PositionType::UTG}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
			{ConditionType::CARDS, {
				CardType::_8, CardType::_8, CardType::SEPARATOR,
				CardType::A, CardType::_10, CardType::SUITED, CardType::SEPARATOR,
				CardType::A, CardType::J, CardType::SEPARATOR
			}}
		}
	});
	strategy_1.addTrigger({
		{ActionType::ALL_IN}, {
			{ConditionType::POSITION, {PositionType::CO}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
			{ConditionType::CARDS, {
				CardType::_6, CardType::_6, CardType::SEPARATOR,
				CardType::A, CardType::_5, CardType::SUITED, CardType::SEPARATOR,
				CardType::K, CardType::J, CardType::SUITED, CardType::SEPARATOR,
				CardType::A, CardType::_8, CardType::SEPARATOR,
				CardType::K, CardType::Q, CardType::SEPARATOR
			}}
		}
	});
	strategy_1.addTrigger({
		{ActionType::ALL_IN}, {
			{ConditionType::POSITION, {PositionType::D}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
			{ConditionType::CARDS, {
				CardType::_2, CardType::_2, CardType::SEPARATOR,
				CardType::A, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
				CardType::K, CardType::_9, CardType::SUITED, CardType::SEPARATOR,
				CardType::Q, CardType::J, CardType::SUITED, CardType::SEPARATOR,
				CardType::A, CardType::_2, CardType::SEPARATOR,
				CardType::K, CardType::_10, CardType::SEPARATOR
			}}
		}
	});
    strategy_1.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::POSITION, {PositionType::B}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
            {ConditionType::CARDS, {
                CardType::_2, CardType::_2, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::K, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::Q, CardType::_5, CardType::SUITED, CardType::SEPARATOR,
                CardType::J, CardType::_8, CardType::SUITED, CardType::SEPARATOR,
                CardType::_10, CardType::_9, CardType::SUITED, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SEPARATOR,
                CardType::K, CardType::_5, CardType::SEPARATOR,
                CardType::Q, CardType::_9, CardType::SEPARATOR,
                CardType::J, CardType::_10, CardType::SEPARATOR
            }}
        }
    });

//SECOND LINE
    strategy_1.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::LESS_PLAYER, {4}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
            {ConditionType::CARDS, {
                CardType::_2, CardType::_2, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::K, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::Q, CardType::_5, CardType::SUITED, CardType::SEPARATOR,
                CardType::J, CardType::_8, CardType::SUITED, CardType::SEPARATOR,
                CardType::_10, CardType::_9, CardType::SUITED, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SEPARATOR,
                CardType::K, CardType::_5, CardType::SEPARATOR,
                CardType::Q, CardType::_9, CardType::SEPARATOR,
                CardType::J, CardType::_10, CardType::SEPARATOR
            }}
        }
    });

//THIRD LINE
    strategy_1.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::LESS_PLAYER, {4}},
            {ConditionType::ACTION, {ActionType::RAISE_1, ActionType::RAISE_2, ActionType::RAISE_3, ActionType::RAISE_4}},
            {ConditionType::CARDS, {
                CardType::_2, CardType::_2, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::K, CardType::_8, CardType::SUITED, CardType::SEPARATOR,
                CardType::Q, CardType::_9, CardType::SUITED, CardType::SEPARATOR,
                CardType::J, CardType::_10, CardType::SUITED, CardType::SEPARATOR,
                CardType::A, CardType::_6, CardType::SEPARATOR,
                CardType::K, CardType::_9, CardType::SEPARATOR,
                CardType::Q, CardType::J, CardType::SEPARATOR
            }}
        }
    });

//LAST LINE
    strategy_1.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::CARDS, {
                CardType::Q, CardType::Q, CardType::SEPARATOR,
            }}
        }
    });

//////////////////////////////////
//STRATEGY 2
    Strategy strategy_2({
        {ActionType::NO_ACTION}, {
            {ConditionType::BB_LOWER, {15}},
            {ConditionType::ROUND, {RoundType::PREFLOP}}
        }
    });
    strategy_2.addTrigger({
        {ActionType::BET_HALF_POT}, {
            {ConditionType::POSITION, {PositionType::UTG}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
            {ConditionType::CARDS, {
                CardType::_8, CardType::_8, CardType::SEPARATOR,
                CardType::A, CardType::_10, CardType::SUITED, CardType::SEPARATOR,
                CardType::A, CardType::J, CardType::SEPARATOR
            }}
        }
    });
    strategy_2.addTrigger({
        {ActionType::BET_HALF_POT}, {
            {ConditionType::POSITION, {PositionType::CO}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
            {ConditionType::CARDS, {
                CardType::_6, CardType::_6, CardType::SEPARATOR,
                CardType::A, CardType::_5, CardType::SUITED, CardType::SEPARATOR,
                CardType::K, CardType::J, CardType::SUITED, CardType::SEPARATOR,
                CardType::A, CardType::_8, CardType::SEPARATOR,
                CardType::K, CardType::Q, CardType::SEPARATOR
            }}
        }
    });
    strategy_2.addTrigger({
        {ActionType::BET_HALF_POT}, {
            {ConditionType::POSITION, {PositionType::D}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
            {ConditionType::CARDS, {
                CardType::_2, CardType::_2, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::K, CardType::_9, CardType::SUITED, CardType::SEPARATOR,
                CardType::Q, CardType::J, CardType::SUITED, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SEPARATOR,
                CardType::K, CardType::_10, CardType::SEPARATOR
            }}
        }
    });
    strategy_2.addTrigger({
        {ActionType::BET_HALF_POT}, {
            {ConditionType::POSITION, {PositionType::B}},
            {ConditionType::ACTION, {ActionType::FOLD, ActionType::CHECK}},
            {ConditionType::CARDS, {
                CardType::_2, CardType::_2, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::K, CardType::_2, CardType::SUITED, CardType::SEPARATOR,
                CardType::Q, CardType::_5, CardType::SUITED, CardType::SEPARATOR,
                CardType::J, CardType::_8, CardType::SUITED, CardType::SEPARATOR,
                CardType::_10, CardType::_9, CardType::SUITED, CardType::SEPARATOR,
                CardType::A, CardType::_2, CardType::SEPARATOR,
                CardType::K, CardType::_5, CardType::SEPARATOR,
                CardType::Q, CardType::_9, CardType::SEPARATOR,
                CardType::J, CardType::_10, CardType::SEPARATOR
            }}
        }
    });


//////////////////////////////////
//STRATEGY 3
    Strategy strategy_3({
        {ActionType::NO_ACTION}, {
            {ConditionType::BB_LOWER, {15}},
            {ConditionType::ROUND, {RoundType::FLOP}}
        }
    });

//FIRST LINE
    strategy_3.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::CARDS, {CardType::DRILL, CardType::SEPARATOR}}
        }
    });
    strategy_3.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::LESS_PLAYER, {4}},
            {ConditionType::CARDS, {CardType::TWO_PAIRS, CardType::SEPARATOR}}
        }
    });
    strategy_3.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::LESS_PLAYER, {3}},
            {ConditionType::CARDS, {CardType::TOP_PAIR, CardType::SEPARATOR}}
        }
    });
    strategy_3.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::LESS_PLAYER, {2}},
            {ConditionType::CARDS, {CardType::MID_PAIR, CardType::SEPARATOR}}
        }
    });
    strategy_3.addTrigger({
        {ActionType::FOLD}, {
            {ConditionType::CARDS, {CardType::LOW_PAIR, CardType::SEPARATOR}}
        }
    });
    strategy_3.addTrigger({
        {ActionType::FOLD}, {
            {ConditionType::CARDS, {CardType::HIGH_CARD, CardType::SEPARATOR}}
        }
    });

    manager.addStrategy(strategy_1);
    manager.addStrategy(strategy_2);
    manager.addStrategy(strategy_3);
}

bool strategyTest() {
	std::cout << "Running StrategyManager Test" << std::endl;

	int testCase = -1;
	bool testResult = true;

	StrategyManager strategyManager;
	initStrategies( strategyManager );

	//init test input
	//TC 0
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::_9, CardColor::HEARTS } );
		testState.hand_cards.push_back( { CardType::_9, CardColor::SPADES } );
		testState.comm_cards.push_back( { CardType::_3, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::_5, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_7, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 - 1;

		Action action = strategyManager.execute( testState );

		if( action.mType != ActionType::ALL_IN ) {
			std::cout << "Strategy Test "  << testCase << " failed " << std::endl;
			testResult = false;
		}
	}

	//TC 1
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::_7, CardColor::HEARTS } );
		testState.hand_cards.push_back( { CardType::_7, CardColor::SPADES } );
		testState.comm_cards.push_back( { CardType::_3, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::_5, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_2, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 - 1;

		Action action = strategyManager.execute( testState );

		if( action.mType == ActionType::ALL_IN ) {
			std::cout << "Strategy Test " << testCase << " failed " << std::endl;
			testResult = false;
		}
	}

	//TC 2
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::A, CardColor::HEARTS } );
		testState.hand_cards.push_back( { CardType::A, CardColor::SPADES } );
		testState.comm_cards.push_back( { CardType::_3, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::_5, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_9, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 + 1;

		Action action = strategyManager.execute( testState );

		if( action.mType == ActionType::ALL_IN ) {
			std::cout << "Strategy Test " << testCase << " failed " << std::endl;
			testResult = false;
		}
	}

	//TC 3
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::A, CardColor::HEARTS } );
		testState.hand_cards.push_back( { CardType::Q, CardColor::SPADES } );
		testState.comm_cards.push_back( { CardType::_3, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::_5, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_9, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 - 1;

		Action action = strategyManager.execute( testState );

		if( action.mType != ActionType::ALL_IN ) {
			std::cout << "Strategy Test " << testCase << " failed " << std::endl;
			testResult = false;
		}
	}


	//TC 4
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::A, CardColor::HEARTS } );
		testState.hand_cards.push_back( { CardType::_2, CardColor::SPADES } );
		testState.comm_cards.push_back( { CardType::_3, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::_5, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_9, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 - 1;
		testState.player_num = 3;

		Action action = strategyManager.execute( testState );

		if( action.mType != ActionType::ALL_IN ) {
			std::cout << "Strategy Test " << testCase << " failed " << std::endl;
			testResult = false;
		}
	}

	//TC 5
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::A, CardColor::HEARTS } );
		testState.hand_cards.push_back( { CardType::Q, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_3, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::_5, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_9, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 - 1;

		Action action = strategyManager.execute( testState );

		if( action.mType != ActionType::ALL_IN ) {
			std::cout << "Strategy Test " << testCase << " failed " << std::endl;
			testResult = false;
		}
	}

	//TC 6
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::A, CardColor::HEARTS } );
		testState.hand_cards.push_back( { CardType::_2, CardColor::SPADES } );
		testState.comm_cards.push_back( { CardType::_3, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::_5, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_9, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 - 1;
		testState.player_num = 2;

		Action action = strategyManager.execute( testState );

		if( action.mType != ActionType::NO_ACTION ) {
			std::cout << "Strategy Test " << testCase << " failed " << std::endl;
			testResult = false;
		}
	}

	//TC 7
	{
		testCase++;
		GameState testState;
		testState.hand_cards.push_back( { CardType::_9, CardColor::SPADES } );
		testState.hand_cards.push_back( { CardType::_3, CardColor::SPADES } );
		testState.comm_cards.push_back( { CardType::_2, CardColor::CLUBS } );
		testState.comm_cards.push_back( { CardType::J, CardColor::HEARTS } );
		testState.comm_cards.push_back( { CardType::_7, CardColor::CLUBS } );
		testState.position = PositionType::UTG;
		testState.small_blind = 10;
		testState.stack = testState.small_blind * 15 * 2 - 1;

		Action action = strategyManager.execute( testState );

		if( action.mType != ActionType::NO_ACTION ) {
			std::cout << "Strategy Test " << testCase << " failed " << std::endl;
			testResult = false;
		}
	}

	if( testResult ) {
		std::cout << "StrategyManager Test OK" << std::endl;
	} else {
		std::cout << "StrategyManager Test FAILED" << std::endl;
	}

	return testResult;
}
