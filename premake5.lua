workspace "ChessClasses"
    configurations { "Debug", "Release" }

project "ChessClasses"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. os.target() .. "/%{cfg.buildcfg}")

    files { "src/**.cpp"}

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "system:macosx"
        xcodebuildsettings {
            ["ARCHS"] = "$(ARCHS_STANDARD)";
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.10";
        }
