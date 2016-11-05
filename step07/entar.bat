tar cvf - README VERSION *.h *.c *.lst *.obj myboard.* entar.bat c.bat burn.bat erase.bat | gzip >%1.tgz
tar cvf - VERSION myboard.hex | gzip >%1.a.tgz
tar cvf - myboard.hex | gzip >%1.b.tgz
