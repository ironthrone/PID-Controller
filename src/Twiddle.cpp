//
// Created by ironthrone on 18-1-7.
//

#include "PID.h"
#include "Twiddle.h"
#include <cmath>
#include <iostream>

Twiddle::Twiddle() {
  pid.Init(p[0], p[1], p[2]);
}


double Twiddle::SteerAngle(double cte) {
//  if (std::abs(cte) > 2.5) {
//    total_err_of_current_params = best_err ;
//    ToUpdateParams();
//    return 0;
//  }
  double steer = pid.SteerAngle(cte);
  if (n >= 100) {
    total_err_of_current_params += cte * cte;
  }
  n++;
  if (n >= N) {
    ToUpdateParams();
  }
  return steer;
}

void Twiddle::ToUpdateParams() {
  //update params,begin next twiddle
  if (DpSum() < threshold) {
    std::cout << "twiddle end , ite count: " << iterate_count << " best err is " << best_err << std::endl;
  } else {
    UpdateParams();
  }
}

void Twiddle::UpdateParams() {
  if (n == 0) {
    return;
  }
  iterate_count++;
  if (!best_err_init) {
    best_err = total_err_of_current_params;
    best_p[0] = p[0];
    best_p[1] = p[1];
    best_p[2] = p[2];
    pid.Init(p[0], p[1], p[2]);

    p[param_index_of_current_twiddle] += dp[param_index_of_current_twiddle];
    best_err_init = true;
    Restart();
    return;
  }

  if (!go_down) {
    if (total_err_of_current_params < best_err) {
      best_err = total_err_of_current_params;
      best_p[0] = p[0];
      best_p[1] = p[1];
      best_p[2] = p[2];
//      std::cout << "\nbest err: " << best_err << "\n" << std::endl;
      dp[param_index_of_current_twiddle] *= 1.1;
      param_index_of_current_twiddle = (param_index_of_current_twiddle + 1) % 3;
      p[param_index_of_current_twiddle] += dp[param_index_of_current_twiddle];
      pid.Init(p[0], p[1], p[2]);

    } else {
      p[param_index_of_current_twiddle] -= 2 * dp[param_index_of_current_twiddle];
      pid.Init(p[0], p[1], p[2]);

      go_down = true;
    }
  } else {
    if (total_err_of_current_params < best_err) {
      best_err = total_err_of_current_params;
      best_p[0] = p[0];
      best_p[1] = p[1];
      best_p[2] = p[2];
//      std::cout << "\nbest err: " << best_err << "\n" << std::endl;
      dp[param_index_of_current_twiddle] *= 1.1;

    } else {
      p[param_index_of_current_twiddle] += dp[param_index_of_current_twiddle];
      dp[param_index_of_current_twiddle] *= 0.9;
    }
    param_index_of_current_twiddle = (param_index_of_current_twiddle + 1) % 3;
    p[param_index_of_current_twiddle] += dp[param_index_of_current_twiddle];
    pid.Init(p[0], p[1], p[2]);

    go_down = false;
  }

  std::cout << "\n";
  std::cout << "best_err: " << best_err << std::endl;
  std::cout << "best_err parameters: [" << " " << best_p[0] << " " << best_p[1] << " " << best_p[2] << "]\n";
  //TODO log position move to begin
  std::cout << "err: " << total_err_of_current_params << std::endl;
  std::cout << "dp: " << dp[0] << " " << dp[1] << " " << dp[2] << std::endl;
  std::cout << "Kp: " << p[0] << " Ki: " << p[1] << " Kd: " << p[2] << std::endl;
  std::cout << "\n" << std::endl;
  Restart();
}

double Twiddle::DpSum() {
  return dp[0] + dp[1] + dp[2];
}

void Twiddle::Restart() {
  n = 0;
  total_err_of_current_params = 0;
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

