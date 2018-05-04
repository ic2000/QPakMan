# QPakMan

This is a WIP loader for .pak files.

# How to use

```
  qpakman [OPTION...] files -o output.pak
  qpakman [OPTION...] images -o output.wad
  qpakman [OPTION...] input.{pak,wad} -o dir
```

Options:

```
  -l  --list          List contents of pak/wad file
  -e  --extract       Extract pak/wad contents into output dir
  -m  --maketex       Make a texture wad from bsp files
  -c  --colors=FILE   Load a colour palette from FILE
  -g  --game=GAME     Select game (one of 'quake1', 'quake2', 'hexen2')
  -f  --force         Overwrite existing files when extracting
  -p  --pic           Create pic format images in the wad
  -r  --raw           Do not convert anything
```

# License

This project is licensed under the GNU General Public License version 3, or at
your option, any later version (SPDX code ``GPL-3.0-or-later``). For details,
please see the ``LICENSE`` file.
