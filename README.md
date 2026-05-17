# QMK Userspace

## Layout

This userspace currently contains a personal Cantor keymap based on Mark Stosberg's 3x5+1 layout, with local changes for macOS, programming, media controls, Mouseless, and Russian typing.

The base layer keeps letters on the main 3x5 columns, with the extra outer keys used for Tab, one-shot Option, one-shot Shift, Delete, one-shot AltGr, and one-shot Func. The thumb clusters provide one-shot Ctrl, Cmd/Enter, Lower/Tab, Raise/Backspace, Space, and one-shot Shift.

Layer highlights:

- Lower: numbers, shifted number symbols, brackets, braces, punctuation, and colon.
- Raise: navigation, editing keys, brightness controls, media controls, volume, and Mouseless trigger (`Raise+I` toggles mouseless.click).
- Func: function keys, Caps Lock, copy/paste-style shortcuts, RGB toggle, and macOS lock screen.
- Mouse: mouse movement/buttons are defined, but there is currently no base-layer keybinding to enter this layer.
- Russian: a Unicode-based Russian typing layer with a custom physical layout.

Russian layer layout:

```text
й ц у к е н    г ш щ з х ъ
Alt ф ы в а п  р о л д ж э
Shift я ч с м и  т ь б ю , '
```

Shifted Russian behavior:

- Russian letters emit uppercase variants when Shift is active.
- `,` emits `.` when shifted.
- `'` emits `"` when shifted.

Russian mode is toggled in QMK with `Cmd+Space`. This shortcut is consumed by the firmware and does not switch the macOS input source.

For the Russian layer to work on macOS, enable and select the `Unicode Hex Input` input source:

1. Open System Settings.
1. Go to Keyboard.
1. Under Text Input, click Edit.
1. Add `Unicode Hex Input` from Other.
1. Keep `Unicode Hex Input` selected while using the keyboard.

The firmware emits Russian characters using QMK Unicode Map. If macOS is using a normal input source instead of `Unicode Hex Input`, Russian characters will appear as Option-symbol sequences such as `º¢£...`.

Build and flash:

```sh
make
make flash
```

`make flash` runs:

```sh
dfu-util -a 0 -s 0x08000000:leave -D cantor_alexeypegov.bin
```

## QMK Userspace Template

This is a template repository which allows for an external set of QMK keymaps to be defined and compiled. This is useful for users who want to maintain their own keymaps without having to fork the [main QMK repository](https://github.com/qmk/qmk_firmware). You must still fork the main QMK repository if writing firmware for a *new* keyboard.

## Howto configure your build targets

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. Enable userspace in QMK config using `qmk config user.overlay_dir="$(realpath qmk_userspace)"`
1. Add a new keymap for your board using `qmk new-keymap`
    * This will create a new keymap in the `keyboards` directory, in the same location that would normally be used in the main QMK repository. For example, if you wanted to add a keymap for the Planck, it will be created in `keyboards/planck/keymaps/<your keymap name>`
    * You can also create a new keymap using `qmk new-keymap -kb <your_keyboard> -km <your_keymap>`
    * Alternatively, add your keymap manually by placing it in the location specified above.
    * `layouts/<layout name>/<your keymap name>/keymap.*` is also supported if you prefer the layout system
1. Add your keymap(s) to the build by running `qmk userspace-add -kb <your_keyboard> -km <your_keymap>`
    * This will automatically update your `qmk.json` file
    * Corresponding `qmk userspace-remove -kb <your_keyboard> -km <your_keymap>` will delete it
    * Listing the build targets can be done with `qmk userspace-list`
1. Commit your changes

## Howto build with GitHub

1. In the GitHub Actions tab, enable workflows
1. Push your changes above to your forked GitHub repository
1. Look at the GitHub Actions for a new actions run
1. Wait for the actions run to complete
1. Inspect the Releases tab on your repository for the latest firmware build

## Howto build locally

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. `cd` into this repository's clone directory
1. Set global userspace path: `qmk config user.overlay_dir="$(realpath .)"` -- you MUST be located in the cloned userspace location for this to work correctly
    * This will be automatically detected if you've `cd`ed into your userspace repository, but the above makes your userspace available regardless of your shell location.
1. Compile normally: `qmk compile -kb your_keyboard -km your_keymap` or `make your_keyboard:your_keymap`

Alternatively, if you configured your build targets above, you can use `qmk userspace-compile` to build all of your userspace targets at once.

## Extra info

If you wish to point GitHub actions to a different repository, a different branch, or even a different keymap name, you can modify `.github/workflows/build_binaries.yml` to suit your needs.

To override the `build` job, you can change the following parameters to use a different QMK repository or branch:
```
    with:
      qmk_repo: qmk/qmk_firmware
      qmk_ref: master
```

If you wish to manually manage `qmk_firmware` using git within the userspace repository, you can add `qmk_firmware` as a submodule in the userspace directory instead. GitHub Actions will automatically use the submodule at the pinned revision if it exists, otherwise it will use the default latest revision of `qmk_firmware` from the main repository.

This can also be used to control which fork is used, though only upstream `qmk_firmware` will have support for external userspace until other manufacturers update their forks.

1. (First time only) `git submodule add https://github.com/qmk/qmk_firmware.git`
1. (To update) `git submodule update --init --recursive`
1. Commit your changes to your userspace repository
