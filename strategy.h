#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"

#include <initializer_list>
#include <vector>
#include <iostream>

class Action
{
public:
	ActionType  mType;
    int         mValue;

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
            mArguments.push_back((int)i);

        if (type == ConditionType::CARDS && mArguments.size() > 0 && mArguments.back() != (int)CardType::SEPARATOR)
            mArguments.push_back((int)CardType::SEPARATOR);

    }

    bool evaluate(const GameState& state);
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
            return Action(ActionType::NO_ACTION);

        for (Strategy i: mStrategies)
        {
            if (i.evaluate(state))
                return i.execute(state);
        }

        return Action(ActionType::NO_ACTION);
    }
};

void initStrategies(StrategyManager& manager);

bool strategyTest();

#endif // STRATEGY_H
