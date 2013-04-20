#define hi(X)  (X + 7)

extern int BPM;

const int G = 1;
const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;

// define Note
typedef struct mynote {
    int n;   // number of notes
    int *value;  // pointer to list of values (1 to 13)
    float length;  // time (s) until next note
    struct mynote* next;  // pointer to next note
} Note;

// create a note, returns a pointer to it
Note* setnote(int, int[], int, int);

// create a note and add to the end of the list linked to Note
// returns pointer to the newest note (i.e. last)
Note* addnote(Note*, int, int[], int, int);
Note* addnote(Note*, int, int, int);
Note* addnote(Note*, Note*);