### How P I D impacts the controller independently

* P is for Proportional, is proportional to current cte .cte = desire - measure,in this project ,it is the distance from the car to the road's middle line.  With a proper P parameter, our car can modify steer angle according to current cte, If the cte is great,p error is great. But this is not enough,because it requires an error to generate the proportional response,if there is no error ,no response will be created. 
* D is for "Derivetive", is based on current cte change rate. I see this change as a future trend of cte. we use this paramter to prevent cte  increas in the next steps.Thus the cte's ossilation can become smaller and smaller
* I is for "Integral", it accounts for the past errors.Because system may have bias ,for example the camera's position,car steering control, these bias make system at a constant distance from the desire result. So i error accounts for past errors, and provide a compensation to it.

## Tune the parameter
The PID is easy to implement, but the tune is time consumed.  I got the final result by   manual tunning.

I diceded to tune the PID controller by twiddle only at first, but the car can run out of road easily after parameters cahnged by twiddle,then the car just hung on, and it is a waste time. So i decide to tune manully.The first step is to understand these variables , i played these paramters freely, and then i understand:
1. throttle controls the car's mas speed, if the car runs too fast,i can decide to decrease it
2. Kd controls car's response to cte change rate. when car run through a curve, the cte maybe very low, but cte change rate increase.so if car runs out of a curve ,i need to tune Kd
3. Ki accounts for historical error. when car runs away the middle line for a long time ,i should tune Ki.But Ki can not too great, because i error is a accumulated value.

Then i make all paramters to zero,throttle to 0.2, and begin to tune these parameters:
1. Tune Kp until the car can run to bridge successfully,i got value 0.05
2. Tune Kd to make car runs more smoother and run through these curves. I got value Kd = 1
3. Then i add Kp to 0.1,because the car's response to current cte is slow
4. Then Tune Ki value to make the car run through curve more smoother because the car run away middle line for many step when running through curves.I got Ki = 0.005
5. Now my car can run successfully,but i want to make to faster , so i increase throttle and use the same thue approach to tune the three paramters to make them fit on a higher speed .
6. Finally i got the result : Kp = 0.1,Ki = 0.0008,Kd = 0.9,at throttle = 0.4,it runs safer at throttle = 0.3

I dont konw if manual method is stupid ,but i got my result.And of course there are many aspects that i can do to make the PID better, such as:
1.decrease throttle when cte is large and speed is high
2.set parameters for different speed
3.practice a more realiable auto tune approach