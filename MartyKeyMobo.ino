#include <LEDMenu.h>
#include "MartyKeyboard.h"
#define MENU_DISPLAY 0
#define MENU_CHORD 1
#define MENU_CHORD_MAJ 1
#define MENU_CHORD_MIN 2
#define MENU_CHORD_DIM 3
#define MENU_CHORD_AUG 4
#define MENU_CHORD_7TH 5
#define MENU_CHORD_MAJ7 6
#define MENU_CHORD_MIN7 7
#define MENU_DISCO 2


MartyKeyboard *martykey[8];
LEDMenu menu(0x70, 7, 8, 6);

testing linter

char noteNames[13] = { 'C', 'C', 'D', 'D', 'E', 'F', 'F', 'G', 'G', 'A', 'A', 'B', 'C' };
uint8_t semiTones[5] = { 1, 3, 6, 8, 10 };
char noteName[4];
uint8_t currentNote;
uint8_t chord[8];

void setup() {
  menu.init();
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i++) {

    martykey[i] = new MartyKeyboard(0x20 + i, 4 + i);
  }

  menu.addMenu("DISP");

  menu.addMenu("CHRD");
  menu.addVal("OFF ");
  menu.addVal("MAJ ");
  menu.addVal("MIN ");
  menu.addVal("DIM ");
  menu.addVal("AUG ");
  menu.addVal("7TH ");
  menu.addVal("MAJ7");
  menu.addVal("MIN7");


  menu.addMenu("DSCO");
  menu.addVal("OFF ");
  menu.addVal("ON  ");
}

void loop() {


  for (uint8_t i = 0; i < sizeof(chord); i++) {
    chord[i] = 0;
  }


  menu.poll();

  if (menu.getVal(MENU_CHORD) == MENU_CHORD_MAJ) {
    chord[0] = 4;
    chord[1] = 7;
  } else if (menu.getVal(MENU_CHORD) == MENU_CHORD_MIN) {
    chord[0] = 3;
    chord[1] = 7;
  } else if (menu.getVal(MENU_CHORD) == MENU_CHORD_DIM) {
    chord[0] = 3;
    chord[1] = 6;
  } else if (menu.getVal(MENU_CHORD) == MENU_CHORD_AUG) {
    chord[0] = 4;
    chord[1] = 8;
  } else if (menu.getVal(MENU_CHORD) == MENU_CHORD_7TH) {
    chord[0] = 4;
    chord[1] = 7;
    chord[2] = 10;
  } else if (menu.getVal(MENU_CHORD) == MENU_CHORD_MAJ7) {
    chord[0] = 4;
    chord[1] = 7;
    chord[2] = 11;
  } else if (menu.getVal(MENU_CHORD) == MENU_CHORD_MIN7) {
    chord[0] = 3;
    chord[1] = 7;
    chord[2] = 10;
  }

  for (int i = 0; i < 5; i++) {

    martykey[i]->poll();
    currentNote = martykey[i]->getLatestNote();


    if (menu.getVal(MENU_DISCO) == 1) {
      martykey[i]->setMode(MartyKeyboard::Mode::DISCO, true);
    } else {
      martykey[i]->setMode(MartyKeyboard::Mode::DISCO, false);
    }

    martykey[i]->setChord(chord);



    if (currentNote != 255) {
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

  if (menu.getMenu() == MENU_DISPLAY /* disp */) {
    menu.print(noteName);
  }
}
