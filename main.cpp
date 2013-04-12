#include "mbed.h"

#define BPM 100  // global beats per minute
DigitalOut keys[] = { (p5), (p6), (p7), (p8), (p9), (p10), (p11), (p12), (p13), (p14), (p15), (p16), (p17) };  // output pins, 1 for each key
Timeout universal;  // universal timer - counts down after each note to next note

typedef struct mynote {
    int n;   // number of notes
    int *value;  // pointer to list of values (1 to 13)
    float length;  // time (s) until next note
    mynote* next;  // pointer to next note
} Note;

Note* currentnote;  // pointer to current note

void play()  {
    // turn on keys
    for (int i=0; i < currentnote->n; ++i)
        keys[currentnote->value[i] - 1] = 1;
    wait_ms(50);
    // turn off
    for (int i=0; i < currentnote->n; ++i)
        keys[currentnote->value[i] - 1] = 0;
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
    temp->n = numnotes;
    temp->value = (int*)malloc(sizeof(int) * numnotes);
    for (int i=0; i<numnotes; ++i)
        temp->value[i] = notes[i];
    temp->length = (float)lengthn/lengthd / BPM * 60;
    temp->next = NULL;
    
    return temp;
}



int main() {
    // turn all keys off?
    for (int i=0; i<13; ++i)
        keys[i] = 0;

    // load notes into memory
  
    int E[] = {1};
    int F[] = {2};
    Note* temp1;
    Note* temp2;
    
    currentnote = setnote(1, E, 1, 4);
    currentnote->next = temp1 = setnote(1, E, 1, 4);
    temp1->next = temp2 = setnote(1, F, 1, 2);
    temp2->next = temp1 = setnote(1, E, 1, 2);
    temp1->next = temp2 = setnote(1, F, 1, 2);
    

    // ready to play
    if (currentnote)  {
        play();
        universal.attach(&playnext, currentnote->length);
    }
    
    while(1);
}
