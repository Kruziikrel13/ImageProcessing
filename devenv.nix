{
  pkgs,
  lib,
  config,
  inputs,
  ...
}:

{
  env = {
    LD_LIBRARY_PATH = "${pkgs.vulkan-loader}/lib:${pkgs.vulkan-validation-layers}/lib";
    VULKAN_SDK = "${pkgs.vulkan-headers}";
    VK_LAYER_PATH = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";
    LSAN_OPTIONS = "suppressions=${./asan.supp}";
  };
  packages = with pkgs; [
    zip
    perf
    flamegraph

    libtiff
    libjpeg
    libpng
    libz

    llvmPackages.openmp
    vulkan-headers
    vulkan-loader
    spdlog

    shaderc
    shader-slang
  ];

  languages = {
    c = {
      enable = true;
      debugger = pkgs.lldb;
    };
    cplusplus.enable = true;
  };

  # https://devenv.sh/languages/
  # languages.rust.enable = true;

  # https://devenv.sh/processes/
  # processes.dev.exec = "${lib.getExe pkgs.watchexec} -n -- ls -la";

  # https://devenv.sh/services/
  # services.postgres.enable = true;

  # https://devenv.sh/scripts/
  scripts.hello.exec = ''
    echo hello from $GREET
  '';

  # https://devenv.sh/basics/
  enterShell = ''
    hello         # Run scripts directly
    git --version # Use packages
  '';

  # https://devenv.sh/tasks/
  # tasks = {
  #   "myproj:setup".exec = "mytool build";
  #   "devenv:enterShell".after = [ "myproj:setup" ];
  # };

  # https://devenv.sh/tests/
  enterTest = ''
    echo "Running tests"
    git --version | grep --color=auto "${pkgs.git.version}"
  '';

  # https://devenv.sh/git-hooks/
  # git-hooks.hooks.shellcheck.enable = true;

  # See full reference at https://devenv.sh/reference/options/
}
