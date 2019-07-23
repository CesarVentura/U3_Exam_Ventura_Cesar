
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

#include <stdio.h>

#define TIME_STEP 64

#define PI 3.1416
#define DIST_OBSTACLE 20.0

int main(int argc, char **argv){
  
 

  int pressed_key;
  float Enco1=0;
  float Enco2=0;
  float Enco3=0;
  float ds_Right1=0;
  float ds_Left2=0;

   //Other variables
   float compare=0;
   float turn_right=0;
   float turn_left=0;
   int w=0;
   int g=1;
   
   wb_robot_init();
   wb_keyboard_enable(TIME_STEP);

   WbDeviceTag wheel_right = wb_robot_get_device("wheel1");
   WbDeviceTag wheel_left = wb_robot_get_device("wheel2");
   WbDeviceTag wheel_back = wb_robot_get_device("wheel3");

   wb_motor_set_position(wheel_right, INFINITY);
   wb_motor_set_position(wheel_left, INFINITY);
   wb_motor_set_position(wheel_back, INFINITY);

   //Encoder devices
   WbDeviceTag Encoder1 = wb_robot_get_device("encoder1");
   WbDeviceTag Encoder2 = wb_robot_get_device("encoder2");
   WbDeviceTag Encoder3 = wb_robot_get_device("encoder3");

   wb_position_sensor_enable(Encoder1, TIME_STEP);
   wb_position_sensor_enable(Encoder2, TIME_STEP);
   wb_position_sensor_enable(Encoder3, TIME_STEP);

   

   //distance sensor devices
   WbDeviceTag dist_sensorR1 = wb_robot_get_device("dist_sensor1");
   WbDeviceTag dist_sensorL2 = wb_robot_get_device("dist_sensor2");

   wb_distance_sensor_enable(dist_sensorR1, TIME_STEP);
   wb_distance_sensor_enable(dist_sensorL2, TIME_STEP);

   

   printf("Left arrow to move linearly to the left\n");
   printf("Right arrow to move linearly to the Right\n");
   printf("UP arrow to move Forward linearly\n");
   printf("DOWN arrow to move Backward linearly\n");
   printf("A key to turn 45° to the left\n");
   printf("S key to turn 45° to the right\n");
   printf("G key to set the automatic mode\n");
   printf("W key to set the manual mode\n");
   
   void manual(){

        ds_Right1 = wb_distance_sensor_get_value(dist_sensorR1);
        ds_Left2 = wb_distance_sensor_get_value(dist_sensorL2);

        Enco1 = wb_position_sensor_get_value(Encoder1);
        Enco2 = wb_position_sensor_get_value(Encoder2);
        Enco3 = wb_position_sensor_get_value(Encoder3);

   



        if(pressed_key == WB_KEYBOARD_UP){
          wb_motor_set_velocity(wheel_left, 5);
          wb_motor_set_velocity(wheel_right, -5);
          wb_motor_set_velocity(wheel_back, 0);
        }
        else if(pressed_key == WB_KEYBOARD_DOWN){
          wb_motor_set_velocity(wheel_left, -5);
          wb_motor_set_velocity(wheel_right, 5);
          wb_motor_set_velocity(wheel_back, 0);
          }
          
        else if(pressed_key == WB_KEYBOARD_LEFT){
          wb_motor_set_velocity(wheel_left, 0);
          wb_motor_set_velocity(wheel_right, -5);
          wb_motor_set_velocity(wheel_back, 5);
         }
         
        else if(pressed_key == WB_KEYBOARD_RIGHT){
          wb_motor_set_velocity(wheel_left, 0);
          wb_motor_set_velocity(wheel_right, 5);
          wb_motor_set_velocity(wheel_back, -5);
          }
          
        else if(pressed_key == 'S' ){
          compare = Enco1 + 0.785398;
          turn_left = 1;
        }

        else if(turn_left == 1){
          if(Enco1 <= compare){
          wb_motor_set_velocity(wheel_left, 5);
          wb_motor_set_velocity(wheel_right,5);
          wb_motor_set_velocity(wheel_back, 5);
          }
        else{
          wb_motor_set_velocity(wheel_left, 0);
          wb_motor_set_velocity(wheel_right, 0);
          wb_motor_set_velocity(wheel_back, 0);
          turn_left = 0;
        }

       }

        else if(pressed_key == 'A' ){
        compare = Enco1 - 0.785398;
        turn_right = 1;
        }
        
        else if(turn_right == 1){
             if(Enco1 >= compare){
          wb_motor_set_velocity(wheel_left, -5);
          wb_motor_set_velocity(wheel_right,-5);
          wb_motor_set_velocity(wheel_back, -5);
             }
        else{
          wb_motor_set_velocity(wheel_left, 0);
          wb_motor_set_velocity(wheel_right, 0);
          wb_motor_set_velocity(wheel_back, 0);
          turn_right = 0;
        }
        } 
        
        else{
          wb_motor_set_velocity(wheel_left, 0);
          wb_motor_set_velocity(wheel_right, 0);
          wb_motor_set_velocity(wheel_back, 0);
        }
   }

  void automatico()
  {

   
    ds_Right1 = wb_distance_sensor_get_value(dist_sensorR1);
    ds_Left2 = wb_distance_sensor_get_value(dist_sensorL2);

    Enco1 = wb_position_sensor_get_value(Encoder1);
    Enco2 = wb_position_sensor_get_value(Encoder2);
    Enco3 = wb_position_sensor_get_value(Encoder3);

    printf("distance_right: %lf\r\n",ds_Right1);
    printf("distance_left: %lf\r\n", ds_Left2);

    printf("Encoder1: %lf\r\n", Enco1);
    printf("Encoder2: %lf\r\n", Enco2);
    printf("Encoder3: %lf\r\n", Enco3);


    wb_motor_set_velocity(wheel_left,  1.66);
    wb_motor_set_velocity(wheel_right, -1.66);
    wb_motor_set_velocity(wheel_back, 0);

    if(ds_Left2 < ds_Right1 && ds_Left2 < 200){

     wb_motor_set_velocity(wheel_left, 1.66);
     wb_motor_set_velocity(wheel_right, 0);
     wb_motor_set_velocity(wheel_back, -1.66);
    }
    else if(ds_Left2 > ds_Right1 && ds_Right1 < 200){
     wb_motor_set_velocity(wheel_left, -1.66);
     wb_motor_set_velocity(wheel_right, 0);
     wb_motor_set_velocity(wheel_back, 1.66);
    }
  }

   wb_motor_set_velocity(wheel_left, 0);
   wb_motor_set_velocity(wheel_right, 0);
   wb_motor_set_velocity(wheel_back, 0);



  while (wb_robot_step(TIME_STEP) != -1) {

  
    pressed_key=wb_keyboard_get_key();
   
     if(pressed_key == 'W')
     {
       w = 1;
       g = 0;
     }
     else if (pressed_key == 'G')
     {
       g = 1;
       w = 0;
     }
 

     if(w == 1)
     manual();

     if(g == 1)
     automatico();
     };

  wb_robot_cleanup();

  return 0;
}