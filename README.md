# CircuitGrid

A step-based electronic simulation.  
Open "CircuitGrid.exe" in the same directory as folder "res".  
Press H for help menu.  

## Items
 - Air (used to remove tiles)
 - Wire (conducts electricity)
 - Output (used to get the output signal from logic-based tiles *[Button/Switch, Logic gates, Clock]* )
 - Battery 
 - Delay (delays signal by its delayvalue & reduces signallength by its delayvalue)
 - Bridge (used to cross wires)
 - Lamp 
 - Button (activate by clicking on it in interaction-mode)
 - Switch (toggle by clicking on it in interaction-mode)
 - NOT, OR, NOR, XOR, XNOR, AND, NAND (Input: up to all 4 surrounding tiles / outputs signal to **OUT** tile)
 - Clock (timervalue in centiseconds; outputs signal with length 1 every cycle)
 - Debug (pauses the simulation if activated)

## Library
SFML for Graphics
##
Demo video playing Bad Apple: https://www.youtube.com/watch?v=16tisvwK9hQ  
Pixel art font by Smoking Drum
