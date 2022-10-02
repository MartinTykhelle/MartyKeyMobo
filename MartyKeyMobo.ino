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

  menu.addMenu("DISP");//0
  menu.addMenu("CHRD");//1
  menu.addVal ("OFF ");
  menu.addVal ("MAJ ");
  menu.addVal ("MIN ");
  
  menu.addMenu("DSCO");//2
  menu.addVal ("OFF ");
  menu.addVal ("ON  ");
  
}

void loop() {
  
  menu.poll();
    for(int i=0;i<5;i++){

  martykey[i]->poll();
  currentNote = martykey[i]->getLatestNote();
  
  if(menu.getVal(2) == 1){
    martykey[i]->setMode(MartyKeyboard::Mode::DISCO,true);
  }
  else{
    martykey[i]->setMode(MartyKeyboard::Mode::DISCO,false);
  }

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
  
  if(menu.getMenu() == 0 /* disp */) {
    menu.print(noteName);
  }


}
