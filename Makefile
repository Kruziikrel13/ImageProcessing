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

staging: all
	rm -rf staging
	mkdir -p staging/source

	@echo "Copying binaries to staging/"
	cp build/{parallel,serial} staging
	cp -r build/shaders staging/

	@echo "Copying source files to staging/source/"
	cp CMakeLists.txt Makefile README.md VERSION .clang-format .clang-tidy staging/source/
	cp -r src/ include/ cmake/ shaders/ staging/source/

	@echo "Creating test archives"
	cp -r test staging/

staging-archive:
	@echo Have you remembered to include the report PDF in staging prior to archiving?
	@if [ ! -d staging ]; then \
		$(MAKE) staging; \
	fi
	zip -rv staging.zip staging

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
