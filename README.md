# OSM RDMSR playground

--

Ein einfacher Programmrahmen. Ihnen zur Hilfe um Ihren Tutoren die Unterschiede zwischen Kernel- und Usermode zu demonstrieren (auf Linux 3+).

In `rdmsr.h` ist ein direkter Aufruf der privilegierten x86_64-Instruktion [**R**ea**d** **M**odel **S**pecific **R**egister](https://www.felixcloutier.com/x86/RDMSR.html) mithilfe von Inline-Assembler vordefiniert. Dort finden Sie auch einige Beispiele für interessante Registernummern, die Sie mithilfe von `__assembly_rdmsr` auslesen können und Wege um die Ergebnisse zu prüfen.

Es müssen die Kernel-Header, ein C-Compiler und `make` installiert sein. Auf Debian-basierenden Linux-Distributionen hierzu folgendes ausführen:

	sudo apt-get install build-essential linux-headers-`uname -r`

Beim Aufruf von `make` werden folgende Dateien erzeugt:

* `user_rdmsr`: Ein im Userspace ausführbares Programm.
* `kernel_rdmsr.ko`: Ein nachladbares Kernelmodul (vergleichbar mit einem Gerätetreiber).

## Sicherheitshinweise

Damit das Kernelmodul gebaut werden kann, darf der Pfad zu Ihrem Quelltext keine Leer- oder Sonderzeichen enthalten.

> [!CAUTION]
> Führen Sie Ihren Kernelcode nicht auf Ihrem Produktivsystem aus. Nutzen Sie lieber eine VM!

Moderne Linux-Systeme versuchen einfache Fehler (*Oops*) abzufangen. Sie können dies (temporär) deaktivieren:

	sudo sh -c 'echo 1 > /proc/sys/kernel/panic_on_oops'

### Cheat-Sheet

| Kommando                          | Bedeutung                                         |
|-----------------------------------|---------------------------------------------------|
| `sudo insmod kernel_rdmsr.ko`     | Kernelmodul laden                                 |
| `sudo rmmod kernel_rdmsr`         | Kernelmodul entfernen (ohne `.ko`!)               |
| `lsmod`                           | Geladene Kernelmodule auflisten                   |
| `dmesg`                           | Kernelausgaben anzeigen (z.B. `printk`)           |
| `sudo dmesg -c`                   | Neue Ausgaben seit dem letzten `-c` Aufruf zeigen |
| `make CFLAGS=-g clean user_rdmsr` | Debugsymbole für `gdb` einfügen (Userspace)       |

### Ergebnis

Kernel Mode:

```text
[ 2847.523440] Hello, kernel space!
[ 2847.523921] value at 139 = 1005022347264
[ 2847.524430] value at 3221225603 = 0
[ 2847.524874] value at 16 = 8820310975045
[ 2849.530066] Goodbye, kernel space!
```

User Mode:

Programm bricht mit "Segmentation fault" ab.

```text
[ 2852.578787] traps: user_rdmsr[10373] general protection fault ip:560a59ff5158 sp:7ffde488e150 error:0 in user_rdmsr[1158,560a59ff5000+1000]
```
