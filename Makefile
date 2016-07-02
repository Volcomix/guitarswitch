objects = plugins/lv2wrap.o plugins/plugin.o plugins/midiplugin.o \
          plugins/repeat/repeat.o

CXXFLAGS = -fPIC

guitarswitch.so : $(objects)
	cc -shared -o guitarswitch.so $(objects)

$(objects) : plugins/plugin.h plugins/midiplugin.h plugins/repeat/repeat.h

clean :
	rm guitarswitch.so $(objects)