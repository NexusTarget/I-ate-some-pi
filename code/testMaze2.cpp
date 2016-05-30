#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor, int speed);

int main(){

init(0);
	int frontIR; //current reading for each IR sensor
	int leftIR;
  	int rightIR;
  	int frontWall = 550; //threshold for if wall is detected in front of the robot
  	int leftWall = 345; //target distance for wall to left
  	int rightWall = 345; //target distance if wall to right
  	double kp = 0.1;
 	double errorValue = 0;
	int motorSpeed = 50;
	double left; //amount to adjust each motor speed
	double right;
	bool intersection = false;
	bool intersection2 = false;

        while(true){
        	frontIR = read_analog(0); //reads IR sensors and prints to the console
                printf("Front: %d", frontIR);

                leftIR = read_analog(1);
                printf(" Left: %d", leftIR);

                rightIR = read_analog(2);
                printf(" Right: %d\n", rightIR);

                if(frontIR > frontWall){ //if a wall is detected in front of the robot
                        printf("wall in front of robot detected \n");
                        if((rightIR < rightWall) && (leftIR < leftWall)){ //turn right if there is no wall
                                printf("no wall left or right \n");
                                intersection = true;
                	        set_motor(1, -1.5  * motorSpeed); //tune 0.43 - got it from calc$
                                set_motor(2, motorSpeed);
                                
        /*      }else if((rightIR < rightWall) && (leftIR > leftWall){
                        printf("no wall to right \n");
                        set_motor(1, -1 * motorSpeed);
                        set_motor(2, motorSpeed);*/
                }

                //else if(leftIR > leftWall){ //turn left if there is no wall to the left
                 //     printf("no wall to the left of robot \n");
                 //     set_motor(1, motorSpeed);
                 //     set_motor(2, 0.30 * motorSpeed);
                //}else if(rightIR > rightWall){
                 //     printf("no wall right of robot \n");
                 //     set_motor(1, 0.30 * motorSpeed);
                 //     set_motor(2, motorSpeed);
                //}
          }else{ //if there is no wall in front of the robot
                if(intersection){
                	set_motor(1, 0.3* motorSpeed);
                        set_motor(2, motorSpeed)
                        if(rightIR > rightWall){
                        	intersection2 = true;
                        	intersection = false;
                        }
                }
                if(intersection2){
                	set_motor(1, 0.3* motorSpeed);
                        set_motor(2, motorSpeed)
                        if(leftIR > leftWall){
                        	intersection2 = false;
                        }
                }
                        
                	
                errorValue = (leftWall - leftIR)+(rightIR - rightWall); //generate negative error for to$
                                                                        //whether this translates to cor$
                right = motorSpeed - (errorValue * kp); //find motor speeds
                left = motorSpeed + (errorValue * kp);
		set_motor(1, left); //set motor speeds
                set_motor(2, right);
          }
    }

}





