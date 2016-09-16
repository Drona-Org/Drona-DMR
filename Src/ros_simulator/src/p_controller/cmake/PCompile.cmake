function (p_compile pproject p_src)
	set(p_compile_cmd mono ${P_COMPILER_PATH})
	get_filename_component(p_src_basename ${p_src} NAME_WE)
	set(generated_c_src ${p_src_basename}.c)
	set(output_dir ${CMAKE_CURRENT_BINARY_DIR}/generated/${pproject})
	set(output_c_srcs ${output_dir}/${generated_c_src} ${output_dir}/linker.c)
	add_custom_command(
		OUTPUT ${output_c_srcs}
	    COMMAND ${CMAKE_COMMAND} -E make_directory ${output_dir}
		COMMAND ${p_compile_cmd} /outputDir:${output_dir} ${p_src}
		DEPENDS ${p_src}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Compiling P ${p_src}..."
	)

	if (NOT (TARGET Prt))
		add_library(Prt SHARED IMPORTED)
		set_target_properties(Prt PROPERTIES IMPORTED_LOCATION ${P_LIB_LINK_PATH}/libPrt_shared.so)
		add_definitions( -DPRT_PLAT_LINUXUSER ) # currently ros only supports *nix/OSX
	endif()

	set(${pproject}_GENERATED_SRCS ${output_c_srcs} PARENT_SCOPE)
	set(${pproject}_INCLUDE_DIRS ${output_dir} ${P_LIB_INCLUDE_PATH} PARENT_SCOPE)
	set(${pproject}_LINK_LIBS Prt PARENT_SCOPE)

endfunction()
