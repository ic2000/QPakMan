# QPakMan 0.1

This is a WIP loader for .pak and .wad files.

# How to use

```
  qpakman [options] files -o output.pak
  qpakman [options] images -o output.wad
  qpakman [options] input.{pak,wad} -o dir
```

Options:

```
  -o, --output=<str>    specify output name/dir
  -l, --list            list contents of pak/wad file
  -e, --extract         extract pak/wad contents into output dir
  -m, --maketex         make a texture wad from bsp files
```

# License

This project is licensed under the GNU General Public License version 3, or at
your option, any later version (SPDX code ``GPL-3.0-or-later``). For details,
please see the ``LICENSE`` file.
