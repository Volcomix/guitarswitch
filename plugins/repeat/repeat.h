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

#ifndef REPEAT_H
#define REPEAT_H

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#include "../midiplugin.h"

#define GS_REPEAT_URI "https://github.com/Volcomix/guitarswitch/plugins/repeat"

class Repeat : public MidiPlugin {
        uint8_t repeat_note;
        uint8_t repeat_velocity;
        void repeat(uint8_t note, uint8_t velocity);
        void stop_repeat();
        void note_on(uint8_t status, uint8_t note, uint8_t velocity);
        void note_off(uint8_t status, uint8_t note, uint8_t velocity);
    public:
        Repeat(const LV2_Feature* const* features) : MidiPlugin(features) { };
};

#endif // REPEAT_H