# Arkanoid-controller
E' un eperimento per avere un controller a rotazione per il gioco arcade Arkanoid. 
Per realizzarlo uso un  Arduino Leonardo e un Rotary Encoder KY-040
Il Rotary Encoder era nel kit Lafvin.
Nota che l'Aurduino Nano non può essere usato come mouse inquanto la libreria <mouse.h> non 
funziona.

## Collegamenti:
5 fili:

* Controller GND al pin gnd del Leonardo
* Controller + al pin 5V del Leonardo
* Controller SW al pin D4 del Leonardo
* Controller DT al pin D3 del Leonardo
* Controller CLK al pin D2 del Leonardo

![Schema](/images/wire.jpg)

## Software
Sono partito dall'esempio di Lafvin che però usa il rotary per controllare un motore.
Interessante la parte che legge il verso della rotazione attraverso un interrupt.
Il senso della rotazione CW (orario) o A-CW (antioraria) si ha con il controller
posizionato con i fili in alto
