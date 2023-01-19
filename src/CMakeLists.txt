find_package(nlohmann_json 3.11.2 REQUIRED)

add_library(libgrubCfg STATIC grub_cfg.cpp)
target_link_libraries(libgrubCfg PRIVATE nlohmann_json::nlohmann_json)
