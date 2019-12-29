# Work in Motion

Experimental screensaver for [Haiku OS](https://haiku-os.org) made for the Google Code-In 2019 competition.

## Usage

- Compile the screensaver using the `Makefile` in the source directory.

`cd src`

`make`

- Copy the file to your screensaver folder.

`cp objects.x86_64-cc7-release/Work\ In\ Motion /boot/system/non-packaged/add-ons/Screen\ Savers`

Make sure to adjust the input directory according to the architecture that you're 
currently using. The `ls` command can help.

## Contributing

I tried to pay attention to making a clean codebase, in order to encourage people to 
experiment with it as well, due to the somewhat limited amount of resources regarding 
screensavers in BeOS/Haiku that are available online.

There are things that could be worked on, so I'll encourage pull requests.

### Installer script

A small installer script for x86_64 builds has been included. This was meant for personal use, but was included here for convenience.

### Alternative source

An alternative version of the source file of the screen saver has been included in the [alternate_src](alternate_src) directory. The code should not be considered as functional or 
representative of my work, but it contains a couple of (mostly commented out) experiments 
that I'd like to archive.

## License

This program has been distributed under the MIT license. Please consult 
[LICENSE](LICENSE) for more information.
