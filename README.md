# Sofle Keymap

This is my [Quantum Mechanical Keyboard (QMK)](https://docs.qmk.fm/) keymap for Sofle keyboard. This repo works as an [External QMK Userspace](https://docs.qmk.fm/newbs_external_userspace).

The base layer is [Hands Down Promethium (Inverted) Layout](https://www.reddit.com/r/KeyboardLayouts/comments/1g66ivi/hands_down_promethium_snth_meets_hd_silverengram/).

To see full visualization, use [Keymap Drawer](https://keymap-drawer.streamlit.app/) with the [sofle_rev1_hasssan.json](./keyboards/sofle/keymaps/hasssan/assets/sofle_rev1_hasssan.json).

## Installation
1. Set up your QMK environment by following the [QMK documentation](https://docs.qmk.fm/#/newbs/getting_started).
1. Clone this repository.
1. Set this repository as overlay
   ```bash
   qmk config user.overlay_dir="$(realpath qmk_userspace)"
   ```
1. Compile the keymap
   ```bash
   qmk compile -kb sofle/rev1 -km hasssan
   ```

## Credits

- Heavily inspired by [getreuer/qmk-keymap](https://github.com/getreuer/qmk-keymap/).
- Original [Sofle default keymap](https://github.com/qmk/qmk_firmware/blob/master/keyboards/sofle/keymaps/default/keymap.c)
