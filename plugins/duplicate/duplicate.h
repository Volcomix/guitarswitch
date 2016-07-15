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

#ifndef DUPLICATE_H
#define DUPLICATE_H

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#include "../articulation.h"

class Duplicate : public Articulation {
        enum Ports {
            TRANSPOSE = 5
        };
        const float* transpose;

        uint8_t dup_channel = 255;
        uint8_t dup_note    = 255;
    protected:
        void activated_note_on(uint8_t channel, uint8_t note, uint8_t velocity);
        void activated_note_off(uint8_t channel, uint8_t note, uint8_t velocity);
        void deactivated_note_off(uint8_t channel, uint8_t note, uint8_t velocity);
    public:
        static const char* URI;
        Duplicate(const LV2_Feature* const* features) : Articulation(features) { };
        
        void connect_port(uint32_t port, void* data);
};

#endif // DUPLICATE_H