BUILT_SOURCES = hello-resources.c	\
				hello-resources.h

noinst_PROGRAMS = hello_layout	\
				  hello_cpu	\
				  hello_stack	\
				  hello_dnd	\
				  hello_animation	\
				  hello_clock	\
				  hello_combo	\
				  hello_dlg	\
				  hello_fc	\
				  hello_tray	\
				  hello_settings	\
				  hello_popup	\
				  $(NULL)

hello_layout_SOURCES = hello-layout.c
hello_layout_CFLAGS = $(GTK3_CFLAGS)
hello_layout_LDADD = $(GTK3_LIBS)

hello_cpu_SOURCES = hello-cpu.c	\
					cpu.c
hello_cpu_CFLAGS = $(GTK3_CFLAGS)
hello_cpu_LDADD = $(GTK3_LIBS)

hello_stack_SOURCES = hello-stack.c	\
					  moses-stackswitcher.c	\
					  moses-iconview.c
hello_stack_CFLAGS = $(GTK3_CFLAGS)
hello_stack_LDADD = $(GTK3_LIBS)

hello_dnd_SOURCES = hello-dnd.c	\
					moses-stackswitcher.c
hello_dnd_CFLAGS = $(GTK3_CFLAGS)
hello_dnd_LDADD = $(GTK3_LIBS)

hello_animation_SOURCES = hello-animation.c
hello_animation_CFLAGS = $(GTK2_CFLAGS)
hello_animation_LDADD = $(GTK2_LIBS)

hello_clock_SOURCES = hello-clock.c	\
					  moses-clock.c	\
					  $(BUILT_SOURCES)
hello_clock_CFLAGS = $(GTK3_CFLAGS)
hello_clock_LDADD = $(GTK3_LIBS)

hello_combo_SOURCES = hello-combo.c
hello_combo_CFLAGS = $(GTK3_CFLAGS)
hello_combo_LDADD = $(GTK3_LIBS)

hello_dlg_SOURCES = hello-dlg.c
hello_dlg_CFLAGS = $(GTK3_CFLAGS)
hello_dlg_LDADD = $(GTK3_LIBS)

hello_fc_SOURCES = hello-fc.c
hello_fc_CFLAGS = $(GTK3_CFLAGS)
hello_fc_LDADD = $(GTK3_LIBS)

hello_tray_SOURCES = hello-tray.c	\
					 na-tray-manager.c	\
					 na-tray-child.c
hello_tray_CFLAGS = $(GTK3_CFLAGS)	\
					$(X11_CFLAGS)
hello_tray_LDADD = $(GTK3_LIBS)	\
				   $(X11_LIBS)

hello_settings_SOURCES = hello-settings.c
hello_settings_CFLAGS = $(GTK3_CFLAGS)
hello_settings_LDADD = $(GTK3_LIBS)

hello_popup_SOURCES = hello-popup.c
hello_popup_CFLAGS = $(GTK3_CFLAGS)
hello_popup_LDADD = $(GTK3_LIBS)

resource_files = $(shell glib-compile-resources --generate-dependencies hello.gresource.xml)
hello-resources.c: hello.gresource.xml $(resource_files)
	$(AM_V_GEN) glib-compile-resources --target=$@ --generate-source --c-name hello $<
hello-resources.h: hello.gresource.xml $(resource_files)
	$(AM_V_GEN) glib-compile-resources --target=$@ --generate-header --c-name hello $<
