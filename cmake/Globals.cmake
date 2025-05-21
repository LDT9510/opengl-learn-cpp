# ========== Global variables ===========

#[[ The root of the project. ]]
set(PROJECT_ROOT_DIR "${PROJECT_SOURCE_DIR}")

#[[ Sources of external libraries. ]]
set(EXTERNAL_LIBS_SOURCES_DIR "${PROJECT_ROOT_DIR}/external/libs")

#[[ Compiler type, for setting flags, etc. ]]
set(CXX_COMPILER_GCC_LIKE_GXPR "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(CXX_COMPILER_MSVC_LIKE_GXPR "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

#[[ Specific Compilers ]]
string(COMPARE EQUAL "CLang" CMAKE_CXX_COMPILER_ID CXX_COMPILER_IS_CLANG)
string(COMPARE EQUAL "MSVC" CMAKE_CXX_COMPILER_ID CXX_COMPILER_IS_MSVC)
string(COMPARE EQUAL "GNU" CMAKE_CXX_COMPILER_ID CXX_COMPILER_IS_GNU)
