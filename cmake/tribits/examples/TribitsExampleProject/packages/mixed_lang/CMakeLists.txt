TRIBITS_PACKAGE( MixedLang  ENABLE_SHADOWING_WARNINGS  CLEANED )

TRIBITS_ADD_DEBUG_OPTION()

TRIBITS_ADD_SHOW_DEPRECATED_WARNINGS_OPTION()

ADD_SUBDIRECTORY(src)

TRIBITS_ADD_TEST_DIRECTORIES(test)

TRIBITS_PACKAGE_POSTPROCESS()
