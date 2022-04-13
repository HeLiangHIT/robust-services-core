# Options common to all RSC builds
#
if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
  (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    message("Reading GlobalSettingsInclude.cmake shared by MSVC and CLang")

    # Clang is currently used only to target Windows
    # Enable Windows targets (*.win.cpp files)
    add_compile_definitions(OS_WIN)

    # Use async exception handling to catch structured exceptions
    add_compile_options(/EHa)

    # Disable optimizations to improve debugging
    add_compile_options(/Od)

    # Keep frame pointers
    add_compile_options(/Oy-)

    # Include security checks
    add_compile_options(/GS)

    # Enable all compiler warnings
    add_compile_options(/Wall)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("Reading GlobalSettingsInclude.cmake for MSVC")

    # Include run-time checks
    add_compile_options(/RTC1)

    # Provide full debugging information
    add_compile_options(/Z7)

    # Disable Just My Code debugging
    add_compile_options(/JMC-)

    # Use standard C++
    add_compile_options(/permissive-)

    # Treat compiler security warnings as errors
    add_compile_options(/sdl)

    # Compiler warnings to treat as errors
    add_compile_options(/we4715)

    # Compiler warnings to suppress
    add_compile_options(/wd4061 /wd4062 /wd4100 /wd4242 /wd4244 /wd4267)
    add_compile_options(/wd4365 /wd4514 /wd4582 /wd4623 /wd4625 /wd4626)
    add_compile_options(/wd4668 /wd4710 /wd4711 /wd4820 /wd5026 /wd5027)
    add_compile_options(/wd5045 /wd5219 /wd26812)

    # Include debugging information
    add_link_options(/DEBUG:FULL)

    # Do not merge identical functions or data
    add_link_options(/OPT:NOICF)

    # Support incremental linking for patching
    add_link_options(/INCREMENTAL)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message("Reading GlobalSettingsInclude.cmake for Clang")

    # Provide full debugging information
    add_compile_options(/Zi)

    # Temporarily disable specific compiler warnings
    add_compile_options(-Wno-defaulted-function-deleted)
    add_compile_options(-Wno-reserved-identifier)
    add_compile_options(-Wno-signed-enum-bitfield)
    add_compile_options(-Wno-tautological-type-limit-compare)

    # Disable specific compiler warnings
    add_compile_options(-Wno-c++98-compat)
    add_compile_options(-Wno-c++98-compat-pedantic)
    add_compile_options(-Wno-cast-align)
    add_compile_options(-Wno-cast-qual)
    add_compile_options(-Wno-char-subscripts)
    add_compile_options(-Wno-covered-switch-default)
    add_compile_options(-Wno-deprecated-copy-with-dtor)
    add_compile_options(-Wno-documentation)
    add_compile_options(-Wno-exit-time-destructors)
    add_compile_options(-Wno-global-constructors)
    add_compile_options(-Wno-header-hygiene)
    add_compile_options(-Wno-implicit-fallthrough)
    add_compile_options(-Wno-implicit-int-conversion)
    add_compile_options(-Wno-implicit-int-float-conversion)
    add_compile_options(-Wno-inconsistent-missing-destructor-override)
    add_compile_options(-Wno-missing-noreturn)
    add_compile_options(-Wno-old-style-cast)
    add_compile_options(-Wno-shadow)
    add_compile_options(-Wno-shadow-field-in-constructor)
    add_compile_options(-Wno-shorten-64-to-32)
    add_compile_options(-Wno-sign-compare)
    add_compile_options(-Wno-sign-conversion)
    add_compile_options(-Wno-suggest-destructor-override)
    add_compile_options(-Wno-switch)
    add_compile_options(-Wno-switch-enum)
    add_compile_options(-Wno-tautological-undefined-compare)
    add_compile_options(-Wno-trigraphs)
    add_compile_options(-Wno-unused-parameter)
    add_compile_options(-Wno-unreachable-code-break)
    add_compile_options(-Wno-unreachable-code-return)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("Reading GlobalSettingsInclude.cmake for GCC")
endif()
