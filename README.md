# lab4-game-skeleton

Functions are divided into libraries, though I did not create any classes. I created individual files for these libraries so I wouldn't have to scroll through hundreds (thousands?) of lines of code and could instead flip through the tabs. 

main.c has the main code and start up functions
ball.h/ball.c contain the code that determines and updates the location of the ball
buzzer.h/buzzer.c contain the code that determines the frequency for the buzzer (LOW_NOTE and HIGH_NOTE ended up being the same frequency but vary in duration)
paddles.h/paddles.c contain the code that intereprets the value in the ADC to update the players paddle as well as using the position of the ball to update the CPU paddle
scoring.h/scoring.c contain the code that updates the score text, announces the winner, and performs a software reset to begin a new game

The NodeMCU is activated when a certain pin is turned high and the joystick is activated when the same pin is turned low. This way the code does not have to be changed and there is only one wire that needs to be moved in the hardware

I spent a lot of time making sure the ball (a square to simplify this part) really touches the top, bottom, paddles, and sides no matter what speed it goes. I used interpolation of the current position in an attempt to make it look more realistic. I will admit that sometimes it does and sometimes it doesn't.

It is also worth noting that even though the ball passes over the dotted center line and the score that neither of these are visually interrupted
