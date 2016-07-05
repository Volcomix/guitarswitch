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

#ifndef MIDIPLUGIN_H
#define MIDIPLUGIN_H

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/ext/atom/util.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/ext/midi/midi.h"

#include "plugin.h"

class MidiPlugin : public Plugin {
        // Ports
        enum {
            IN  = 0,
            OUT = 1
        };
        const LV2_Atom_Sequence* in_port;
        LV2_Atom_Sequence* out_port;

        // URIs
        typedef struct {
            LV2_URID midi_Event;
        } URIs;
        URIs uris;

        uint32_t out_capacity;

        void map_uris();
        void run(uint32_t sample_count);
    protected:
        LV2_Atom_Event* ev;

        void append_event(LV2_Atom_Event* ev);
        void forward();
        
        virtual void connect_port(uint32_t port, void* data);

        virtual void note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
            forward();
        }
        virtual void note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
            forward();
        }
    public:
        MidiPlugin(const LV2_Feature* const* features) : Plugin(features) { };
};

typedef struct {
    LV2_Atom_Event event;
    uint8_t        msg[3];
} MIDINoteEvent;

#endif // MIDIPLUGIN_H