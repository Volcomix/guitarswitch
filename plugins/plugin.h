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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <cstring>

#include <string>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"

using namespace std;

class Plugin {
    protected:
        // Features
        LV2_URID_Map* map;
        
    public:
        Plugin(const LV2_Feature* const* features);

        virtual void mapUris()                               = 0;
        virtual void connect_port(uint32_t port, void* data) = 0;
        virtual void run(uint32_t sample_count)              = 0;
};

class MissingFeatureException {
        string featureName;
    public:
        MissingFeatureException(string featureName) { this->featureName = featureName; }
        string getFeatureName()                     { return featureName; }
};

#endif // PLUGIN_H