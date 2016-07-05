/*
    GuitarSwitch - LV2 plugins to enable Guitar articulations on Midi notes
    Copyright (C) 2016  Volcomix

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "repeat.h"

const char* Repeat::URI = "https://github.com/Volcomix/guitarswitch/plugins/repeat";

void Repeat::repeat(uint8_t channel, uint8_t note, uint8_t velocity) {
    MIDINoteEvent repeat;
    repeat.event  = *ev;
    repeat.msg[0] = channel | LV2_MIDI_MSG_NOTE_ON;
    repeat.msg[1] = note;
    repeat.msg[2] = velocity;

    append_event(&repeat.event);

    repeat_channel  = channel;
    repeat_note     = note;
    repeat_velocity = velocity;
}

void Repeat::stop_repeat() {
    if (repeat_note != -1) {
        MIDINoteEvent stop;
        stop.event  = *ev;
        stop.msg[0] = repeat_channel | LV2_MIDI_MSG_NOTE_OFF;
        stop.msg[1] = repeat_note;
        stop.msg[2] = repeat_velocity;

        append_event(&stop.event);

        repeat_channel  = -1;
        repeat_note     = -1;
        repeat_velocity = -1;
    }
}

void Repeat::activated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    stop_repeat();
    forward();
}

void Repeat::deactivated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    stop_repeat();
    forward();
}

void Repeat::activated_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    forward();
    stop_repeat();
    repeat(channel, note, velocity);
}