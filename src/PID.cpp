#include "PID.h"
#include <math.h>
#include <iostream>

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;
  p_error = 0;
  i_error = 0;
  d_error = 0;
  prev_cte = 0;
  prev_cte_init = false;
}


double PID::SteerAngle(double cte) {
  p_error = cte;
  i_error += cte;
  if (!prev_cte_init) {
    prev_cte_init = true;
    prev_cte = cte;
  }
  d_error = cte - prev_cte;
//  double steer = -Kp * p_error  - Kd * d_error;
  double steer = -Kp * p_error - Ki * i_error - Kd * d_error;
//  steer = fmin(fmax(steer, -1), 1);

//  std::cout << "steer: " << steer << std::endl;
//  std::cout << "p_error: " << cte <<" i_error" << i_error<<" d_error" << d_error << std::endl;
  prev_cte = cte;
  return steer;
}
