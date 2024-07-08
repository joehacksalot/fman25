
#include "Song.h"

const SongNotes SuccessSound = {
  "Success Sound",
  240,   // Tempo
  6,   // Number of Notes
  {
    {NOTE_A5, NOTE_TYPE_EIGHTH, 1},
    {NOTE_B5, NOTE_TYPE_EIGHTH, 1},
    {NOTE_D6, NOTE_TYPE_EIGHTH, 1},
    {NOTE_E6, NOTE_TYPE_EIGHTH, 1},
    {NOTE_A6, NOTE_TYPE_QUARTER, 1},
    {NOTE_REST, NOTE_TYPE_QUARTER, 1}
  }
};
