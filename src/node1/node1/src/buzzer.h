#ifndef BUZZER_H_
#define BUZZER_H_

uint16_t song, note;
uint16_t beat;
uint16_t whole_note, half_note, quarter_note, eight_note, sixteenth_note, triplets_note;
uint16_t three_sixteenths, three_eights;
uint8_t music_on, game_song;

void BUZZER_init(void);
void BUZZER_start(uint8_t start);
void BUZZER_set_tempo(uint8_t tempo);
void BUZZER_play_song(char *screen_name);
void BUZZER_play_note(float note);
void BUZZER_choose_game_song(uint8_t song_on);

#endif