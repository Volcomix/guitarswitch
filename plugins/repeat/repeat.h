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

#include <cstring>

#include <string>
#include <iostream>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/ext/atom/util.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/ext/midi/midi.h"
#include "lv2/lv2plug.in/ns/ext/patch/patch.h"

using namespace std;

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

class Repeat {
        // Features
        LV2_URID_Map* map;

	    // Ports
        enum {
            IN  = 0,
            OUT = 1
        };
	    const LV2_Atom_Sequence* in_port;
        LV2_Atom_Sequence* out_port;

        // URIs
        RepeatURIs uris;

        void mapUris();
        
    public:
        Repeat(const LV2_Feature* const* features);
        void connect_port(uint32_t port, void* data);
        void run(uint32_t sample_count);
};

class MissingFeatureException {
        string featureName;
    public:
        MissingFeatureException(string featureName) { this->featureName = featureName; }
        string getFeatureName()                     { return featureName; }
};

static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
    ((Repeat*)instance)->connect_port(port, data);
}

static LV2_Handle instantiate(const LV2_Descriptor*     descriptor,
                              double                    rate,
                              const char*               path,
                              const LV2_Feature* const* features) {
    try {
        return (LV2_Handle)new Repeat(features);
    } catch (MissingFeatureException& e) {
        cerr << "Missing feature " << e.getFeatureName() << endl;
    }

	return NULL;
}

static void cleanup(LV2_Handle instance) {
	delete (Repeat*)instance;
}

static void run(LV2_Handle instance, uint32_t sample_count) {
    ((Repeat*)instance)->run(sample_count);
}

static const void* extension_data(const char* uri) {
	return NULL;
}

static const LV2_Descriptor descriptor = {
	GS_REPEAT_URI,
	instantiate,
	connect_port,
	NULL,  // activate,
	run,
	NULL,  // deactivate,
	cleanup,
	extension_data
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
	switch (index) {
	case 0:
		return &descriptor;
	default:
		return NULL;
	}
}

#endif // REPEAT_H