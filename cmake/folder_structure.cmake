include_guard()
# Organize source files into Visual Studio filters
function(organize_sources TARGET_NAME)
    # Get all sources/headers for the target
    get_target_property(TARGET_SOURCES ${TARGET_NAME} SOURCES)

    foreach(FILE ${TARGET_SOURCES})
        # Get the file's relative path from the PROJECT_SOURCE_DIR
        file(RELATIVE_PATH RELATIVE_PATH "${PROJECT_SOURCE_DIR}" "${FILE}")

        # Extract the directory component (e.g., "src/Core")
        get_filename_component(FILE_DIR "${RELATIVE_PATH}" DIRECTORY)

        # Convert directory separators to Visual Studio filter separators
        string(REPLACE "/" "\\" GROUP_NAME "${FILE_DIR}")

        # Assign the file to a filter
        source_group("${GROUP_NAME}" FILES "${FILE}")
    endforeach()
endfunction()
