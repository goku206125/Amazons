# Amazon game documentation

### Game can be compiled as 
* **Autonomous mode**
	* This compiled version needs commandline arguments to run the code
	* Autonomous mode uses random function to choose and place or move to random location
	* Every message saying like move to: r,c   , means row and column on matrix  (row and column indexes start from 0)
	* outputboard.txt can be checked manually openning, to verify correct program exection
	* ISSUES
	* Firing arrows could not be implemented
	* When the player name is not in the inputbard.txt new player_name is added to ouputboard.txt, but the program terminates, just rerunning the code fixes the issue
	* Movement does not work when inputbard.txt and outputboard.txt are the same
* **Interactive mode**
    * To run interactive mode uncomment line8 in main.c
	* Two players enter their names, inputboard.txt and N number of amazons
	* All moves should be selected based on row, column relation in board matrix (example: 0, 2)
	* Placement phase is held until all amazons are placed
	* During movement phase the score is calculated based on adding matrix cell treasure value
	* Movement pahse is help until any of the players has  no possible moves
	* Output is not saved in any file
	* ISSUES
	* Firing arrows could not be implemented	
### Created by Aayush Gupta.
