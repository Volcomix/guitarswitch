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

#include "duplicate.h"

const char* Duplicate::URI = "https://github.com/Volcomix/guitarswitch/plugins/duplicate";

void Duplicate::connect_port(uint32_t port, void* data) {
    switch (port) {
    case TRANSPOSE: transpose = (const float*)data;         break;
    default       : Articulation::connect_port(port, data); break;
    }
}

void Duplicate::duplicate(uint8_t channel, uint8_t note, uint8_t velocity) {
    uint8_t transpose       = *this->transpose;
    uint8_t transposed_note = note + transpose;

    if (transpose == 0 || transposed_note < 0 || transposed_note > 127) {
        return;
    }
    
    append_note_on(channel, transposed_note, velocity);
    dup_channel = channel;
    dup_note    = note;
}

void Duplicate::stop_duplicate(uint8_t velocity) {
    uint8_t transpose = *this->transpose;
    append_note_off(dup_channel, dup_note + transpose, velocity);
}

void Duplicate::activated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (dup_note != 255) {
        stop_duplicate(velocity);
    }
    forward();
    duplicate(channel, note, velocity);
}

void Duplicate::activated_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    forward();
    if (dup_channel == channel && dup_note == note) {
        stop_duplicate(velocity);
        dup_channel = 255;
        dup_note    = 255;
    }
}

void Duplicate::deactivated_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    activated_note_off(channel, note, velocity);
}