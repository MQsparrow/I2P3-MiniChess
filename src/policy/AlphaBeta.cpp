#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./AlphaBeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int AlphaBeta::alphabeta(State* state, int depth, int alpha, int beta, bool maximizing){
  if (depth == 0 || state->game_state != UNKNOWN) {
    return state->evaluate();
  }

  if (maximizing) {
    int value = INT_MIN;
    for (const auto& action : state->legal_actions) {
      State* ns = state->next_state(action);
      value = std::max(value, alphabeta(ns, depth - 1, alpha, beta, false));
      delete ns;
      alpha = std::max(alpha, value);
      if(alpha >= beta) break; // Beta cutoff
    } return value;
  } else {
    int value = INT_MAX;
    for (const auto& action : state->legal_actions) {
      State* ns = state->next_state(action);
      value = std::min(value, alphabeta(ns, depth - 1, alpha, beta, true));
      delete ns;
      beta = std::min(beta, value);
      if(alpha >= beta) break;  // Alpha cutoff
    } return value;
  }
}

Move AlphaBeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  int ans = 0, cnt = 0;
  int cmp = !state->player?INT_MIN:INT_MAX; 
  for(auto& i: actions){
    auto tmp = state->next_state(i);
    int val = alphabeta(tmp, depth, INT_MIN, INT_MAX, !state->player);
    if(state->player && cmp > val){
        ans = cnt; cmp = val;
    } else if(!state->player && cmp < val){
        ans = cnt; cmp = val;
    } cnt++;
  } return actions[ans];
}