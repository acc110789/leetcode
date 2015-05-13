noinst_PROGRAMS = hello_layout	\
				  hello_cpu	\
				  hello_stack

BUILT_SOURCES = moses-resources.c	\
				moses-resources.h

hello_layout_SOURCES = hello-layout.c
hello_layout_CFLAGS = $(GTK_TESTCASE_CFLAGS)
hello_layout_LDADD = $(GTK_TESTCASE_LIBS)

hello_cpu_SOURCES = hello-cpu.c	\
					cpu.c
hello_cpu_CFLAGS = $(GTK_TESTCASE_CFLAGS)
hello_cpu_LDADD = $(GTK_TESTCASE_LIBS)

hello_stack_SOURCES = $(BUILT_SOURCES)	\
					  hello-stack.c	\
					  moses-stackswitcher.c
hello_stack_CFLAGS = $(GTK_TESTCASE_CFLAGS)
hello_stack_LDADD = $(GTK_TESTCASE_LIBS)

resource_files = dot.png
moses-resources.c: moses.gresource.xml $(resource_files)
	$(AM_V_GEN) glib-compile-resources --target=$@ --generate-source --c-name moses $<
moses-resources.h: moses.gresource.xml $(resource_files)
	$(AM_V_GEN) glib-compile-resources --target=$@ --generate-header --c-name moses $<

EXTRA_DIST = $(resource_files) moses.gresource.xml
