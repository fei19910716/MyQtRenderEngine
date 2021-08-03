
set(vendor_libs
    glfw
)   

foreach(lib ${vendor_libs})
    add_subdirectory(${lib})
endforeach(lib ${vendor_libs})


add_library(libvendor INTERFACE)

target_link_libraries(libvendor INTERFACE ${vendor_libs})