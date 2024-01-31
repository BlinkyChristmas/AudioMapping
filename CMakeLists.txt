cmake_minimjum_required(VERSION 3.25)
project(AudioMapping VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(AudioMapping

    ${PROJECT_SOURCE_DIR}/AudioMapping/main.cpp
    
    ${PROJECT_SOURCE_DIR}/AudioMapping/MusicController.cpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/MusicController.hpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/chunkheader.cpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/chunkheader.hpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/fileheader.cpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/fileheader.hpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/mwavfile.cpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/mwavfile.hpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/wavfmtchunk.cpp
    ${PROJECT_SOURCE_DIR}/AudioMapping/wavfile/wavfmtchunk.hpp

    ${PROJECT_SOURCE_DIR}/common/utility/buffer.cpp
    ${PROJECT_SOURCE_DIR}/common/utility/buffer.hpp
    ${PROJECT_SOURCE_DIR}/common/utility/dbgutil.hpp
    ${PROJECT_SOURCE_DIR}/common/utility/mapfile.cpp
    ${PROJECT_SOURCE_DIR}/common/utility/mapfile.hpp
    ${PROJECT_SOURCE_DIR}/common/utility/strutil.hpp
    ${PROJECT_SOURCE_DIR}/common/utility/timeutil.cpp
    ${PROJECT_SOURCE_DIR}/common/utility/timeutil.hpp

    ${PROJECT_SOURCE_DIR}/thirdparty/rtaudio/RtAudio.cpp
    ${PROJECT_SOURCE_DIR}/thirdparty/rtaudio/RtAudio.h
)

if (WIN32)
    target_compile_definitions(AudioMapping PRIVATE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG>
        __WINDOWS_DS__
        _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
       _WIN32_WINNT=0x0A00
    )
    target_compile_options(AudioMapping PRIVATE
        $<$<CONFIG:Release>:/O2>
    )
    target_link_libraries(AudioMapping
        PUBLIC
            ole32
            dsound
    )
else()
    target_compile_definitions(AudioMapping PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
    )

    target_compile_options(AudioMapping PRIVATE
        $<$<CONFIG:Release>:-O2>
        -Wno-deprecated-declarations
    )
    
   if (APPLE)
        target_compile_definitions(AudioMapping PRIVATE
            __MACOSX_CORE__
        )

        FIND_LIBRARY(COREAUDIO CoreAudio)
        FIND_LIBRARY(COREFOUNDATION CoreFoundation )
        MARK_AS_ADVANCED ( COREAUDIO COREFOUNDATION )

        target_link_libraries(AudioMapping
            PUBLIC
                pthread
                ${COREAUDIO}
                ${COREFOUNDATION}
        )

    else ()
        target_compile_definitions(AudioMapping PRIVATE
            __LINUX_ALSA__
        )
        target_link_libraries(AudioMapping
            PUBLIC
                asound
                pthread
        )
    endif(APPLE)
    
endif (WIN32)

target_include_directories(AudioMapping
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/AudioMapping/
        ${PROJECT_SOURCE_DIR}/common/
        ${PROJECT_SOURCE_DIR}/thirdparty/
        ${PROJECT_SOURCE_DIR}/thirdparty/asio/
)

    

