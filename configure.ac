AC_INIT(src/main.c)

PACKAGE=sstream
VERSION=0.1

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

AC_PROG_CC([gcc cl cc])

AC_CHECK_LIB([avdevice], [avdevice_version],[],[AC_MSG_ERROR(["Required library libavdevice not found"])])
AC_CHECK_LIB([avcodec], [avcodec_version],[],[AC_MSG_ERROR(["Required library libavcodec not found"])])

AC_OUTPUT(Makefile src/Makefile)
