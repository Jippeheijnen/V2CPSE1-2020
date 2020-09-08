//
// Created by Jippe Heijnen on 1-10-2019.
//
#include "note_player.hpp"
#include <hwlib.hpp>

#ifndef CSM_MY_NOTE_PLAYER_HPP
#define CSM_MY_NOTE_PLAYER_HPP

class my_note_player : public note_player {
private:
    hwlib::pin_out & lsp;
    const int freqs[17] = {261, 440,466,494,523,554,587,622,659,698,740,784,830,880,932,987,1046};
    char notes[17][4] = {"C3","A4","A4#","B4","C5","C5#","D5","D5#","E5","F5","F5#","G5","G5#","A6","A6#","B6","C6"};
public:
    my_note_player( hwlib::pin_out & lsp ):
            lsp( lsp )
    {}

    void play( const note & n );
};

#endif //CSM_MY_NOTE_PLAYER_HPP
