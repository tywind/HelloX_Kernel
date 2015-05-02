del hcnimge.bin
del master.bin
process -i master.dll -o master.bin
append -s realinit.bin -a miniker.bin -b 2000 -o image_1.bin
append -s image_1.bin -a master.bin -b 12000 -o image_2.bin
ren image_2.bin hcnimge.bin
del image_1.bin
