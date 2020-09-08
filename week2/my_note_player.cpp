#include "hwlib.hpp"
#include "my_note_player.hpp"



void my_note_player::play( const note & n ){
    if( n.frequency == 0 ){
        hwlib::wait_us( n.duration );

    } else {
        auto half_period = n.duration/2;
        auto end = hwlib::now_us() + n.duration;
        while ( end > hwlib::now_us() ) {
            hwlib::wait_us( half_period );
            for (int i=0; i<17; i++){
                if (n.frequency == my_note_player::freqs[i])
                    hwlib::cout << "Note: "<< my_note_player::notes[i] << " Frequency: " << my_note_player::freqs[i] << "Hz" << hwlib::endl;
                else if (n.frequency != my_note_player::freqs[i])
                    continue;
            }
//            hwlib::cout << "Frequency: " << n.frequency << "Hz" << hwlib::endl;
            hwlib::wait_us( half_period );
        }
    }
}
