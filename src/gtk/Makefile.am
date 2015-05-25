BUILT_SOURCES = hello-resources.c	\
				hello-resources.h

noinst_PROGRAMS = hello_layout	\
				  hello_cpu	\
				  hello_stack	\
				  hello_dnd	\
				  hello_animation	\
				  hello_clock	\
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

resource_files = $(shell glib-compile-resources --generate-dependencies hello.gresource.xml)
hello-resources.c: hello.gresource.xml $(resource_files)
	$(AM_V_GEN) glib-compile-resources --target=$@ --generate-source --c-name hello $<
hello-resources.h: hello.gresource.xml $(resource_files)
	$(AM_V_GEN) glib-compile-resources --target=$@ --generate-header --c-name hello $<
