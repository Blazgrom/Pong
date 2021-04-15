function(set_cpp_standard_properties project_name)

    set_target_properties(${project_name}
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
    )

    target_compile_features(${project_name} PUBLIC cxx_std_17)
endfunction()