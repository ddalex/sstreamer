AC_INIT(src/main.c)

PACKAGE=sstream
VERSION=0.1

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

AC_PROG_CC([gcc cl cc])

AC_CHECK_LIB([avdevice], [avdevice_version],[],[AC_MSG_ERROR(["Required library libavdevice not found"])])
AC_CHECK_LIB([avformat], [avformat_version],[],[AC_MSG_ERROR(["Required library libavformat not found"])])
AC_CHECK_LIB([avcodec], [avcodec_version],[],[AC_MSG_ERROR(["Required library libavcodec not found"])])
AC_CHECK_LIB([avutil], [avutil_version],[],[AC_MSG_ERROR(["Required library libavutil not found"])])

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_OUTPUT(Makefile src/Makefile)
