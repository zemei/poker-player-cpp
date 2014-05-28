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

            bool isSuited = false;
            for (int i: mArguments)
            {
                std::vector<CardType> cardSet;
                if (i == (int)CardType::SEPARATOR)
                {
                    if (cardSet.size() == 0)
                    {
                        isSuited = false;
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
    }

    return true;
}

void initStrategies(StrategyManager& manager)
{
    Strategy strategy_1({
        {ActionType::FOLD}, {
            {ConditionType::BB_LOWER, {100}}
        }
    });
    /*strategy_1.addTrigger({
		{}, {
			{},
			{}
		}
	});*/
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
    manager.addStrategy(strategy_1);
}
