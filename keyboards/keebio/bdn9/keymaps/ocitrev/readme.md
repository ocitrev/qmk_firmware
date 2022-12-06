# ocitrev's layout for keebio BDN9

| Vol +/-              | Hue +/-      | Brightness +/-       |
|:--------------------:|:------------:|:--------------------:|
| `CTRL`+`SHIFT`+`ESC` | `F13`        | Toggle RGB           |
| Settings Layer       | `CTRL`+`F19` | `CTRL`+`F20`         |
| `CTRL`+`WIN`+`LEFT`  | `CTRL`+`K`   | `CTRL`+`WIN`+`RIGHT` |

|                | Saturation +/- |                |
|:--------------:|:--------------:|:--------------:|
| `QK_BOOT`      | `F16`          |                |
|                | `F17`          |                |
| Media Prev     | `F18`          | Media Next     |

### Install MSYS2 MINGW64
```
winget install msys2.msys2
```

### Add to Terminal
```
{
    "name": "MSYS2 MINGW64",
    "commandline": "C:/msys64/usr/bin/env.exe MSYS=enable_pcon MSYSTEM=MINGW64 /bin/bash --login",
    "guid": "{bbf3857f-9971-4b2c-8ca8-0d52bf543735}",
    "icon": "C:/msys64/mingw64.ico"
}
```

### Setup MINGW64 to build qmk
```
pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-python-qmk
```

### Setup qmk
```
qmk setup -H "$USERPROFILE/source/repos/qmk_firmware" ocitrev/qmk_firmware
qmk config user.keymap=ocitrev
qmk config user.keyboard=keebio/bdn9/rev2
```

