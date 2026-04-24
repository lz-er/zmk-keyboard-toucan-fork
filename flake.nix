{
  description = "ZMK firmware for the beekeeb Toucan split keyboard (local build, no GitHub Actions)";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    zmk-nix = {
      url = "github:lilyinstarlight/zmk-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, zmk-nix }: let
    forAllSystems = nixpkgs.lib.genAttrs (nixpkgs.lib.attrNames zmk-nix.packages);
  in {
    packages = forAllSystems (system: let
      pkgs = nixpkgs.legacyPackages.${system};
      zmk  = zmk-nix.legacyPackages.${system};

      # Only ship files that affect the firmware so Nix's content hash
      # doesn't churn on every random edit.
      src = nixpkgs.lib.sourceFilesBySuffices self [
        ".board" ".cmake" ".conf" ".defconfig" ".dts" ".dtsi" ".json"
        ".keymap" ".overlay" ".shield" ".yml" "_defconfig"
        ".c" ".h"
      ];

      board = "seeeduino_xiao_ble";

      # Hash of all `west update` deps from config/west.yml.
      # If this ever needs to change (e.g. west.yml updated), Nix will
      # tell you the new value as `got: sha256-...`.
      zephyrDepsHash = "sha256-vWkof2b17gLgKemffXlEbNKU2qerX2b+ylp0l5lh/xk=";

      common = {
        inherit src board zephyrDepsHash;
        meta = {
          description = "Toucan ZMK firmware";
          license     = nixpkgs.lib.licenses.mit;
          platforms   = nixpkgs.lib.platforms.all;
        };
      };

      # Each side uses a different shield list, so build them as plain
      # keyboards and bundle the .uf2s ourselves (rather than using
      # buildSplitKeyboard's `%PART%` template, which can't express that).
      left = zmk.buildKeyboard (common // {
        name            = "toucan-left";
        shield          = "toucan_left rgbled_adapter nice_view_gem";
        enableZmkStudio = true;
      });

      right = zmk.buildKeyboard (common // {
        name   = "toucan-right";
        shield = "toucan_right rgbled_adapter";
      });

      reset = zmk.buildKeyboard (common // {
        name   = "toucan-reset";
        shield = "settings_reset";
      });

      # `firmware.parts` is what zmk-nix's flasher uses to know which
      # files (zmk_<part>.uf2) it can flash.
      firmware = pkgs.runCommand "toucan-firmware" {
        parts = [ "left" "right" "reset" ];
        passthru = { inherit left right reset; };
      } ''
        mkdir $out
        ln -s ${left}/zmk.uf2  $out/zmk_left.uf2
        ln -s ${right}/zmk.uf2 $out/zmk_right.uf2
        ln -s ${reset}/zmk.uf2 $out/zmk_reset.uf2
      '';
    in {
      default = firmware;
      inherit firmware left right reset;

      # Generic flasher script bound to our firmware bundle.
      flash = zmk.packages.flash.override or
              zmk-nix.packages.${system}.flash.override
              { inherit firmware; };
    });

    devShells = forAllSystems (system: {
      default = zmk-nix.devShells.${system}.default;
    });
  };
}
