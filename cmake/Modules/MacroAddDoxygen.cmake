macro(add_doxygen)
    # check if doxygen is even installed
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(WARNING "Doxygen not found, cannot generate documentation.")
    else()
        # prepare doxygen configuration file
        configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in ${PROJECT_SOURCE_DIR}/Doxyfile)

        # add doxygen as target
        add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile)

        # cleanup $build/api-doc on "make clean"
        set_property(DIRECTORY APPEND PROPERTY
                     ADDITIONAL_MAKE_CLEAN_FILES doc)

        # add doxygen as dependency to doc-target
        get_target_property(DOC_TARGET doc TYPE)
        if(NOT DOC_TARGET)
            add_custom_target(doc)
        endif()
        add_dependencies(doc doxygen)

        # install HTML API documentation and manual pages
        #set(DOC_PATH "share/doc/${PROJECT_NAME}")
        #install(DIRECTORY ${PROJECT_BINARY_DIR}/doc/html DESTINATION ${DOC_PATH})

        # install man pages into packages, scope is now project root..
        #install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/man/man3 DESTINATION share/man/man3)
    endif()
endmacro()
