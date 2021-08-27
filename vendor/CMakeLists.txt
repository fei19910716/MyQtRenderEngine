set(vendor_libs
    entityx
)

foreach(vendor_lib ${vendor_libs})
    add_subdirectory(${vendor_lib})
endforeach(vendor_lib ${venc})


add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE ${vendor_libs})