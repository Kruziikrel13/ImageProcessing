# Disregard this file. This is just a Nix shell definition for automatically creating a development environment and only has use if on the NixOS operating system.
{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    clang-tools
    cmake
    lldb
    valgrind
    perf
    hotspot
    clang-analyzer
    mermaid-cli
    (clang-uml.overrideAttrs rec {
      version = "0.6.2";
      src = fetchFromGitHub {
        owner = "bkryza";
        repo = "clang-uml";
        rev = version;
        hash = "sha256-hGjLOyduTc+yOQhO5gDKNfY0fDvbUfvF0FrdjrDheyw=";
      };
    })

    llvmPackages.openmp

    libtiff
    libjpeg
    libpng
    libz

    vulkan-headers
    spdlog
    shaderc
    shader-slang
  ];

  LD_LIBRARY_PATH = "${pkgs.vulkan-loader}/lib:${pkgs.vulkan-validation-layers}/lib";
  VULKAN_SDK = "${pkgs.vulkan-headers}";
  VK_LAYER_PATH = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";

  LSAN_OPTIONS = "suppressions=${./asan.supp}";
}
