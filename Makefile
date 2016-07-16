PREFIX = /usr/local
LV2DIR = $(PREFIX)/lib/lv2

BUNDLE = guitarswitch.lv2

# -DDEBUG might be added to DEFS
CXXFLAGS = -fPIC $(DEFS)

PLUGINS = $(wildcard plugins/*/*.cc)

OBJS = plugins/lv2wrap.o plugins/plugin.o plugins/midiplugin.o plugins/articulation.o \
       $(PLUGINS:.cc=.o)

all : guitarswitch.so

guitarswitch.so : $(OBJS)
	cc -shared -o guitarswitch.so $(OBJS)

$(OBJS) : plugins/plugin.h plugins/midiplugin.h plugins/articulation.h \
          $(PLUGINS:.cc=.h)

install : all manifest.ttl.in $(PLUGINS:.cc=.ttl)
	install -d $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install guitarswitch.so $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install -m644 manifest.ttl.in $(DESTDIR)$(LV2DIR)/$(BUNDLE)/manifest.ttl
	install -m644 $(PLUGINS:.cc=.ttl) $(DESTDIR)$(LV2DIR)/$(BUNDLE)

uninstall :
	rm -rf $(DESTDIR)$(LV2DIR)/$(BUNDLE)

clean :
	rm guitarswitch.so $(OBJS)