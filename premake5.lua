workspace "ChessClasses"
    configurations { "Debug", "Release" }
    architecture "x64"

project "ChessClasses"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.cpp", "src/**.h", "**.png"}

    includedirs { "vendor/SFML-2.6.1/include" }

    filter "configurations:Debug"
        symbols "On"
        links
           {
            "sfml-graphics-d",
		    "sfml-window-d",
		    "sfml-system-d"
           }
        libdirs { "vendor/SFML-2.6.1/lib" }
        postbuildcommands {
         "{COPY} \"vendor/SFML-2.6.1/bin/*.dll\" \"%{cfg.targetdir}\""
        }

    filter "configurations:Release"
        optimize "On"
        links
           {
            "sfml-graphics",
		    "sfml-window",
		    "sfml-system"
           }
        libdirs { "vendor/SFML-2.6.1/lib" }
        postbuildcommands {
         "{COPY} \"vendor/SFML-2.6.1/bin/*.dll\" \"%{cfg.targetdir}\""
        }

    filter "system:macosx"
        xcodebuildsettings {
            ["ARCHS"] = "$(ARCHS_STANDARD)";
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.10";
        }
