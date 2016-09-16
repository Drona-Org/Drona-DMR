function (p_compile pproject p_src)
	get_filename_component(p_src_basename ${p_src} NAME_WE)
	set(generated_c_src ${p_src_basename}.c)
	set(output_dir ${CMAKE_CURRENT_BINARY_DIR}/generated/${pproject})
	set(output_c_srcs ${output_dir}/${generated_c_src} ${output_dir}/linker.c)
	add_custom_command(
		OUTPUT ${output_c_srcs}
	    COMMAND ${CMAKE_COMMAND} -E make_directory ${output_dir}
		COMMAND ${P_COMPILE_CMD} /outputDir:${output_dir} ${p_src}
		DEPENDS ${p_src}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Compiling P ${p_src}..."
	)
	set(${pproject}_GENERATED_SRCS ${output_c_srcs} PARENT_SCOPE)

	if (NOT (TARGET Prt))
		add_library(Prt STATIC IMPORTED)
		set_target_properties(Prt PROPERTIES IMPORTED_LOCATION ${P_LIB_PATH}/libPrt_static.a)
	endif()

	set(${pproject}_INCLUDE_DIRS ${output_dir} ${P_LIB_INCLUDE_PATH} PARENT_SCOPE)
	set(${pproject}_LINK_LIBS Prt PARENT_SCOPE)

endfunction()
