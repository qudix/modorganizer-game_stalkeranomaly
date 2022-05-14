cmake_minimum_required(VERSION 3.16)

add_library(game_stalkeranomaly
    SHARED
)

mo2_configure_plugin(game_stalkeranomaly
    WARNINGS OFF
)

mo2_install_target(game_stalkeranomaly)

mo2_add_filter(
    NAME src/features
    GROUPS
        features/stalkeranomaly_savegame
)
