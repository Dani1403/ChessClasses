workspace "ChessClasses"
    configurations { "Debug", "Release" }
    architecture "x64"

project "ChessClasses"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.cpp", "src/**.h"}

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    links
    {
        "sfml-graphics",
		"sfml-window",
		"sfml-system"
        "sfml-audio",
        "sfml-network"
    }

    filter "system:macosx"
        xcodebuildsettings {
            ["ARCHS"] = "$(ARCHS_STANDARD)";
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.10";
        }
