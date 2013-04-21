paperwallet
===========

Arduino Based Bitcoin Paper Wallet Printer

Demo at http://www.youtube.com/watch?v=f7y_emuo68g

The sketch compiles ot exactly 32,768 bytes so you'll need to either burn it using a programmer (don't forget to disable bootloader on reset)

e.g.

avrdude -v -patmega328p -cusbtiny -U hfuse:w:0xDF:m

Or disable some functionality (e.g. uncomment the printing)
