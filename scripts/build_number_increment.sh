awk '$2 !~ /VERSION_BUILD_NUMBER/ {print} $2 ~ /VERSION_BUILD_NUMBER/ {print "#define VERSION_BUILD_NUMBER "$3+1}' src/version_info.hpp > src/version_info.hpp
