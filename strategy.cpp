#include "strategy.h"

bool Condition::evaluate(const GameState& state)
{
    switch(mType)
    {
    case ConditionType::ACTION:
        {
            //
        }
        break;
    case ConditionType::CARDS:
        {
            if (mArguments.size() == 0)
                return false;

            //bool isSuited = false;
            for (int i: mArguments)
            {
                std::vector<CardType> cardSet;
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

            if (state.position == (PositionType)mArguments[0])
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
            {ConditionType::BB_HIGHER, {15}}
        }
    });

//FIRST LINE
	strategy_1.addTrigger({
		{ActionType::ALL_IN}, {
			{ConditionType::POSITION, {PositionType::UTG}},
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

//LAST LINE
    strategy_1.addTrigger({
        {ActionType::ALL_IN}, {
            {ConditionType::CARDS, {
                CardType::K, CardType::K, CardType::SEPARATOR,
            }}
        }
    });

    manager.addStrategy(strategy_1);
}
