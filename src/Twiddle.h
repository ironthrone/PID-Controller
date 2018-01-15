//
// Created by ironthrone on 18-1-7.
//

#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <uWS/uWS.h>
#include "PID.h"
#include <climits>

class Twiddle {
  public:
  PID pid;
  double p[3] = {0,0,0};
  double best_p[3] = {0,0,0};
  // dp_i can collide to 0.2
  double dp[3] = {0.5,0.1,0.5};
  double best_err = INT_MAX;
  bool best_err_init = false;
  int N = 400;
  int n = 0;
  double total_err_of_current_params = 0;
  bool go_down = false;
  int param_index_of_current_twiddle = 0;
  double threshold = 0.001;
  int iterate_count = 0;
  uWS::WebSocket<uWS::SERVER> ws;

  Twiddle();


  /**
   * calculate steer angle , and statistic iteration and err
   */
  double SteerAngle(double cte);

  /**
   * is time to update params, and it is time to reset the simulator
   */
  void ToUpdateParams();

  double DpSum();

  /**
   * update params
   */
  void UpdateParams();

  void Restart();
};

#endif //TWIDDLE_H
