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

#ifndef ARTICULATION_H
#define ARTICULATION_H

#include "midiplugin.h"

class Articulation : public MidiPlugin {
        // Ports
        enum {
            MODE         = 2,
            ACTIVATE_KEY = 3
        };
        enum Mode {
            ALWAYS = 0,
            HOLD   = 1,
            STOP   = 2
        };
        const float* mode;
        const float* activate_key;

        bool activated;

        uint8_t last_note = 255; // STOP mode

        void connect_port(uint32_t port, void* data);

        void note_on(uint8_t channel, uint8_t note, uint8_t velocity);
        void note_off(uint8_t channel, uint8_t note, uint8_t velocity);
    protected:
        virtual void activated_note_on(uint8_t channel,
                                       uint8_t note,
                                       uint8_t velocity) { forward(); }

        virtual void deactivated_note_on(uint8_t channel,
                                         uint8_t note,
                                         uint8_t velocity) { forward(); }

        virtual void activated_note_off(uint8_t channel,
                                        uint8_t note,
                                        uint8_t velocity) { forward(); }

        virtual void deactivated_note_off(uint8_t channel,
                                          uint8_t note,
                                          uint8_t velocity) { forward(); }
    public:
        Articulation(const LV2_Feature* const* features) : MidiPlugin(features) { };
};

#endif // ARTICULATION_H