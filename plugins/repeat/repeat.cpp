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

#include "repeat.h"

Repeat::Repeat(const LV2_Feature* const* features) {
	// Get host features
    for (int i = 0; features[i]; ++i) {
		if (!strcmp(features[i]->URI, LV2_URID__map)) {
			map = (LV2_URID_Map*)features[i]->data;
		}
	}
    if (!map) {
        throw MissingFeatureException("urid:map");
	}

    // Map URIs and initialise forge/logger
    mapUris();
}

void Repeat::mapUris() {
    uris.atom_Path          = map->map(map->handle, LV2_ATOM__Path);
	uris.atom_Resource      = map->map(map->handle, LV2_ATOM__Resource);
	uris.atom_Sequence      = map->map(map->handle, LV2_ATOM__Sequence);
	uris.atom_URID          = map->map(map->handle, LV2_ATOM__URID);
	uris.atom_eventTransfer = map->map(map->handle, LV2_ATOM__eventTransfer);
	uris.midi_Event         = map->map(map->handle, LV2_MIDI__MidiEvent);
	uris.patch_Set          = map->map(map->handle, LV2_PATCH__Set);
	uris.patch_property     = map->map(map->handle, LV2_PATCH__property);
    uris.patch_value        = map->map(map->handle, LV2_PATCH__value);
}

void Repeat::connect_port(uint32_t port, void* data) {
	switch (port) {
	case IN:
		in_port = (const LV2_Atom_Sequence*)data;
		break;
	case OUT:
		out_port = (LV2_Atom_Sequence*)data;
		break;
	default:
		break;
	}
}

void Repeat::run(uint32_t sample_count) {

}