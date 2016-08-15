#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef DEBUG
#include <stdio.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__ );
#else
#define DEBUG_PRINT(...)
#endif

static char *ra_fns[] = {
	"/usr/lib64/ld-2.23.so",
	"/usr/lib/systemd/systemd-bootchart",
	"/usr/lib64/libc-2.23.so",
	"/usr/lib64/libc.so.6",
	"/usr/lib64/libgcc_s.so.1",
	"/usr/lib/systemd/systemd",
	"/usr/lib64/libpthread.so.0",
	"/usr/lib64/libcap.so.2",
	"/usr/lib64/librt.so.1",
	"/usr/lib64/libpam.so.0",
	"/usr/lib64/libkmod.so.2",
	"/usr/lib64/libmount.so.1",
	"/usr/lib64/libdl.so.2",
	"/usr/lib64/libblkid.so.1",
	"/usr/lib64/libuuid.so.1",
	"/usr/lib/systemd/system-generators/systemd-fstab-generator",
	"/usr/lib/systemd/system-generators/systemd-debug-generator",
	"/usr/bin/kmod",
	"/usr/bin/mount",
	"/usr/lib64/libattr.so.1",
	"/usr/lib64/libacl.so.1",
	"/usr/lib/systemd/systemd-random-seed",
	"/usr/lib/systemd/systemd-vconsole-setup",
	"/usr/lib/systemd/systemd-udevd",
	"/usr/lib64/liblz4.so.1",
	"/usr/bin/udevadm",
	"/usr/lib/systemd/systemd-journald",
	"/usr/bin/systemd-tmpfiles",
	"/usr/bin/clr_power",
	"/usr/lib/systemd/systemd-timesyncd",
	"/usr/lib64/libnss_files.so.2",
	"/usr/lib64/libnss_altfiles.so.2",
	"/usr/lib64/libnss_libvirt.so.2",
	"/usr/lib64/libnss_resolve.so.2",
	"/usr/lib64/libm.so.6",
	"/usr/lib64/libutil.so.0",
	"/usr/lib64/libpthread.so.0",
	"/usr/lib64/libdl.so.2",
	"/usr/lib64/libutil.so.1",
	"/usr/lib64/libm.so.6",
	"/var/cache/ldconfig/ld.so.cache",
	"/usr/lib64/libc.so.6",
	"/usr/lib64/libpthread.so.0",
	"/usr/lib64/libdl.so.2",
	"/usr/lib64/libutil.so.1",
	"/usr/lib64/libm.so.6",
	"/usr/lib/python2.7/site.py",
	"/usr/lib/python2.7/site.pyc",
	"/usr/lib/python2.7/os.py",
	"/usr/lib/python2.7/os.pyc",
	"/usr/lib/python2.7/posixpath.py",
	"/usr/lib/python2.7/posixpath.pyc",
	"/usr/lib/python2.7/stat.py",
	"/usr/lib/python2.7/stat.pyc",
	"/usr/lib/python2.7/genericpath.py",
	"/usr/lib/python2.7/genericpath.pyc",
	"/usr/lib/python2.7/warnings.py",
	"/usr/lib/python2.7/warnings.pyc",
	"/usr/lib/python2.7/linecache.py",
	"/usr/lib/python2.7/linecache.pyc",
	"/usr/lib/python2.7/types.py",
	"/usr/lib/python2.7/types.pyc",
	"/usr/lib/python2.7/UserDict.py",
	"/usr/lib/python2.7/UserDict.pyc",
	"/usr/lib/python2.7/_abcoll.py",
	"/usr/lib/python2.7/_abcoll.pyc",
	"/usr/lib/python2.7/abc.py",
	"/usr/lib/python2.7/abc.pyc",
	"/usr/lib/python2.7/_weakrefset.py",
	"/usr/lib/python2.7/_weakrefset.pyc",
	"/usr/lib/python2.7/copy_reg.py",
	"/usr/lib/python2.7/copy_reg.pyc",
	"/usr/lib/python2.7/traceback.py",
	"/usr/lib/python2.7/traceback.pyc",
	"/usr/lib/python2.7/sysconfig.py",
	"/usr/lib/python2.7/sysconfig.pyc",
	"/usr/lib/python2.7/re.py",
	"/usr/lib/python2.7/re.pyc",
	"/usr/lib/python2.7/sre_compile.py",
	"/usr/lib/python2.7/sre_compile.pyc",
	"/usr/lib/python2.7/sre_parse.py",
	"/usr/lib/python2.7/sre_parse.pyc",
	"/usr/lib/python2.7/sre_constants.py",
	"/usr/lib/python2.7/sre_constants.pyc",
	"/usr/lib/python2.7/lib-dynload/_locale.so",
	"/usr/lib/python2.7/_sysconfigdata.py",
	"/usr/lib/python2.7/_sysconfigdata.pyc",
	"/usr/lib/python2.7/encodings/__init__.py",
	"/usr/lib/python2.7/encodings/__init__.pyc",
	"/usr/lib/python2.7/codecs.py",
	"/usr/lib/python2.7/codecs.pyc",
	"/usr/lib/python2.7/encodings/aliases.py",
	"/usr/lib/python2.7/encodings/aliases.pyc",
	"/usr/lib/python2.7/encodings/ascii.py",
	"/usr/lib/python2.7/encodings/ascii.pyc",
	"/usr/bin/waagent",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/agent.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/agent.pyc",
	"/usr/lib/python2.7/subprocess.py",
	"/usr/lib/python2.7/subprocess.pyc",
	"/usr/lib/python2.7/lib-dynload/time.so",
	"/usr/share/zoneinfo/UTC",
	"/usr/lib/python2.7/lib-dynload/select.so",
	"/usr/lib/python2.7/lib-dynload/fcntl.so",
	"/usr/lib/python2.7/pickle.py",
	"/usr/lib/python2.7/pickle.pyc",
	"/usr/lib/python2.7/struct.py",
	"/usr/lib/python2.7/struct.pyc",
	"/usr/lib/python2.7/lib-dynload/_struct.so",
	"/usr/lib/python2.7/lib-dynload/binascii.so",
	"/usr/lib64/libz.so.1",
	"/usr/lib/python2.7/lib-dynload/cStringIO.so",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/metadata.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/metadata.pyc",
	"/usr/lib/python2.7/platform.py",
	"/usr/lib/python2.7/platform.pyc",
	"/usr/lib/python2.7/string.py",
	"/usr/lib/python2.7/string.pyc",
	"/usr/lib/python2.7/lib-dynload/strop.so",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/fileutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/fileutil.pyc",
	"/usr/lib/python2.7/shutil.py",
	"/usr/lib/python2.7/shutil.pyc",
	"/usr/lib/python2.7/fnmatch.py",
	"/usr/lib/python2.7/fnmatch.pyc",
	"/usr/lib/python2.7/collections.py",
	"/usr/lib/python2.7/collections.pyc",
	"/usr/lib/python2.7/lib-dynload/_collections.so",
	"/usr/lib/python2.7/lib-dynload/operator.so",
	"/usr/lib/python2.7/keyword.py",
	"/usr/lib/python2.7/keyword.pyc",
	"/usr/lib/python2.7/heapq.py",
	"/usr/lib/python2.7/heapq.pyc",
	"/usr/lib/python2.7/lib-dynload/itertools.so",
	"/usr/lib/python2.7/lib-dynload/_heapq.so",
	"/usr/lib/python2.7/lib-dynload/grp.so",
	"/usr/lib/python2.7/tempfile.py",
	"/usr/lib/python2.7/tempfile.pyc",
	"/usr/lib/python2.7/io.py",
	"/usr/lib/python2.7/io.pyc",
	"/usr/lib/python2.7/lib-dynload/_io.so",
	"/usr/lib/python2.7/random.py",
	"/usr/lib/python2.7/random.pyc",
	"/usr/lib/python2.7/__future__.py",
	"/usr/lib/python2.7/__future__.pyc",
	"/usr/lib/python2.7/lib-dynload/math.so",
	"/usr/lib/python2.7/hashlib.py",
	"/usr/lib/python2.7/hashlib.pyc",
	"/usr/lib/python2.7/lib-dynload/_hashlib.so",
	"/usr/lib64/libssl.so.1.0.0",
	"/usr/lib64/libcrypto.so.1.0.0",
	"/usr/lib/python2.7/lib-dynload/_random.so",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/logger.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/logger.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/future.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/future.pyc",
	"/usr/lib/python2.7/httplib.py",
	"/usr/lib/python2.7/httplib.pyc",
	"/usr/lib/python2.7/lib-dynload/array.so",
	"/usr/lib/python2.7/socket.py",
	"/usr/lib/python2.7/socket.pyc",
	"/usr/lib/python2.7/lib-dynload/_socket.so",
	"/usr/lib/python2.7/functools.py",
	"/usr/lib/python2.7/functools.pyc",
	"/usr/lib/python2.7/lib-dynload/_functools.so",
	"/usr/lib/python2.7/lib-dynload/_ssl.so",
	"/usr/lib/python2.7/urlparse.py",
	"/usr/lib/python2.7/urlparse.pyc",
	"/usr/lib/python2.7/mimetools.py",
	"/usr/lib/python2.7/mimetools.pyc",
	"/usr/lib/python2.7/rfc822.py",
	"/usr/lib/python2.7/rfc822.pyc",
	"/usr/lib/python2.7/ssl.py",
	"/usr/lib/python2.7/ssl.pyc",
	"/usr/lib/python2.7/textwrap.py",
	"/usr/lib/python2.7/textwrap.pyc",
	"/usr/lib/python2.7/contextlib.py",
	"/usr/lib/python2.7/contextlib.pyc",
	"/usr/lib/python2.7/base64.py",
	"/usr/lib/python2.7/base64.pyc",
	"/usr/lib/python2.7/lib-dynload/datetime.so",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/textutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/textutil.pyc",
	"/usr/lib/python2.7/lib-dynload/crypt.so",
	"/usr/lib64/libcrypt.so.1",
	"/usr/lib/python2.7/xml/__init__.py",
	"/usr/lib/python2.7/xml/__init__.pyc",
	"/usr/lib/python2.7/xml/dom/__init__.py",
	"/usr/lib/python2.7/xml/dom/__init__.pyc",
	"/usr/lib/python2.7/xml/dom/domreg.py",
	"/usr/lib/python2.7/xml/dom/domreg.pyc",
	"/usr/lib/python2.7/xml/dom/minicompat.py",
	"/usr/lib/python2.7/xml/dom/minicompat.pyc",
	"/usr/lib/python2.7/xml/dom/minidom.py",
	"/usr/lib/python2.7/xml/dom/minidom.pyc",
	"/usr/lib/python2.7/xml/dom/xmlbuilder.py",
	"/usr/lib/python2.7/xml/dom/xmlbuilder.pyc",
	"/usr/lib/python2.7/copy.py",
	"/usr/lib/python2.7/copy.pyc",
	"/usr/lib/python2.7/weakref.py",
	"/usr/lib/python2.7/weakref.pyc",
	"/usr/lib/python2.7/xml/dom/NodeFilter.py",
	"/usr/lib/python2.7/xml/dom/NodeFilter.pyc",
	"/usr/lib/python2.7/distutils/__init__.py",
	"/usr/lib/python2.7/distutils/__init__.pyc",
	"/usr/lib/python2.7/distutils/version.py",
	"/usr/lib/python2.7/distutils/version.pyc",
	"/usr/lib/os-release",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/loader.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/loader.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/conf.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/conf.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/exception.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/exception.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/osutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/shellutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/shellutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/cryptutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/cryptutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/daemon.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/daemon.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/event.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/event.pyc",
	"/usr/lib/python2.7/atexit.py",
	"/usr/lib/python2.7/atexit.pyc",
	"/usr/lib/python2.7/json/__init__.py",
	"/usr/lib/python2.7/json/__init__.pyc",
	"/usr/lib/python2.7/json/decoder.py",
	"/usr/lib/python2.7/json/decoder.pyc",
	"/usr/lib/python2.7/json/scanner.py",
	"/usr/lib/python2.7/json/scanner.pyc",
	"/usr/lib/python2.7/lib-dynload/_json.so",
	"/usr/lib/python2.7/json/encoder.py",
	"/usr/lib/python2.7/json/encoder.pyc",
	"/usr/lib/python2.7/threading.py",
	"/usr/lib/python2.7/threading.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/restapi.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/restapi.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/restutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/utils/restutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/init.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/init.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/monitor.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/monitor.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/dhcp.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/dhcp.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/protocolUtil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/protocolUtil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/ovfenv.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/ovfenv.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/wire.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/wire.pyc",
	"/usr/lib/python2.7/xml/sax/__init__.py",
	"/usr/lib/python2.7/xml/sax/__init__.pyc",
	"/usr/lib/python2.7/xml/sax/xmlreader.py",
	"/usr/lib/python2.7/xml/sax/xmlreader.pyc",
	"/usr/lib/python2.7/xml/sax/handler.py",
	"/usr/lib/python2.7/xml/sax/handler.pyc",
	"/usr/lib/python2.7/xml/sax/_exceptions.py",
	"/usr/lib/python2.7/xml/sax/_exceptions.pyc",
	"/usr/lib/python2.7/xml/sax/saxutils.py",
	"/usr/lib/python2.7/xml/sax/saxutils.pyc",
	"/usr/lib/python2.7/urllib.py",
	"/usr/lib/python2.7/urllib.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/metadata.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/protocol/metadata.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/scvmm.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/scvmm.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/env.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/env.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/provision.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/provision.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/resourceDisk.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/resourceDisk.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/extension.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/extension.pyc",
	"/usr/lib/python2.7/zipfile.py",
	"/usr/lib/python2.7/zipfile.pyc",
	"/usr/lib/python2.7/lib-dynload/zlib.so",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/deprovision.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/default/deprovision.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/osutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/provision.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/provision.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/deprovision.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/ubuntu/deprovision.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/redhat/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/redhat/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/redhat/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/redhat/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/redhat/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/redhat/osutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/osutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/deprovision.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/clearlinux/deprovision.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/osutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/deprovision.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/coreos/deprovision.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/suse/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/suse/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/suse/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/suse/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/suse/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/suse/osutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/debian/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/debian/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/debian/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/debian/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/debian/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/debian/osutil.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/__init__.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/__init__.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/distro.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/distro.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/resourceDisk.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/resourceDisk.pyc",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/osutil.py",
	"/usr/lib/python2.7/site-packages/azurelinuxagent/distro/freebsd/osutil.pyc",
	"/usr/share/defaults/waagent/waagent.conf",
	NULL
};


int main(void)
{
	int i, fd;
	struct stat st;

	pid_t pid = fork();

	if (pid == -1) {
		DEBUG_PRINT("fork failed\n");
		execl("/usr/lib/systemd/systemd-bootchart", "systemd-bootchart", NULL);
	} else if (pid > 0 ) {
		execl("/usr/lib/systemd/systemd-bootchart", "systemd-bootchart", NULL);
	} else {
		usleep(10000);
		DEBUG_PRINT("readahead files:\n");
		for (i = 0; ra_fns[i]; i++) {
			DEBUG_PRINT("%s\n", ra_fns[i]);
			fd = open(ra_fns[i], O_RDONLY);
			if (fd < 0) {
				DEBUG_PRINT("open failed to open %s\n", ra_fns[i]);
				continue;
			}
			if (fstat(fd, &st) < 0) {
				DEBUG_PRINT("fstat failed on %s\n", ra_fns[i]);
				close(fd);
				continue;
			}
			if (readahead(fd, 0, st.st_size) < 0) {
				DEBUG_PRINT("readahead failure on %s: %s\n", ra_fns[i], strerror(errno));
			}
			close(fd);
		}
	}

	return 0;
}

