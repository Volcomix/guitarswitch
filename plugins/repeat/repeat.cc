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

void Repeat::stop_repeat(uint8_t velocity) {
    if (repeat_note != 255) {
        append_note_off(repeat_channel, repeat_note, velocity);
    }
}

void Repeat::activated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    stop_repeat(velocity);
    repeat_channel = 255;
    repeat_note    = 255;
    forward();
}

void Repeat::deactivated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    activated_note_on(channel, note, velocity);
}

void Repeat::activated_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    forward();
    stop_repeat(velocity);
    append_note_on(channel, note, velocity);
    repeat_channel = channel;
    repeat_note    = note;
}