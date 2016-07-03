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

#include "articulation.h"

void Articulation::note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (note == 38) {
        activated = true;
    } else if (activated) {
        activated_note_on(channel, note, velocity);
    } else {
        forward();
    }
}

void Articulation::note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (note == 38) {
        activated = false;
    } else if (activated) {
        activated_note_off(channel, note, velocity);
    } else {
        forward();
    }
}