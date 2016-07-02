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
#include "lv2/lv2plug.in/ns/ext/atom/util.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/ext/midi/midi.h"
#include "lv2/lv2plug.in/ns/ext/patch/patch.h"

#include "../plugin.h"

#define GS_REPEAT_URI "https://github.com/Volcomix/guitarswitch/plugins/repeat"

typedef struct {
	LV2_URID atom_Path;
	LV2_URID atom_Resource;
	LV2_URID atom_Sequence;
	LV2_URID atom_URID;
	LV2_URID atom_eventTransfer;
	LV2_URID midi_Event;
	LV2_URID patch_Set;
	LV2_URID patch_property;
	LV2_URID patch_value;
} RepeatURIs;

class Repeat : public Plugin {
	    // Ports
        enum {
            IN  = 0,
            OUT = 1
        };
	    const LV2_Atom_Sequence* in_port;
        LV2_Atom_Sequence* out_port;

        // URIs
        RepeatURIs uris;
    public:
        Repeat(const LV2_Feature* const* features) : Plugin(features) { };

        void mapUris();
        void connect_port(uint32_t port, void* data);
        void run(uint32_t sample_count);
};

#endif // REPEAT_H