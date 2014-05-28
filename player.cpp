#include "player.h"
//Continous delivery poker

const char* Player::VERSION = "Default C++ folding player";

struct GameState {
    int small_blind;
    int stack;
    bool has_A;
};


//////////////////////////////////
//START of Code section for Laja


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
int Player::betRequest(json::Value game_state)
{
    GameState gs;
    gs.small_blind = game_state["small_blind"].ToInt();

    json::Value me = game_state["players"][game_state["in_action"].ToInt()];
    gs.stack = me["stack"];

    gs.has_A = me["hand"]["hole_cards"].ToArray()[0]["rank"].ToString() == "A" || me["hand"]["hole_cards"].ToArray()[1]["rank"].ToString() == "A";

    return gs.has_A ? 1000 : 0;
}

void Player::showdown(json::Value game_state)
{
}
//END of Code section for Tibi
//////////////////////////////////
