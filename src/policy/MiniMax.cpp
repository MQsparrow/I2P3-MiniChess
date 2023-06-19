#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./MiniMax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int MiniMax::minimax(State *state, int depth, bool maximizing){
    if (depth == 0 || state->game_state != UNKNOWN) {
    return state->evaluate();
  }

  int ans;
  if(maximizing){
    ans = INT_MIN;
    for (const auto& i: state->legal_actions){
      State* ns = state->next_state(i);
      ans = std::max(ans, minimax(ns, depth - 1, false));
      delete ns;
    }
  } else{
    ans = INT_MAX;
    for (const auto& action : state->legal_actions) {
      State* ns = state->next_state(action);
      ans = std::min(ans, minimax(ns, depth - 1, true));
      delete ns;
    }
  }

  return ans;
}

Move MiniMax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  int ans = 0, cnt = 0;
  int cmp = !state->player?INT_MIN:INT_MAX; 
  for(auto& i: actions){
    auto tmp = state->next_state(i);
    int val = minimax(tmp, depth, !state->player);
    if(state->player && cmp > val){
        ans = cnt; cmp =  val;
    } else if(!state->player && cmp < val){
        ans = cnt; cmp =  val;
    } cnt++;
  }

  return actions[ans];
}