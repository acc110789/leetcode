noinst_PROGRAMS = install_rpm	\
				  rpmbuild	\
				  write_rpm	\
				  elfdeps	\
				  update_db	\
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

update_db_CFLAGS = $(RPM_CFLAGS)	\
				   $(NULL)
update_db_LDADD = $(RPM_LIBS)	\
				  $(NULL)

rpmbuild_CFLAGS = $(RPM_CFLAGS)  \
				  $(GLIB2_CFLAGS)  \
				  $(POPT_CFLAGS) \
				  $(NULL)
rpmbuild_LDADD = $(RPM_LIBS) \
				 $(GLIB2_LIBS)  \
				 $(POPT_LIBS)    \
				 $(WITH_LIBRPMBUILD_LIB)	\
				 $(NULL)
