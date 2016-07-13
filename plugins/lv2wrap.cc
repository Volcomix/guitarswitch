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

#include <iostream>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#include "plugin.h"
#include "duplicate/duplicate.h"
#include "repeat/repeat.h"

using namespace std;

static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
    ((Plugin*)instance)->connect_port(port, data);
}

template <class T>
static LV2_Handle instantiate(const LV2_Descriptor*     descriptor,
                              double                    rate,
                              const char*               path,
                              const LV2_Feature* const* features) {
    try {
        Plugin* plugin = new T(features);

        // Map URIs and initialise forge/logger
        plugin->map_uris();

        return (LV2_Handle)plugin;
    } catch (MissingFeatureException& e) {
        cerr << "Missing feature " << e.get_feature_name() << endl;
    }

    return NULL;
}

static void cleanup(LV2_Handle instance) {
    delete (Plugin*)instance;
}

static void run(LV2_Handle instance, uint32_t sample_count) {
    ((Plugin*)instance)->run(sample_count);
}

static const void* extension_data(const char* uri) {
    return NULL;
}

static LV2_Descriptor descriptor;

template <class T>
static const LV2_Descriptor* get_descriptor() {
    descriptor.URI            = T::URI;
    descriptor.instantiate    = instantiate<T>;
    descriptor.connect_port   = connect_port;
    descriptor.activate       = NULL;
    descriptor.run            = run;
    descriptor.deactivate     = NULL;
    descriptor.cleanup        = cleanup;
    descriptor.extension_data = extension_data;
    return &descriptor;
}

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0 : return get_descriptor<Duplicate>();
    case 1 : return get_descriptor<Repeat>();
    default: return NULL;
    }
}