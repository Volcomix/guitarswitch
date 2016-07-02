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

#include "midiplugin.h"

void MidiPlugin::mapUris() {
    uris.midi_Event = map->map(map->handle, LV2_MIDI__MidiEvent);
}

void MidiPlugin::connect_port(uint32_t port, void* data) {
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

void MidiPlugin::forward(const uint32_t out_capacity, LV2_Atom_Event* ev) {
    lv2_atom_sequence_append_event(out_port, out_capacity, ev);
}

void MidiPlugin::noteOn(const uint32_t out_capacity, LV2_Atom_Event* ev) {
    forward(out_capacity, ev);
}

void MidiPlugin::noteOff(const uint32_t out_capacity, LV2_Atom_Event* ev) {
    forward(out_capacity, ev);
}

void MidiPlugin::run(uint32_t sample_count) {
    const uint32_t out_capacity = out_port->atom.size;

	lv2_atom_sequence_clear(out_port);
    out_port->atom.type = in_port->atom.type;

    LV2_ATOM_SEQUENCE_FOREACH(in_port, ev) {
        if (ev->body.type == uris.midi_Event) {
            const uint8_t* const msg = (const uint8_t*)(ev + 1);
			switch (lv2_midi_message_type(msg)) {
            case LV2_MIDI_MSG_NOTE_ON: noteOn(out_capacity, ev); break;
            case LV2_MIDI_MSG_NOTE_OFF: noteOff(out_capacity, ev); break;
            default: forward(out_capacity, ev); break;
            }
        }
    }
}