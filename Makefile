PREFIX = /usr/local
LV2DIR = $(PREFIX)/lib/lv2

BUNDLE = guitarswitch.lv2

# -DDEBUG might be added to DEFS
CXXFLAGS = -fPIC $(DEFS)

PLUGINS = $(wildcard plugins/*/*.cc)

OBJS = plugins/lv2wrap.o plugins/plugin.o plugins/midiplugin.o plugins/articulation.o \
       $(PLUGINS:.cc=.o)

all : guitarswitch.so manifest.ttl

guitarswitch.so : $(OBJS)
	cc -shared -o guitarswitch.so $(OBJS)

$(OBJS) : plugins/plugin.h plugins/midiplugin.h plugins/articulation.h \
          $(PLUGINS:.cc=.h)

manifest.ttl : manifest.ttl.in plugin.ttl.in
	cp manifest.ttl.in manifest.ttl
	for lv2name in $(basename $(notdir $(PLUGINS))) ; do \
		sed "s/@LV2NAME@/$$lv2name/" plugin.ttl.in \
		>> manifest.ttl ; done

install : all $(PLUGINS:.cc=.ttl)
	install -d $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install guitarswitch.so $(DESTDIR)$(LV2DIR)/$(BUNDLE)
	install -m644 manifest.ttl $(PLUGINS:.cc=.ttl) $(DESTDIR)$(LV2DIR)/$(BUNDLE)

uninstall :
	rm -rf $(DESTDIR)$(LV2DIR)/$(BUNDLE)

clean :
	rm guitarswitch.so $(OBJS) manifest.ttl