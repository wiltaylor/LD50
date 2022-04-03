{
  description = "LD50 - Delay the inevitable";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  with builtins;
  let
    allPkgs = lib.mkPkgs {
      inherit nixpkgs;
      cfg = { allowUnfree = true; };
    };

    lib = import ./lib;

  in {

    devShell = lib.withDefaultSystems (sys: let 
      pkgs = allPkgs."${sys}";
    in import ./shell.nix { inherit pkgs; });

    defaultPackage = lib.withDefaultSystems (sys: self.packages."${sys}".game);

    packages = lib.withDefaultSystems (sys: let
      pkgs = allPkgs."${sys}";
      stdenv = pkgs.stdenv;
      win64-stdenv = pkgs.pkgsCross.mingwW64.stdenv;
      win32-stdenv = pkgs.pkgsCross.mingw32.stdenv;
    in {
      game = stdenv.mkDerivation {
        name = "game";
        src = ./src;

        buildInputs = with pkgs; [ raylib libGLU glfw mesa xorg.libX11 ];

        buildPhase = "cc main.c card.c player.c gamerender.c input.c ai.c gamemode.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11";

        installPhase = ''
          mkdir -p $out/bin
          cp game $out/bin/game
          cp -r $src/resource $out/bin
        '';    
      };

      web-game = let 
        raylib-web = stdenv.mkDerivation {
          name = "raylib-web";
          src = pkgs.fetchFromGitHub {
            owner = "raysan5";
            repo = "raylib";
            rev = "4.0.0";
            sha256 = "sha256-Z5loBW0V6uOTrmFPSD0s5qyqU+sG6+jCZmh4fHZxX9c=";
            
          };

          phases = [ "unpackPhase" "buildPhase" "installPhase" ];

          buildInputs = with pkgs; [ emscripten ];

          buildPhase = ''
            cd src
            emcc -c rcore.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
            emcc -c rshapes.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
            emcc -c rtextures.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
            emcc -c rtext.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
            emcc -c rmodels.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
            emcc -c utils.c -Os -Wall -DPLATFORM_WEB
            emcc -c raudio.c -Os -Wall -DPLATFORM_WEB

            emar rcs libraylib.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o utils.o raudio.o
          '';

          installPhase = ''
            mkdir -p $out/lib
            mkdir -p $out/includes

            cp libraylib.a $out/lib/libraylib.a
            cp raudio.h $out/includes/raudio.h
            cp raylib.h $out/includes/raylib.h
            cp raymath.h $out/includes/raymath.h
            cp rlgl.h $out/includes/rlgl.h
          '';
        };
      in stdenv.mkDerivation {
        name = "game-web";
        src = ./src;

        buildInputs = with pkgs; [ emscripten raylib-web ];

        buildPhase = ''
          mkdir -p cache
          cp -r ${pkgs.emscripten}/share/emscripten/cache ./cache
          mkdir -p src/resource
          cp -r ${src/resource} src
          export EM_CACHE=cache
          mkdir -p build
          ls src/resource -lah
          emcc  -o build/index.html main.c card.c player.c gamerender.c input.c ai.c gamemode.c -Os -Wall ${raylib-web}/lib/libraylib.a -I ${raylib-web}/includes -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB --embed-file resource@src/resource --shell-file index.html
        '';

        installPhase = ''
          mkdir -p $out
          cp build/* $out
        '';
      };
    });
  };
}
