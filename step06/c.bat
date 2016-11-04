call c51env
rm *.obj stdout
c51 uart.c ip sb cd wl(2) rom(large) small pl(24575) >>stdout
c51 main.c ip sb cd wl(2) rom(large) small pl(24575) >>stdout
bl51 @myboard.lnk >>stdout
oh51 myboard >>stdout
grep COMPLETE stdout
burn -RE myboard.hex
