workspace "ChessClasses"
    configurations { "Debug", "Release" }
    architecture "x86"

project "ChessClasses"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.cpp", "src/**.h"}

    includedirs { "vendor/SFML-2.6.1/include" }

    filter "configurations:Debug"
        symbols "On"
        links
           {
            "sfml-graphics-d",
		    "sfml-window-d",
		    "sfml-system-d"
            "sfml-audio-d",
            "sfml-network-d"
           }
        libdirs { "vendor/SFML-2.6.1/lib" }

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
        libdirs { "vendor/SFML-2.6.1/lib" }

    filter "system:macosx"
        xcodebuildsettings {
            ["ARCHS"] = "$(ARCHS_STANDARD)";
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.10";
        }
