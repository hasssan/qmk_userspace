# @hasssan's qmk userspace

This is my [External QMK Userspace](https://docs.qmk.fm/newbs_external_userspace) repository.

- Keymap for [Sofle RGB](./keyboards/sofle/keymaps/hasssan/README.md)

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

## License

This repository is licensed under the GPL-2.0-or-later.
See the [LICENSE](./LICENSE) file for more details.
