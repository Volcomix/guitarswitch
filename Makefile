PREFIX = /usr/local
LV2DIR = $(PREFIX)/lib/lv2

BUNDLE = guitarswitch.lv2

# -DDEBUG might be added to DEFS
CXXFLAGS = -fPIC $(DEFS)

OBJS = plugins/lv2wrap.o plugins/plugin.o plugins/midiplugin.o \
       plugins/articulation.o plugins/repeat/repeat.o plugins/duplicate/duplicate.o \
       plugins/noise/noise.o

all : guitarswitch.so

guitarswitch.so : $(OBJS)
	cc -shared -o guitarswitch.so $(OBJS)

$(OBJS) : plugins/plugin.h plugins/midiplugin.h plugins/articulation.h \
          plugins/repeat/repeat.h plugins/duplicate/duplicate.h \
          plugins/noise/noise.h

install : all manifest.ttl.in plugins/repeat/repeat.ttl \
          plugins/duplicate/duplicate.ttl plugins/noise/noise.ttl
	install -d $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install guitarswitch.so $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install -m644 manifest.ttl.in $(DESTDIR)$(LV2DIR)/$(BUNDLE)/manifest.ttl
	install -m644 plugins/repeat/repeat.ttl $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install -m644 plugins/duplicate/duplicate.ttl $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install -m644 plugins/noise/noise.ttl $(DESTDIR)$(LV2DIR)/$(BUNDLE)

uninstall :
	rm -rf $(DESTDIR)$(LV2DIR)/$(BUNDLE)

clean :
	rm guitarswitch.so $(OBJS)