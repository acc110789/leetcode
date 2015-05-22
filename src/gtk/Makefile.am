noinst_PROGRAMS = hello_layout	\
				  hello_cpu	\
				  hello_stack	\
				  hello_dnd	\
				  hello_animation	\
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
