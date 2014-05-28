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
                std::vector<int> cardSet;
                if (i == (int)CardType::SEPARATOR)
                {
                    if (cardSet.size() == 0)
                    {
                        isSuited = false;
                        continue;
                    }

                    //bool result = check(cardSet);
                    cardSet.clear();
                }
                else
                {
                    /*if (i == (int)CardType::SUITED)
                        isSuited = true;
                    else*/
                        cardSet.push_back(i);
                }
            }

            return false;
        }
        break;
    case ConditionType::POSITION:
        {
            /*if ()
                return true;*/

            return false;
        }
        break;
    case ConditionType::ROUND:
        {
            /*if ()
                return true;*/

            return false;
        }
        break;
    }

    return true;
}

void initStrategies(StrategyManager manager)
{
    Strategy strategy_1({
        {ActionType::FOLD}, {
            {ConditionType::BB_LOWER, {100}}
        }
    });
    /*strategy_1.addTrigger({

    });*/
    manager.addStrategy(strategy_1);
}
