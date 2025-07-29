
workspace "ZeusEngine"
    configurations {"Debug","Release"}    

    startproject "Game"

project "Game"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"

    architecture ("x64")

    includedirs 
    { 
        "Zeus/Source", 
        "Zeus/Dependencies/Glfw/Include", 
        
    }

    libdirs 
    {
       --"deps/glfw/lib", 
       --"deps/assimp/lib", 
       
    }

    links 
    {
      "Zeus",
       --"glfw3.dll",
       --"glfw3.lib",
    

    }

   files
    { 
      "Game/Source/**.h", 
      "Game/Source/**.cpp"
    }

    --pchheader "Core/Core.h"
    --pchsource "src/Core/Core.cpp"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      buildoptions { "/MP" }
      kind "ConsoleApp"

      links 
      {
          --"assimp-vc143-mtd.lib",
          --"assimp-vc143-mtd.dll",
          --"freetyped.lib",
          --"box2dd.lib",
      }

      --postbuildcommands { "{COPY} deps/glfw/lib/glfw3.dll bin/Debug" }
      --postbuildcommands { "{COPY} deps/assimp/lib/assimp-vc143-mtd.dll bin/Debug" }
      --postbuildcommands { "{COPY} deps/openal/lib/OpenAL32.dll bin/Debug" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      buildoptions { "/MP" }
      kind "WindowedApp"

      links 
      {
          --"assimp-vc143-mt.lib",
          --"assimp-vc143-mt.dll",
          --"freetype.lib",
          --"rbox2d.lib",
      }

    filter "files:**.c"
      flags { "NoPCH" }

      --postbuildcommands { "{COPY} libs/sdl3/lib/x64/SDL3.dll bin/Release" }
      --postbuildcommands { "{COPY} libs/openal/libs/OpenAL32.dll bin/Release" }


project "Zeus"
    kind "StaticLib"

    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"

    architecture ("x64")

    files
    { 
      "Zeus/Source/**.h", 
      "Zeus/Source/**.cpp"
    }

    includedirs 
    { 
        "Zeus/Dependencies/Glfw/Include", 
    }

    libdirs 
    {
       "Zeus/Dependencies/Glfw/Library", 
       --"deps/assimp/lib", 
       
    }

    links
    {
       "glfw3.dll",
       "glfw3.lib",
    }


    postbuildcommands { "{COPY} Zeus/Dependencies/Glfw/Library/glfw3.dll bin/Debug" }

       filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      buildoptions { "/MP" }


