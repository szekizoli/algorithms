solution "Algorithms"
    configurations  { "Debug", "Release" }
    startproject    "Algorithms-unittest"

    location "build"

project "Algorithms-main"
    kind      "StaticLib"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "src/main/**.h", 
            "src/main/**.cpp" }

    includedirs { "src/main" }
    filter "configurations:Debug"
    	defines {"DEBUG"}
    	flags {"Symbols"}
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

project "GoogleTest"
    kind      "StaticLib"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "../3rd/gtest-1.7.0/src/gtest_main.cc", 
            "../3rd/gtest-1.7.0/src/gtest-all.cc" }

    libdirs { "../3rd/" }
    includedirs {"../3rd/gtest-1.7.0", "../3rd/gtest-1.7.0/include"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        flags {"Symbols"}
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

project "Algorithms-tests-unit"
    kind      "ConsoleApp"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "src/tests-unit/**.h", 
            "src/tests-unit/**.cpp" }

    links {"Algorithms-main", "GoogleTest"}
    libdirs { "../3rd/" }
    includedirs {"../3rd/gtest-1.7.0", "../3rd/gtest-1.7.0/include", "src/main" }
    filter "configurations:Debug"
        defines {"DEBUG"}
        flags {"Symbols"}
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"