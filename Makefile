PREFIX = /usr/local
LV2DIR = $(PREFIX)/lib/lv2

BUNDLE = guitarswitch.lv2

CXXFLAGS = -fPIC

OBJS = plugins/lv2wrap.o plugins/plugin.o plugins/midiplugin.o \
       plugins/repeat/repeat.o

all : guitarswitch.so

guitarswitch.so : $(OBJS)
	cc -shared -o guitarswitch.so $(OBJS)

$(OBJS) : plugins/plugin.h plugins/midiplugin.h plugins/repeat/repeat.h

install : all
	install guitarswitch.so $(DESTDIR)$(LV2DIR)/$(BUNDLE)

clean :
	rm guitarswitch.so $(OBJS)