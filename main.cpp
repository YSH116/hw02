#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut aout(PA_4);
AnalogIn ain(D11);
DigitalIn down(D6);
DigitalIn sel(D8);
DigitalIn up(D9);
uLCD_4DGL uLCD(D1, D0, D2);
int freq = 0, j, ok; //T = 2000;
float ADCdata[100];

int main() 
{   
    freq = 320; //cut-off freq 1/(2*3.14*(3900+3900)*47*10^-9) = 434.358hz, T = 2.302ms
    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.color(RED);
    uLCD.locate(0,2);
    uLCD.printf("%3dHz", freq);
    while (1) {
        if (sel) ok = 1;
        if (up) {
            freq += 20;
            uLCD.locate(0,2);
            uLCD.printf("%3dHz", freq);
        }
        else if (down) {
            freq -= 20;
            uLCD.locate(0,2);
            uLCD.printf("%3dHz", freq);
        }
        else if (ok) { // generate triangular wave & S = 2
            if (j == 100) j = 0; 
            else if (j <= 20) aout = j/20.0/1.1;                
            else aout = (100-j)/80.0/1.1;
            //T = 1/freq*1000000;
            ADCdata[j++] = ain;
            //wait_us((T-1260)/100);
        }
        /*if (j == 100) {
            for (j = 0; j <= 100; j++) printf("%f\r\n", ADCdata[j]);
        }*/
    }
}
