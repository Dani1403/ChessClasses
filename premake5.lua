workspace "ChessClasses"
    configurations { "Debug", "Release" }
    architecture "x86"

project "ChessClasses"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.cpp", "src/**.h"}

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
