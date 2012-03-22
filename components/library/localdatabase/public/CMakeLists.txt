include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/library/base/public
  ${CMAKE_SOURCE_DIR}/components/job/public)

xpidl(sbILocalDatabaseLibrary
  sbILocalDatabaseAsyncGUIDArray
  sbILocalDatabaseLibraryCopyListener
  sbILocalDatabaseGUIDArray
  sbILocalDatabaseLibrary
  sbILocalDatabaseMediaItem
  sbILocalDatabaseMigrationHandler
  sbILocalDatabaseMigrationHelper
  sbILocalDatabasePropertyCache
  sbILocalDatabaseResourceProperty
  sbILocalDatabaseResourcePropertyBag
  sbILocalDatabaseSmartMediaList
  sbILocalDatabaseTreeView
  sbILocalDatabaseSimpleMediaList
  sbILibraryStatistics)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase
  sbIJob)