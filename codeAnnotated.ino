 /* 
 *  This is the starter code for CM10194 System Architecture I Arduino Coursework 1.
 *  You need to extend this code to fufill the coursework specification. 
 *  Couresework specification on Moodle: https://moodle.bath.ac.uk/mod/assign/view.php?id=914187
*/

#include <Servo.h> //installing the servo library

// assign LEDs and button to pins
int ledPin[] = {4,5,6};
int redPin[] = {11,12,13};
int playerOneButton = 2;
int playerTwoButton = 3;
int whiteLED = 9; //LED for a correct score for P1
int orangeLED = 8;//LED for a correct score for P2
int piezoPin = 7; //the pin for the piezo 
int servo = 10;

// declare variables
int randNumber;
int whiteLEDOn; 
int scoreP1 = 0;//store player ones score in this variable
int scoreP2 = 0;//store player twos score in this variable 
int BoolP1 = 0;//Boolean to help the code check whether the button press for player one is correct
int BoolP2 = 0;//Boolean to help the code check whether the button press for player two is correct
Servo myServo;//sets the servo to the name myServo

//setup interrupt, button input and LED outputs
void setup() {
  attachInterrupt(digitalPinToInterrupt(2), checkPlayerOneInput, FALLING); // specify interrupt for when player ones button is pressed
  attachInterrupt(digitalPinToInterrupt(3), checkPlayerTwoInput, FALLING); // interrupt for when player twos button is pressed 
  for (int i=0; i<3; i++){ // loop to assign all player 1 LEDS to the pins
    pinMode(ledPin[i], OUTPUT); // setting the LEDs as an output 
  }
  for (int i=0; i<3; i++){ // loop to assign all player 1 LEDS to the pins
    pinMode(redPin[i], OUTPUT); // setting the LEDs as an output 
  }
  myServo.attach(10); // attaching the servo to pin 10
  pinMode(playerOneButton, INPUT_PULLUP);
  pinMode(playerTwoButton, INPUT_PULLUP);
  pinMode(whiteLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
}

//run main program loop
void loop() {
  while (scoreP1 <10 && scoreP2 < 10){ // while the game has not ended keep the game playing for player one and player two
     playerOneGame(); // runs the game for player one
     playerTwoGame(); //runs the game for player two
     ScoreCompare();  // checks the score 
  }
  if (scoreP1 >= 10){ // if player one has reached the score limit 
    gameOver(scoreP1,scoreP2); //run the game over function passing through both players scores
    }
  else if(scoreP2>=10){ // if player two has reached the score limit 
      gameOver(scoreP1,scoreP2); //run the game over function passing through both players scores
    }
}

void gameOver(int scoreP1, int scoreP2){ // game over function passing both players score as integers
for(int i = 0; i <= 20; i++){ // create a for loop to flash all their LEDs
      delay(50);
      digitalWrite(ledPin[0],HIGH);
      digitalWrite(ledPin[1],HIGH); // lighting up all the LEDs for player one 
      digitalWrite(ledPin[2],HIGH);
      digitalWrite(redPin[0],HIGH);
      digitalWrite(redPin[2],HIGH); // lighting up all the LEDs for player two
      digitalWrite(redPin[1],HIGH);
      delay(50);
      digitalWrite(ledPin[0],LOW);
      digitalWrite(ledPin[1],LOW); // turning the lights off 
      digitalWrite(ledPin[2],LOW);
      digitalWrite(redPin[0],LOW);
      digitalWrite(redPin[2],LOW); // turning off all the LEDs for player two
      digitalWrite(redPin[1],LOW);
      if (scoreP1 >=10){ // if player one has won the game
      digitalWrite(whiteLED,HIGH);//turn player 1 LED on to show they have won the game 
      delay(50);
      digitalWrite(whiteLED,LOW);//turn the LED off
      delay(50);
    }
  
      else if (scoreP2 >=10){ //if player two has won the game 
      digitalWrite(orangeLED,HIGH); //turn player 2 LED on to show they have won the game 
      delay(50);
      digitalWrite(orangeLED,LOW);//turn the LED off
      delay(50);

        }

  }
  scoreP1=0; //resets both players scores
  scoreP2=0;
}


void ScoreCompare(){ // function to compare both plyers score and adjust the servo to point to the winner
  if(scoreP1 > scoreP2){ // if player one is winning
    myServo.write(180);//rotate the servo and arrow by 180 degrees from 90 to the direction of player one
    }
   else if(scoreP1 < scoreP2){ // if player two is winning 
    myServo.write(0);//rotate the servo to 0 degrees from 90 to show that player two is winning 
  }else{// if no one is winnning and the game is tied 
   myServo.write(90); // rotate the servo to 90 degrees to point inbetween the two players
  }
}



void playerOneGame(){ //function for player ones game 
      BoolP1 = 0; // sets the boolean for player one to 0. The boolean is used to see when a button press is incorrect or correct
      randNumber = random(3); // select a random number
      digitalWrite(ledPin[randNumber], HIGH); // light the LED with this number
      int ButtonTime = random(750-1500);//create a random time for the button to be correctly pressed
      long stime = millis();//initialise a variable to store the time starting from 0 milliseconds 
      while (millis() - stime < ButtonTime){ //while the time is less than the button time
        BoolP1 = 1; // set the boolean for player 1 tobe true 
        //this means that a button pressed at this time is a correct button pressed
       
      }
      BoolP1 = 0; // when the time runs out set the boolean back to 0 so any button presses are incorrect 
      digitalWrite(ledPin[randNumber], LOW);//turn the lit LED off
      delay(random(500-2000)); // wait a randome time again before the function is used again in the main loop    
      }
void playerTwoGame(){//function for player twos game
      BoolP2 = 0;// // sets the boolean for player two to 0. The boolean is used to see when a button press is incorrect or correct
      randNumber = random(3); // select a random number
      digitalWrite(redPin[randNumber], HIGH); // light the LED with this number
      int ButtonTime = random(750-1500); //create a random time for the button to be pressed for player two
      long stime = millis();//initialise a variable to store the time starting from 0 milliseconds 
      while (millis() - stime < ButtonTime){//while the time is less than the button time generated any button presses in this time are valid
        BoolP2 = 1; //sets player twos boolean value to 1 so that the button press in this time is a valid button press
      }
      BoolP2 = 0;// when the time runs out set the boolean back to 0 so any button presses are incorrect 
      digitalWrite(redPin[randNumber], LOW);//turn the lit LED off
      delay(random(500-2000));// wait a randome time again before the function is used again in the main loop 
      }


void checkPlayerOneInput(){//the interrupt function for player ones button 
  //the function checks that when the button is pressed for player one at any time it is a correct button press
  if(BoolP1 == 1){//if the boolean value for player one is valid
    playerOneInput();//run the function which shows that the button press was correct
  }else{//if the button press was invalid
    tone(piezoPin,3000,300); //output a sound on the peizo to show that the button press was incorrect
  }
  }     
void playerOneInput() {//function for a correct button press by P1
      BoolP1 = 1;
      digitalWrite(whiteLED, HIGH);//turns P1, LED that indicates a correct button press on
      tone(piezoPin,1000,300);//outputs a unique sound for a correct button press player one on the piezo
      scoreP1 +=1;//increments player ones score by one
      delay(1000);//waits 1000 millisecons 
      digitalWrite(whiteLED, LOW);//then turns the LED off that indicates a correct button is played
  
 }
 
void checkPlayerTwoInput(){//the interrupt function for player twos button 
    //the function checks that when the button is pressed for player two at any time it is a correct button press
  if(BoolP2 == 1){//if the boolean was valid in other words if the button press was valid 
    playerTwoInput(); //run function which shows player twos button press was correct
  }else{//if the button press was invalid
    tone(piezoPin,3000,300); //output a sound on the peizo to show that the button press was incorrect
  }
  } 
void playerTwoInput() {//function for a correct button press by P2
      BoolP2 = 1;
      digitalWrite(orangeLED, HIGH);//turns on the LED that indictaes a score has been scored by player two 
      tone(piezoPin,500,300);//outputs a unique sound for a correct button press player two on the piezo
      scoreP2 +=1;//increments player twos score by one
      delay(1000);//waits a sec to turn the LED off
      digitalWrite(orangeLED, LOW);//then turns the LED off that indicates a correct button is played
   }
  
  /*change this code so that white LED only switches on when button is pressed 
  at the right time*/
