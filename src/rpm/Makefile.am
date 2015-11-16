noinst_PROGRAMS = install_rpm	\
				  write_rpm	\
				  elfdeps	\
				  $(NULL)

install_rpm_CFLAGS = $(RPM_CFLAGS)	\
				   $(GLIB2_CFLAGS)	\
				   $(POPT_CFLAGS)	\
				   $(NULL)
install_rpm_LDADD = $(RPM_LIBS)	\
				  $(GLIB2_LIBS)	\
				  $(POPT_LIBS)	\
				  $(NULL)

write_rpm_CFLAGS = $(RPM_CFLAGS)    \
				  $(GLIB2_CFLAGS)  \
				  $(POPT_CFLAGS)   \
				  $(NULL)
write_rpm_LDADD = $(RPM_LIBS)   \
				 $(GLIB2_LIBS) \
				 $(POPT_LIBS)  \
				 $(NULL)

elfdeps_CFLAGS = $(RPM_CFLAGS)	\
				 $(POPT_CFLAGS)	\
				 $(NULL)

elfdeps_LDADD = $(RPM_LIBS)	\
				$(POPT_LIBS)	\
				$(WITH_LIBELF_LIB)	\
				$(NULL)
