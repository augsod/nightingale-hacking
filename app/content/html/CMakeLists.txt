include(SbDistribute)
include(SbJarManifest)

project(app.content.html)

sb_distribute_preprocess(${CMAKE_CURRENT_SOURCE_DIR}
  eula.html
  about.html)

sb_jar_manifest()

add_dependencies(${PROJECT_NAME}.manifest
  ${PROJECT_NAME}.eula.html
  ${PROJECT_NAME}.about.html)

add_custom_target(${PROJECT_NAME}.CLEAN ALL
  ${CMAKE_COMMAND} -E remove -f
  ${CMAKE_CURRENT_SOURCE_DIR}/eula.html
  ${CMAKE_CURRENT_SOURCE_DIR}/about.html)

add_dependencies(${PROJECT_NAME}.CLEAN
  ${PROJECT_NAME}.jar)
