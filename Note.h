#define BPM 100  // global beats per minute

typedef struct mynote {
    int n;   // number of notes
    int *value;  // pointer to list of values (1 to 13)
    float length;  // time (s) until next note
    struct mynote* next;  // pointer to next note
} Note;

Note* setnote(int, int[], int, int);