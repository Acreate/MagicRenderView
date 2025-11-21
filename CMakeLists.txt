cmake_minimum_required( VERSION 3.19 )

# # 加载模块
find_package( CmakeFuncs REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/srcs/cmake/cmakeFuncs/CmakeFuncs" )

# # 获取当前文件夹名称
get_current_dir_name( prject_name ${CMAKE_CURRENT_SOURCE_DIR} )
message( "============ ${prject_name}" )
message( "name = " ${prject_name} ) # # 当前文件名配置为项目名称
project( ${prject_name} )
message( "============ ${CURRENT_FOLDER}" )

set( CMAKE_C_STANDARD 17 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_VISIBILITY_PRESET hidden )
set( CMAKE_C_EXTENSIONS ON )
set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )
set( CMAKE_CXX_EXTENSIONS ON )

include( GenerateExportHeader )
include( GNUInstallDirs )
get_cmake_separator( _cmake_sep )
init_std_builder_path()

find_package( Qt6 QUIET COMPONENTS Widgets Core LinguistTools Network )
if( NOT Qt6_FOUND OR NOT EXISTS "${Qt6_DIR}" )
    # # 使用 qt6
    set( Qt6_DIR "C:/Qt/6.10.0/msvc2022_64/lib/cmake/QT6/" )
    init_qt_dir_event( "${Qt6_DIR}" )
    find_package( Qt6 REQUIRED COMPONENTS Widgets Core LinguistTools  )
else()
    init_qt_dir_event( "${Qt6_DIR}" )
endif()

PRINTF_QT_CMAKE_OUT()

qt_standard_project_setup()

# # supper_cmake_builder_language( _cmake_supper_language_list ) # # 语言支持列表
append_source_file_extensions( LANGUAGES C CXX SUFFIXS h hpp hc H HPP HC ui UI ) # # 追加后缀名

get_cmake_separator( cmake_sep_char )

# add_subdirectory_tools_lib()
# add_subdirectory_code_cpp23_project()
# add_subdirectory_code_project() # # 测试工具
get_path_cmake_dir_path( bin_list "${CMAKE_CURRENT_SOURCE_DIR}/srcs/cpp" "CMakeLists.txt" )
list( APPEND out_path_list ${lib_list} ${bin_list} )
filter_path_repetition( list_result out_path_list )
append_sub_directory_cmake_project_path_list( list_result )

configure_all_target()
