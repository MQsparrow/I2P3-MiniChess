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
  if(!depth || state->game_state != UNKNOWN) return state->evaluate();
  if(maximizing){
    int value = INT_MIN;
    for (const auto& action : state->legal_actions) {
      State* ns = state->next_state(action);
      value = std::max(value, alphabeta(ns, depth - 1, alpha, beta, false));
      alpha = std::max(alpha, value); delete ns;
      if(beta <= alpha) break; // Beta cutoff
    } return value;
  } else{
    int value = INT_MAX;
    for (const auto& action : state->legal_actions) {
      State* ns = state->next_state(action);
      value = std::min(value, alphabeta(ns, depth - 1, alpha, beta, true));
      beta = std::min(beta, value); delete ns;
      if(beta <= alpha) break;  // Alpha cutoff
    } return value;
  }
}

Move AlphaBeta::get_move(State* state, int depth) {
  if(!state->legal_actions.size()) state->get_legal_actions();
  const auto& actions = state->legal_actions;
  int ans = 0, cnt = 0, num = 0;
  for (const auto& i : actions) {
    int alpha = INT_MIN, beta = INT_MAX;
    int cmp = !state->player?INT_MIN:INT_MAX;
    const auto& tmp = state->next_state(i);
    int val = alphabeta(tmp, depth, alpha, beta, state->player);
    if(!state->player){
      if(cmp < val){
        ans = cnt; cmp =  val; num++;
      } alpha = std::max(alpha, cmp);
      if(beta <= alpha) break;
    } else{
      if(cmp > val){
        ans = cnt; cmp =  val; num++;
      } beta = std::min(beta, cmp);
      if(beta <= alpha) break;
    } cnt++; delete tmp;
  } 

  return actions[ans];
}
