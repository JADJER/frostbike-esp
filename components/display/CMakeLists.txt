set(display_srcs
        "src/display.c"
        "src/epd4in2.cpp"
        "src/epdif.cpp"
        "src/epdpaint.cpp"
        "src/font8.cpp"
        "src/font12.cpp"
        "src/font16.cpp"
        "src/font20.cpp"
        "src/font24.cpp"
        "src/imagedata.cpp")

idf_component_register(SRCS "${display_srcs}" INCLUDE_DIRS "include")