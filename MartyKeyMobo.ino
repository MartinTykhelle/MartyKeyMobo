#include <LEDMenu.h>
#include "MartyKeyboard.h"
MartyKeyboard *martykey[8];
LEDMenu menu(0x70,7,8,6); 


char noteNames[13] = {'C', 'C', 'D', 'D', 'E', 'F', 'F', 'G', 'G', 'A', 'A', 'B', 'C'};
uint8_t semiTones[5] = {1, 3, 6, 8, 10};
char noteName[4];
uint8_t currentNote;

void setup() {
  menu.init();
  Serial.begin(9600);
  // put your setup code here, to run once:
  for(int i=0;i<5;i++){

  martykey[i] = new MartyKeyboard(0x20+i,4+i);
  }

  menu.addMenu("DISP");
  menu.addMenu("CHRD");
  menu.addVal ("OFF ");
  menu.addVal ("MAJ ");
  menu.addVal ("MIN ");
}

void loop() {
  // put your main code here, to run repeatedly:
    for(int i=0;i<5;i++){

  martykey[i]->poll();
  currentNote = martykey[i]->getLatestNote();
  if(currentNote !=255){
    noteName[0] = noteNames[currentNote % 12];
    noteName[1] = ' '; 
    noteName[2] = ' '; 
    noteName[3] = (char)currentNote / 12 + 48;
    for (int j = 0; j < sizeof(semiTones); j++) {
        if (currentNote % 12 == semiTones[j]) {
          noteName[1] = '#';
        }
      }

  }
  
  }
  menu.poll();
  
  if(menu.getMenu() == 0 /* disp */) {
    menu.print(noteName);
  }
}
