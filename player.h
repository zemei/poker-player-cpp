#include "json.h"

class Player
{
    public:
        static int betRequest(json::Value game_state);

        static void showdown(json::Value game_state);
};
