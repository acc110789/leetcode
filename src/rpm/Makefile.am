noinst_PROGRAMS = install_rpm	\
				  write_rpm	\
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
				 -lrpmbuild	\
				 $(NULL)
