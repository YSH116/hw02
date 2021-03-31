#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut aout(PA_4);
AnalogIn ain(D11);
DigitalIn down(D5);
DigitalIn sel(D9);
DigitalIn up(D3);
uLCD_4DGL uLCD(D1, D0, D2);

int main() 
{   
    int freq = 50, ratio = 1, i = 1, l = 1, sample_pt = 1, T = 2000, sample = 50;//cut-off freq 1/(2*3.14*(36800+3900)*47*10^-9) = 83.243hz, T = 0.012ms
    float ADCdata[500];
    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.color(RED);
    uLCD.locate(0,2);
    uLCD.printf("%3dHz", freq);
    while (1) {
        if (up) {
            freq += 10;
            uLCD.locate(0,2);
            uLCD.printf("%3dHz", freq);
        }
        if (down) {
            freq -= 10;
            uLCD.locate(0,2);
            uLCD.printf("%3dHz", freq);
        }
        if (sel) { 
            T = 1000000/freq;
            sample = 100*freq/500;
            uLCD.locate(0,2);
            uLCD.printf("%3dHz", freq);
            for (l = 0; l < 500; l++)
                printf("%f\r\n", ADCdata[l]);
        }
        if (ratio == 100) ratio = 0; // generate triangular wave & S = 2 
        if (ratio <= 20) aout = ratio/20.0/1.1;                
        if (ratio > 20) aout = (100-ratio)/80.0/1.1;
        ratio++;
        if (sample_pt >= 500) { // sample 
            sample_pt = 0; 
            i = 0;
        } 
        else if (i % sample == 0) {
            ADCdata[sample_pt] = ain;
            sample_pt++;
        }
        i++;
        wait_us(T/100-10);
    }
}
