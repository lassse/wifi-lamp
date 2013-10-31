#include <Process.h>
#include <Servo.h> 


Servo motor;
int motorTicker = 0;
int motorTime = 80;

boolean useWifi = true;

int wifiCheck = 20;
int wifiCurrent = 0;

int current = 0;
int signal = 0;

Process p;


void setup() {
    Bridge.begin();
    Serial.begin(9600);
    motor.attach(11);
}

void loop() {
    
    if (useWifi) {
        if (wifiCurrent < wifiCheck) {
            wifiCurrent++;
        }else{
            p.runShellCommand("/usr/bin/pretty-wifi-info.lua | grep Signal"); 
            while(p.running());  
            while (p.available()){ 
                int result = p.parseInt();
                if (result != 0) {
                    signal = map(result, 50, 70, 0, 4);
    
                    Serial.println("  ");  
                    Serial.println("------------------------");  
                    Serial.print("Mapped signal strength: ");  
                    Serial.println(signal);    
                }
            }
    
            wifiCurrent = 0; 
        }
    }else{
        signal = 3;
    }
    
    if (motorTicker > motorTime) {
        motor.write(110);
        motorTicker = 0;        
    }else{
        motor.write(94);
        motorTicker++;   
    }    

    delay(30);

}


