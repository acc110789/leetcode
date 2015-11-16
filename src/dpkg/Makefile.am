noinst_PROGRAMS = extract_deb	\
				  $(NULL)

extract_deb_CFLAGS = $(LIBDPKG_CFLAGS)	\
				     $(NULL)
extract_deb_LDADD = $(LIBDPKG_LIBS)	\
				    $(ZLIB_LIBS)	\
				    -lbz2	\
				    $(LIBLZMA_LIBS)	\
				    $(NULL)
