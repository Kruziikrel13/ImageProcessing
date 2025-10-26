TRACE?=OFF
PROFILE?=OFF
ASAN?=OFF

CONFIGURE=cmake --no-warn-unused-cli -S . -B ./build \
					-DASAN:STRING=${ASAN} -DTRACE:STRING=${TRACE} -DPROFILE:STRING=${PROFILE} \
					-DCMAKE_BUILD_TYPE:STRING
BUILD=cmake --build ./build --target all -j`nproc 2>/dev/null || getconf NPROCESSORS_CONF` --config


stub:
	@echo "Do not run $(MAKE) directly without any arguments."

release:
	$(CONFIGURE)=Release
	$(BUILD) Release

debug:
	$(CONFIGURE)=Debug
	$(BUILD) Debug


.PHONY: clean
clean:
	rm -rf build/

reset:
	git clean -ffdx

all:
	$(MAKE) clean
	$(MAKE) release

nix:
	echo "use nix" > .envrc
	direnv allow
