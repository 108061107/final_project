#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include <iostream>
#include <cmath>

using namespace std;

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial pc(STDIO_UART_TX, STDIO_UART_RX);
BufferedSerial xbee(D1, D0);
DigitalInOut pin11(D11);
BufferedSerial openmv_uart(D10,D9); // tx, rx


BBCar car(pin5, pin6, servo_ticker);

void follow_line();

int main(){
    pc.set_baud(9600);
    xbee.set_baud(9600);
    openmv_uart.set_baud(9600);

    char data[30];
    char recv[1];
    int first_time = 1;
    while(1){
        if (openmv_uart.readable()){
            openmv_uart.read(recv, sizeof(recv));
            if (recv[0] == 'y') {
                if (first_time == 1) {
                    char buffer0[22];
                    sprintf(buffer0, "Start follow line...\r\n");
                    xbee.write(buffer0, sizeof(buffer0));
                    first_time = 0;
                }
                follow_line();
            }
            else {
                car.stop();
                char buffer1[13];
                sprintf(buffer1, "Line ended.\r\n");
                xbee.write(buffer1, sizeof(buffer1));
                data[0] = recv[0];
                for (int j = 1; j < 30; ) {
                    if (openmv_uart.readable()){
                        openmv_uart.read(recv, sizeof(recv));
                        data[j] = recv[0];
                        j++;
                    }
                }
                break;
            }
        }
    }
    /*
    for (int i = 0; i < 30; i++) printf("%c", data[i]);
    printf("\n");
    char buffer2[32];
    sprintf(buffer2, "%s\r\n", data);
    xbee.write(buffer2, sizeof(buffer2));
    */

    float data_tx_R = (data[5]-'0') + (data[7]-'0')/10.0 + (data[8]-'0')/100.0 + (data[9]-'0')/1000.0;    // 3.177
    float data_tz_R = (data[16]-'0')*10.0 + (data[17]-'0') + (data[19]-'0')/10.0 + (data[20]-'0')/100.0 + (data[21]-'0')/1000.0;
    float data_tx_L = (data[6]-'0') + (data[8]-'0')/10.0 + (data[9]-'0')/100.0 + (data[10]-'0')/1000.0;
    float data_tz_L = (data[17]-'0')*10.0 + (data[18]-'0') + (data[20]-'0')/10.0 + (data[21]-'0')/100.0 + (data[22]-'0')/1000.0;
    float angle_R = atan(data_tx_R/data_tz_R);
    float angle_L = atan(data_tx_L/data_tz_L);
    float side_R = sqrt(data_tx_R*data_tx_R+data_tz_R*data_tz_R);
    float side_L = sqrt(data_tx_L*data_tx_L+data_tz_L*data_tz_L);
    float distance_R = side_R*sin(angle_R)*6.2;
    float distance_L = side_L*sin(angle_L)*6.2;
    float distance_z_R = data_tz_R*6.2;
    float distance_z_L = data_tz_L*6.2;
    float speed = 19.5;

    wait_us(2000000);

    if (data[0] == 'R') {
        char buffer3[20];
        sprintf(buffer3, "Apriltag detected.\r\n");
        xbee.write(buffer3, sizeof(buffer3));

        char buffer4[74];
        sprintf(buffer4, "BBCar position: %.1fcm far away, %.1fcm displacement on the right side.\r\n", distance_z_R, distance_R/3);
        xbee.write(buffer4, sizeof(buffer4));

        char buffer5[31];
        sprintf(buffer5, "Start position calibration...\r\n");
        xbee.write(buffer5, sizeof(buffer5));

        // printf("%f %f\n", data_tx_R, data_tz_R);
        car.turn(-200, -0.1);
        ThisThread::sleep_for(1200ms);
        car.goStraight(-200);
        wait_us(1000*distance_R/speed*1000);
        car.turn(200, -0.1);
        ThisThread::sleep_for(800ms);
        car.stop();
        ThisThread::sleep_for(2s);
    }
    else if (data[0] == 'L') {
        char buffer3[20];
        sprintf(buffer3, "Apriltag detected.\r\n");
        xbee.write(buffer3, sizeof(buffer3));

        char buffer4[73];
        sprintf(buffer4, "BBCar position: %.1fcm far away, %.1fcm displacement on the left side.\r\n", distance_z_L, distance_L/3);
        xbee.write(buffer4, sizeof(buffer4));

        char buffer5[31];
        sprintf(buffer5, "Start position calibration...\r\n");
        xbee.write(buffer5, sizeof(buffer5));

        // printf("%f %f\n", data_tx_L, data_tz_L);
        car.turn(120, -0.1);
        ThisThread::sleep_for(1050ms);
        car.goStraight(-200);
        wait_us(850*distance_L/speed*1000);
        car.turn(-100, -0.1);
        ThisThread::sleep_for(1800ms);
        car.stop();
        ThisThread::sleep_for(2s);
    }

    char buffer6[20];
    sprintf(buffer6, "Calibration ended.\r\n");
    xbee.write(buffer6, sizeof(buffer6));

    char buffer7[20];
    sprintf(buffer7, "Go to destination.\r\n");
    xbee.write(buffer7, sizeof(buffer7));

    parallax_ping ping(pin11);
    while(float(ping) > 30) {
        char buffer[13];
        printf("Ping = %.1f\n", float(ping));
        sprintf(buffer, "Ping = %.1f\r\n", float(ping));
        xbee.write(buffer, sizeof(buffer));
        car.goStraight(-200);
        ThisThread::sleep_for(300ms);
    }
    car.stop();
    char buffer8[38];
    sprintf(buffer8, "Within 30cm, destination arrived.\r\n\n\n\n");
    xbee.write(buffer8, sizeof(buffer8));

    
}

void follow_line() {
    car.goStraight(-200);
}