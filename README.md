paperwallet
===========

Arduino Based Bitcoin Paper Wallet Printer

Demo at http://www.youtube.com/watch?v=noW77GqmNBQ

The sketch compiles is larger than 32,256 bytes so you'll need to either burn it using a programmer (don't forget to disable bootloader on reset)

e.g.

avrdude -v -patmega328p -cusbtiny -U hfuse:w:0xDF:m

Or disable some functionality (e.g. random number verification)
