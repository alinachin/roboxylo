#include "mbed.h"
#include "Note.h"

#include "MidiFileIn/MidiFileIn.h"


DigitalOut keys[] = { (p5), (p6), (p7), (p8), (p9), (p10), (p11), (p12), (p13), (p14), (p15), (p16), (p17) };  // output pins, 1 for each key
Timeout universal;  // universal timer - counts down after each note to next note

Note* currentnote;  // pointer to current note
Note* lastnote;     // pointer to last (tail) note - for note creation

int BPM;            // global BPM (speed)

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



/*



// easily create a continuous sequence of notes w/ specified duration, returning a pointer to initial note
Note* scale(int start, int end, int lengthn, int lengthd)  {
    int ntuple; // number of notes to play
    float length;  // length of each individual note
    int arr[] = {start};
    
    if (start > end)  {
        ntuple = start - end + 1;
    }
    else  {
        ntuple = end - start + 1; 
    }
    
    length = (float)lengthn/lengthd / ntuple / BPM*60;
    Note* head = setnote(1, arr, 0, 0); // length dummied out for now
    head->length = length;
    
    for (int i=1; i<ntuple; ++i)  {
        int value;
        if (start > end)  value = start - i;
        else  value = start + i;
        
        int arr2[] = {value};
        Note* temp = addnote(head, 1, arr2, 0, 0);
        temp->length = length;
    }
    
    return head;
}

// create a continuous alternation between 2 notes w/ specified duration
Note* trill(int n1, int n2, int lengthn, int lengthd)  {
    // use 16th notes (relative to BPM)
    
    return NULL;
    
}

Note* snare(int note, int lengthn, int lengthd)  {
    return trill(note, note, lengthn, lengthd);
}

*/




int main() {

    BPM = 100;  // default tempo
    
    // turn all keys off?
    for (int i=0; i<13; ++i)
        keys[i] = 0;

    // load notes into memory
  
    /* int E[] = {1};
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
    */
    
    /*
    int e[] = {E};
    int fM[] = {C, F};
    currentnote = setnote(1, e, 1, 1);
    addnote(currentnote, 2, fM, 1, 1);
    
    addnote(currentnote, scale(G, hi(G), 1, 1));
    */

    /*

    

    // last lab Demo
    
    currentnote = scale(F, D, 3, 2);
    addnote(currentnote, D, 1, 2);
    addnote(currentnote, E, 11, 2);
    addnote(currentnote, G, 1, 2);
    addnote(currentnote, scale(F, D, 3, 2));
    addnote(currentnote, D, 3, 2);
    addnote(currentnote, E, 1, 2);
    addnote(currentnote, C, 3, 2);
    addnote(currentnote, D, 1, 1);
    addnote(currentnote, G, 9, 2);
    addnote(currentnote, D, 1, 1);
    addnote(currentnote, E, 1, 2);
    addnote(currentnote, F, 1, 1);
    addnote(currentnote, D, 1, 2);
    addnote(currentnote, B, 1, 1);
    addnote(currentnote, C, 1, 2);
    addnote(currentnote, D, 1, 1);
    addnote(currentnote, G, 1, 2);
    addnote(currentnote, C, 1, 2);
    addnote(currentnote, D, 1, 2);
    addnote(currentnote, E, 1, 2);
    addnote(currentnote, D, 1, 2);
    addnote(currentnote, C, 1, 2);
    addnote(currentnote, G, 1, 2);
    
    */
    
    
    // ready to play
    if (currentnote)  {
        play();
        universal.attach(&playnext, currentnote->length);
    }
    
    while(1);
}
