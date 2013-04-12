#include "mbed.h"
#include "Note.h"

DigitalOut keys[] = { (p5), (p6), (p7), (p8), (p9), (p10), (p11), (p12), (p13), (p14), (p15), (p16), (p17) };  // output pins, 1 for each key
Timeout universal;  // universal timer - counts down after each note to next note

Note* currentnote;  // pointer to current note
Note* lastnote;     // pointer to last (tail) note - for note creation

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



// easily create a continuous sequence of notes, returning a pointer to initial note
void scale(int start, int end, int lengthn, int lengthd)  {
    
}


int main() {
    // turn all keys off?
    for (int i=0; i<13; ++i)
        keys[i] = 0;

    // load notes into memory
  
    int E[] = {1};
    int F[] = {2};
    int G[] = {3};
    int A[] = {4};
    Note* temp1;
    Note* temp2;
    
    currentnote = setnote(1, G, 1, 4);
    currentnote->next = temp1 = setnote(1, A, 1, 4);
    temp1->next = temp2 = setnote(1, G, 1, 2);
    temp2->next = temp1 = setnote(1, F, 1, 2);
    temp1->next = temp2 = setnote(1, E, 1, 1);
    

    // ready to play
    if (currentnote)  {
        play();
        universal.attach(&playnext, currentnote->length);
    }
    
    while(1);
}
