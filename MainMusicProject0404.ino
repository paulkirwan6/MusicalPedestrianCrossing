#include <notes.h>

//defining the pins
const int trigPin = 9;
const int echoPin = 10;

const int trigPin2 = 11;
const int echoPin2 = 12;

//defining variables
//variables here will exist outside the loop, and the values can be used in future loops without being reset
long duration;
#define buffersize 10
int filteredDistance, distance, filteredDistance2, distance2, buffer[buffersize], count = 0, value, t = 0;
int lastFilteredValue, lastFilteredValue2;
int currentSpeed1; int currentSpeed2;

// notes in the jaw theme
int melody[] = {
  NOTE_E4, NOTE_F4
};

// stopped at crossing
int cross[] = {
  NOTE_A1
};

// passed crossing
int passed[] = {
  NOTE_A7
};

//notes in the theme where the car passes the crossing (can be changed later)
int melodyVictory[] =
{
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F6, END
};

int noteDurationCross[] = {
  4
};

// note durations: 8 = quarter note, 4 = 8th note, etc.
//there are as many numbers in these as there are notes to play
int noteDurations[] = {
  4, 2
};

//the notes are given higher values when the song will play slower
int noteDurations2[] =
{
  4, 2
};

int noteDurations3[] =
{
  8, 4
};

int noteDurations4[] =
{
  16, 8
};

int noteDurationsVictory [] =
{
  2, 2, 2, 2
};

int speed = 90;

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the 2nd trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the 2nd echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop()
{
  //gets 10 values at the beggining of every loop to fill the buffer
  for (int i = 0; i <= 10; i++)
  {
    //accesses the 2 pins connected to the sensor, and puts these into the distance function
    distance = getDistance(9, 10);
    //filters these values to get the lowest
    filteredDistance = filter(distance);
  }
  for (int i = 0; i <= 10; i++)
  {
    distance2 = getDistance(11, 12);
    filteredDistance2 = filter(distance2);
  }
    currentSpeed1 = lastFilteredValue - filteredDistance;
    currentSpeed2 = lastFilteredValue2 - filteredDistance2;
  Serial.print("Distance: ");
  Serial.println(filteredDistance);
  Serial.print("                               Distance2: ");
  Serial.println(filteredDistance2);

  //when car has passed crossing
  if (filteredDistance < 25 && filteredDistance > 20 && filteredDistance2 < 25 && filteredDistance2 >20|| filteredDistance < 25 && filteredDistance >20 && filteredDistance2 > 55|| filteredDistance > 55 && filteredDistance2 < 25 && filteredDistance2 > 20 || (filteredDistance > 20 && filteredDistance < 25 && filteredDistance2 < 25) || (filteredDistance2 > 20 && filteredDistance2 < 25 && filteredDistance < 25 ) )
  {
    for (int thisNote = 0; melodyVictory[thisNote] != -1; thisNote++)
    {
      int noteDuration = speed * noteDurationsVictory[thisNote];
      tone(3, melodyVictory[thisNote], noteDuration * .95);
      Serial.println(melodyVictory[thisNote]);
      delay(noteDuration);
      noTone(3);
    }
  }

  //when car 1 is at the crossing and car 2 is at the crossing, off the track, or passed the crossing
  else if ((filteredDistance <= 32 && filteredDistance >= 25 && filteredDistance == lastFilteredValue) && ((filteredDistance2 <= 32 && filteredDistance2 >= 25) || filteredDistance2 >= 55 || filteredDistance2 <= 25))
  {
    delay(500);
    if (lastFilteredValue == filteredDistance)
    {
      for (int thisNote = 0; cross[thisNote] != -1; thisNote++)
      {
        int noteDuration = speed * noteDurationCross[thisNote];
        tone(3, cross[thisNote], noteDuration * .95);
        Serial.println(cross[thisNote]);
        delay(noteDuration);
        noTone(3);
      }
    }
  }

  //when car 2 is at the crossing and car 1 is at the crossing, off the track, or passed the crossing
  else if ((filteredDistance2 <= 32 && filteredDistance2 >= 25 && filteredDistance2 == lastFilteredValue2))
  {
    delay(500);
    if (lastFilteredValue2 == filteredDistance2)
    {
      for (int thisNote = 0; cross[thisNote] != -1; thisNote++)
      {
        int noteDuration = speed * noteDurationCross[thisNote];
        tone(3, NOTE_A1 , noteDuration * .95);
        Serial.println(cross[thisNote]);
        delay(noteDuration);
        noTone(3);
      }
    }
  }
  
  //then cycles through every distance range from closest to farthest
  else if (filteredDistance >= 33 && filteredDistance <= 40 || filteredDistance2 >= 33 && filteredDistance2 <= 40)
  {
    for (int thisNote = 0; melody[thisNote] != -1; thisNote++)
    {
      int noteDuration = speed * noteDurations2[thisNote];
      tone(3, melody[thisNote], noteDuration * .95);
      Serial.println(melody[thisNote]);
      delay(noteDuration);
      noTone(3);
    }
  }
  
  else if (filteredDistance >= 41 && filteredDistance <= 50 || filteredDistance2 >= 41 && filteredDistance2 <= 50) {
    for (int thisNote = 0; melody[thisNote] != -1; thisNote++)
    {
      int noteDuration = speed * noteDurations3[thisNote];
      tone(3, melody[thisNote], noteDuration * .95);
      Serial.println(melody[thisNote]);
      delay(noteDuration);
      noTone(6);
    }
  }
  
  else if (filteredDistance >= 51  && filteredDistance <= 57 || filteredDistance2 >= 51  && filteredDistance2 <= 57)
  {
    for (int thisNote = 0; melody[thisNote] != -1; thisNote++)
    {
      int noteDuration = speed * noteDurations4[thisNote];
      tone(3, melody[thisNote], noteDuration * .95);
      Serial.println(melody[thisNote]);
      delay(noteDuration);

      noTone(3);
    }
  }
   
  else if(filteredDistance2 > 60 && filteredDistance2 < 200 || filteredDistance  > 60 && filteredDistance < 200)
  {
    if(filteredDistance2 > 60 && filteredDistance2 < 200 && filteredDistance >60)
    {
      int playNote = ChooseNote(currentSpeed1);
      Serial.println(playNote);
      tone(3, playNote, 500);
      delay(500);
      noTone(3); 
    }
    if(filteredDistance  > 60 && filteredDistance < 200 && filteredDistance2 > 60)
    {
      int playNote2 = ChooseNote(currentSpeed2);
      Serial.println(playNote2);
      tone(3, playNote2, 500);
      delay(500);
      noTone(3);
    }
  }

  else
  {
     noTone(3);
  }
  //now the current distance becomes old distance for the next loop's comparisons
  lastFilteredValue = filteredDistance;
  lastFilteredValue2 = filteredDistance2;
  filteredDistance = 0;
  filteredDistance2 = 0;
}


