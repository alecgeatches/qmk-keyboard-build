$srcFolder = "$PSScriptRoot\..\src"
$buildFolder = "$PSScriptRoot\..\qmk_firmware"

# docker run --rm -v ${buildFolder}:"/qmk_firmware" -v ${srcFolder}:"/qmk_firmware/keyboards/ergodox_ez/keymaps/alecg" qmkfm/qmk_firmware `
# 	/bin/sh -c "SKIP_GIT=1 make -j4 ergodox_ez:alecg && cp /qmk_firmware/ergodox_ez_alecg.hex /qmk_firmware/keyboards/ergodox_ez/keymaps/alecg"

docker-compose exec qmk /bin/sh -c "SKIP_GIT=1 make ergodox_ez:alecg && cp /qmk_firmware/ergodox_ez_alecg.hex /qmk_firmware/keyboards/ergodox_ez/keymaps/alecg"
