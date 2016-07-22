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

#ifndef GS_ARTICULATION_H
#define GS_ARTICULATION_H

#include "midiplugin.h"

class Articulation : public MidiPlugin {
        enum Ports {
            MODE               = 2,
            ACTIVATE_KEY       = 3,
            VELOCITY_THRESHOLD = 4
        };
        enum Mode {
            ALWAYS       = 0,
            HOLD         = 1,
            STOP         = 2,
            MIN_VELOCITY = 3,
            MAX_VELOCITY = 4
        };
        const float* mode;
        const float* activate_key;
        const float* velocity_threshold;

        // HOLD mode
        bool activated;

        // STOP mode
        uint8_t last_note       = 255;
        uint8_t cancel_note_off = 255;

        void hold_note_on(uint8_t channel, uint8_t note, uint8_t velocity);
        void hold_note_off(uint8_t channel, uint8_t note, uint8_t velocity);

        void stop_note_on(uint8_t channel, uint8_t note, uint8_t velocity);
        void stop_note_off(uint8_t channel, uint8_t note, uint8_t velocity);

        void min_velocity_note_on(uint8_t channel, uint8_t note, uint8_t velocity);
        void min_velocity_note_off(uint8_t channel, uint8_t note, uint8_t velocity);

        void max_velocity_note_on(uint8_t channel, uint8_t note, uint8_t velocity);
        void max_velocity_note_off(uint8_t channel, uint8_t note, uint8_t velocity);
    protected:
        void note_on(uint8_t channel, uint8_t note, uint8_t velocity);
        void note_off(uint8_t channel, uint8_t note, uint8_t velocity);

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

        virtual void connect_port(uint32_t port, void* data);
};

#endif // GS_ARTICULATION_H