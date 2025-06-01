**Compile & Install module**
```
$ sudo make
$ sudo insmod ./hello.ko
$ sudo insmod ./kpr.ko
```

**Check if the module is loaded**
```
$ sudo dmesg | grep hello
```
