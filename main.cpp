#include<iostream>
#include<string>
#include "json.h"
#include "player.h"

using namespace std;

const char* json_test = R"raw({"players":[{"name":"Royal Pityoka","stack":980,"status":"active","bet":20,"version":"Royal Pityoka AI player","id":0},{"name":"Get Shorty","stack":1000,"status":"folded","bet":0,"version":"Default Python folding player, version 2","id":1},{"name":"Articsoka","stack":1000,"status":"folded","bet":0,"version":"Default Java folding player","id":2},{"name":"AllIn","stack":1000,"status":"folded","bet":0,"version":"Starsky","id":3},{"name":"Rounders","stack":990,"status":"active","bet":10,"hole_cards":[{"rank":"5","suit":"diamonds"},{"rank":"9","suit":"clubs"}],"version":"Default C++ folding player","id":4}],"small_blind":10,"orbits":0,"dealer":3,"community_cards":[],"current_buy_in":20,"pot":30,"in_action":4,"minimum_raise":10})raw";

int main(int argc, char* argv[])
{
    if(argc==1){
        cout<< "Running Test" << endl;
        assert(HandEvaluator::selfTest());
        {
            GameState gs;
            assert(Player::fillState(gs, json::Deserialize(json_test)));
        }
        return 0;
    }
    string action = argv[1];
    string game_state_json;
    getline(cin, game_state_json);
    cerr << game_state_json;
    json::Value game_state = json::Deserialize(game_state_json);

    if(action == "bet_request")
    {
        cout << Player::betRequest(game_state);
    }
    else if(action == "showdown")
    {
        Player::showdown(game_state);
    }
    else if(action == "version")
    {
        cout << Player::VERSION;
    }

    return 0;
}
