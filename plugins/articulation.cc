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

#include "articulation.h"

void Articulation::connect_port(uint32_t port, void* data) {
    switch (port) {
    case MODE              : mode               = (const float*)data; break;
    case ACTIVATE_KEY      : activate_key       = (const float*)data; break;
    case VELOCITY_THRESHOLD: velocity_threshold = (const float*)data; break;
    default                : MidiPlugin::connect_port(port, data);    break;
    }
}

void Articulation::hold_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (note == (uint8_t)*activate_key) {
        activated = true;
        forward();
    } else if (activated) {
        activated_note_on(channel, note, velocity);
    } else {
        deactivated_note_on(channel, note, velocity);
    }
}

void Articulation::hold_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (note == (uint8_t)*activate_key) {
        activated = false;
        forward();
    } else if (activated) {
        activated_note_off(channel, note, velocity);
    } else {
        deactivated_note_off(channel, note, velocity);
    }
}

void Articulation::stop_note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (note == (uint8_t)*activate_key) {
        forward();
        if (last_note != 255) {
            MIDINoteEvent stop;
            stop.event  = *ev;
            stop.msg[0] = channel | LV2_MIDI_MSG_NOTE_OFF;
            stop.msg[1] = last_note;
            stop.msg[2] = velocity;
            ev = &stop.event;
            activated_note_off(channel, last_note, velocity);

            cancel_note_off = last_note;
            last_note       = 255;
        }
    } else {
        last_note = note;
        deactivated_note_on(channel, note, velocity);
    }
}

void Articulation::stop_note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (note == (uint8_t)*activate_key) {
        forward();
    } else if (note == cancel_note_off) {
        cancel_note_off = 255;
    } else {
        deactivated_note_off(channel, note, velocity);
        if (note == last_note) {
            last_note = 255;
        }
    }
}

void Articulation::min_velocity_note_on(uint8_t channel,
                                        uint8_t note,
                                        uint8_t velocity) {
    if (velocity >= (uint8_t)*velocity_threshold) {
        activated_note_on(channel, note, velocity);
    } else {
        deactivated_note_on(channel, note, velocity);
    }
}

void Articulation::min_velocity_note_off(uint8_t channel,
                                         uint8_t note,
                                         uint8_t velocity) {
    if (velocity >= (uint8_t)*velocity_threshold) {
        activated_note_off(channel, note, velocity);
    } else {
        deactivated_note_off(channel, note, velocity);
    }
}

void Articulation::max_velocity_note_on(uint8_t channel,
                                        uint8_t note,
                                        uint8_t velocity) {
    if (velocity <= (uint8_t)*velocity_threshold) {
        activated_note_on(channel, note, velocity);
    } else {
        deactivated_note_on(channel, note, velocity);
    }
}

void Articulation::max_velocity_note_off(uint8_t channel,
                                         uint8_t note,
                                         uint8_t velocity) {
    if (velocity <= (uint8_t)*velocity_threshold) {
        activated_note_off(channel, note, velocity);
    } else {
        deactivated_note_off(channel, note, velocity);
    }
}

void Articulation::note_on(uint8_t channel, uint8_t note, uint8_t velocity) {
    switch ((uint8_t)*mode) {
    case HOLD        : hold_note_on(channel, note, velocity);         break;
    case STOP        : stop_note_on(channel, note, velocity);         break;
    case MIN_VELOCITY: min_velocity_note_on(channel, note, velocity); break;
    case MAX_VELOCITY: max_velocity_note_on(channel, note, velocity); break;
    default          : activated_note_on(channel, note, velocity);    break;
    }
}

void Articulation::note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
    switch ((uint8_t)*mode) {
    case HOLD        : hold_note_off(channel, note, velocity);         break;
    case STOP        : stop_note_off(channel, note, velocity);         break;
    case MIN_VELOCITY: min_velocity_note_off(channel, note, velocity); break;
    case MAX_VELOCITY: max_velocity_note_off(channel, note, velocity); break;
    default          : activated_note_off(channel, note, velocity);    break;
    }
}