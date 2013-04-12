#include "mbed.h"

#define BPM 72  // global beats per minute
DigitalOut keys[] = { (p5) };  // output pins, 1 for each key
Timeout universal;  // universal timer - counts down after each note to next note

typedef struct mynote {
    int *value;  // pointer to list of values (1 to 13)
    float length;  // time (s) until next note
    mynote* next;  // pointer to next note
} Note;

Note* currentnote;  // pointer to current note

void play()  {
    // turn on keys
    keys[currentnote->value[0] - 1] = 1;
    wait_ms(100);
    // turn off
    keys[currentnote->value[0] - 1] = 0;
}

// play next note
void playnext()  {
    // get next note
    Note* temp = currentnote;
    currentnote = currentnote->next;
    
    // dispose of current one
    free(temp->value);
    free(temp);
    
    // play next note
    if (currentnote)  {
        play();
        universal.attach(&playnext, currentnote->length);
    }
}



Note* setnote(int numnotes, int notes[], int lengthn, int lengthd)  {
    Note* temp = (Note*)malloc(sizeof(Note));
    temp->value = (int*)malloc(sizeof(int) * numnotes);
    for (int i=0; i<numnotes; ++i)
        temp->value[i] = notes[i];
    temp->length = (float)lengthn/lengthd / BPM * 60;
    temp->next = NULL;
    
    return temp;
}



int main() {
    // turn all keys off?
    // for ()
    keys[0] = 0;

    // load notes into memory
    /*
    currentnote = (Note*)malloc(sizeof(Note));
    currentnote->value = (int*)malloc(sizeof(int) * 1);
    currentnote->value[0] = 1;
    currentnote->length = 1.0 / BPM * 60;
    
    Note* temp = (Note*)malloc(sizeof(Note));
    temp->value = (int*)malloc(sizeof(int) * 1);
    temp->value[0] = 1;
    temp->length = 1.0 / BPM * 60;
    currentnote->next = temp;
    temp->next = NULL;
    */
    int notes[] = {1};
    currentnote = setnote(1, notes, 1, 4);
    Note* temp = setnote(1, notes, 1, 4);
    currentnote->next = temp;
    temp->next = setnote(1, notes, 1, 2);
    temp->next->next = setnote(1, notes, 1, 4);

    // ready to play
    if (currentnote)  {
        play();
        universal.attach(&playnext, currentnote->length);
    }
    
    while(1);
}
