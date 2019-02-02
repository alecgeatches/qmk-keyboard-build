$srcFolder = "${PWD}\src"
$buildFolder = "${PWD}\qmk_firmware"

# Run container and build firmware
docker run --rm -v ${buildFolder}:"/qmk_firmware" -v ${srcFolder}:"/qmk_firmware/keyboards/ergodox_ez/keymaps/alecg" qmkfm/qmk_firmware `
	/bin/sh -c "make ergodox_ez:alecg && cp /qmk_firmware/ergodox_ez_alecg.hex /qmk_firmware/keyboards/ergodox_ez/keymaps/alecg"