//function to get the distance in cms
int getDistance (int trig, int echo)
{
  // Clears the trigPin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  //then sets it low again
  digitalWrite(trig, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);

  // Calculates the distance in centimeters
  distance = duration * 0.034 / 2;

  return distance;
}

//the function that filters 10 values into 1 to get the most accurate reading and ignore random spikes from the readings
int filter(int value)
{
  boolean swapped = true;
  int temp, j = 0;
  int filteredBuffer[buffersize] = {};
  for (int i = 0; i <= buffersize - 2; i++)
  {
    buffer[i] = buffer[i + 1];
  }

  buffer[buffersize - 1] = value;

  //Until the buffer is full, return raw data
  if (count < buffersize)
  {
    count++;
    return value;
  }
  else //Buffer has been filled, apply filter
  {
    for (int i = 0; i < buffersize; i++)
    {
      filteredBuffer[i] = buffer[i];
    }
  }

  //Sort the buffer in ascending order
  while (swapped)
  {
    swapped = false;
    j++;
    for (int i = 0; i < (buffersize - 1) - j; i++)
    {
      if (filteredBuffer[i] > filteredBuffer[i + 1])
      {
        temp = filteredBuffer[i];
        filteredBuffer[i] = filteredBuffer[i + 1];
        filteredBuffer[i + 1] = temp;
        swapped = true;
      }
    }
  }
  
  //Return the lowest value in the buffer
  return filteredBuffer[0];
}

int ChooseNote(int speedNote)
{
  switch(speedNote)
  {
  case 0:
  return 0;
  case 1:
  return NOTE_C3;
  case 2:
  return NOTE_D3;
  case 3:
  return NOTE_E3;
  case 4:
  return NOTE_F3;
  case 5:
  return NOTE_G3;
  case 6:
  return NOTE_A3;
  case 7:
  return NOTE_B5;
  case 8:
  return NOTE_C5;
  case 9:
  return NOTE_D5;
  case 10:
  return NOTE_E5;
  case 11:
  return NOTE_F5;
  case 12:
  return NOTE_G5;
  case 13:
  return NOTE_A5;
  case 14:
  return NOTE_B6;
  case 15:
  return NOTE_C6;
  case 16:
  return NOTE_D6;
  case 17:
  return NOTE_E6;
  case 18:
  return NOTE_F6;
  case 19:
  return NOTE_G6;
  case 20:
  return NOTE_A6;
  case 21:
  return NOTE_B7;
  case 22:
  return NOTE_C7;
  case 23:
  return NOTE_D7;
  case 24:
  return NOTE_E7;
  case 25:
  return NOTE_F7;
  case 26:
  return NOTE_G7;
  case 27:
  return NOTE_A7;
  default:
  return 0;
  }
}
