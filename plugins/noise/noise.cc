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

#include "noise.h"

const char* Noise::URI = "https://github.com/Volcomix/guitarswitch/plugins/noise";

void Noise::connect_port(uint32_t port, void* data) {
    switch (port) {
    case NOISE_CHANNEL: noise_channel = (const float*)data;     break;
    case NOISE_NOTE   : noise_note    = (const float*)data;     break;
    default           : Articulation::connect_port(port, data); break;
    }
}

void Noise::stop_noise(uint8_t velocity) {
    if (noise_playing) {
        append_note_off(*noise_channel, *noise_note, velocity);
    }
}

void Noise::activated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    stop_noise(velocity);
    noise_playing = false;
    forward();
}

void Noise::deactivated_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    activated_note_on(channel, note, velocity);
}

void Noise::activated_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    forward();
    stop_noise(velocity);
    append_note_on(*noise_channel, *noise_note, velocity);
    noise_playing = true;
}