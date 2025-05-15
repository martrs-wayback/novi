"novi" is the Russian word for "new."  It seemed a fitting
name for a tool that hunts through trees of RPM files in 
search of the newest versions of each product.

This is intended for use with a tree of OS install/update
media: download the updates, determine which files are
newest, remove the old ones, then rebuild the installer's
RPM file list.  Such a process is detailed in this article
that I published on O'Reilly Network:

"Pre-Patched Kickstart Installs"
http://www.linuxdevcenter.com/pub/a/linux/2005/02/17/kickstart_updates.html


TO BUILD:

This is vague (for now), please bear with me.

Novi uses the RPM libraries, which means building Novi requires the full
suite of RPM development's prereq packages.  That includes:

        librpm-4.3.so => /usr/lib/librpm-4.3.so (0x00acc000)
        librpmdb-4.3.so => /usr/lib/librpmdb-4.3.so (0x00f0b000)
        libelf.so.1 => /usr/lib/libelf.so.1 (0x00959000)
        librpmio-4.3.so => /usr/lib/librpmio-4.3.so (0x00cdc000)
        libbeecrypt.so.6 => /usr/lib/libbeecrypt.so.6 (0x00350000)
        libdl.so.2 => /lib/libdl.so.2 (0x0013d000)
        librt.so.1 => /lib/tls/librt.so.1 (0x00c0d000)
        libpthread.so.0 => /lib/tls/libpthread.so.0 (0x00ab3000)
        libz.so.1 => /usr/lib/libz.so.1 (0x00311000)
        libbz2.so.1 => /usr/lib/libbz2.so.1 (0x00111000)
        libpopt.so.0 => /usr/lib/libpopt.so.0 (0x002f6000)
        libselinux.so.1 => /lib/libselinux.so.1 (0x00122000)
        libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x0053c000)
        libm.so.6 => /lib/tls/libm.so.6 (0x00141000)
        libgcc_s.so.1 => /lib/libgcc_s.so.1 (0x00130000)
        libc.so.6 => /lib/tls/libc.so.6 (0x0065f000)
        /lib/ld-linux.so.2 (0x00e14000)

Note that this is a bit of libtool foolishness -- it can't find its special
".la" libraries for some of these (on my system, libbeecrypt) so it
complains.  Building without libtool doesn't have these headaches, as the
standard linker knows when to leave certain dependencies till runtime...

