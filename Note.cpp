#include "mbed.h"
#include "Note.h"

// initializer for Note struct
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