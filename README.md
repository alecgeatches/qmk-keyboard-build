# qmk-keyboard-build

Source and Windows build tools for compiling and flashing a custom `alecg` ErgoDox keymap.

## Installing

```bash
$ git clone git@github.com:alecgeatches/qmk-keyboard-build.git
$ git clone git@github.com:qmk/qmk_firmware.git qmk-keyboard-build/qmk_firmware
$ cd qmk-keyboard-build

# Run qmk Docker container
# $ docker-compose up

# To build keymap (PowerShell)
$ .\tools\qbuild.ps1

# To flash keyboard (PowerShell)
$ .\tools\qflash.ps1
```
