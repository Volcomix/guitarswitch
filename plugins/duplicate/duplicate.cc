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

void Duplicate::duplicate(uint8_t status, uint8_t note, uint8_t velocity) {
    forward();

    uint8_t transpose = *this->transpose;
    if (transpose == 0 || note + transpose < 0 || note + transpose > 127) {
        return;
    }

    MIDINoteEvent duplicate;
    duplicate.event  = *ev;
    duplicate.msg[0] = status;
    duplicate.msg[1] = note + transpose;
    duplicate.msg[2] = velocity;

    append_event(&duplicate.event);
}

void Duplicate::activated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    duplicate(channel | LV2_MIDI_MSG_NOTE_ON, note, velocity);
}

void Duplicate::activated_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    duplicate(channel | LV2_MIDI_MSG_NOTE_OFF, note, velocity);
}

void Duplicate::deactivated_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    activated_note_off(channel, note, velocity);
}