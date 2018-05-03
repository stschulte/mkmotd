#!/bin/sh

BASEDIR=`dirname "$0"`
SPECFILE="${BASEDIR}/mkmotd.spec"
SOURCEDIR=`readlink -f "${BASEDIR}/.."`
SOURCEDIR_BASENAME=`basename "$SOURCEDIR"`

VERSION=`sed -n "s/^Version:\s*\(.*\)/\1/p" "$SPECFILE"`
TARBALL="${HOME}/rpmbuild/SOURCES/mkmotd-${VERSION}.tar.gz"

[ ! -d "${HOME}/rpmbuild/SOURCES" ] && mkdir -p "${HOME}/rpmbuild/SOURCES"
[ ! -d "${HOME}/rpmbuild/SPECS" ]   && mkdir -p "${HOME}/rpmbuild/SPECS"

echo "Copying spec file"
install -m 0644 "$SPECFILE" "${HOME}/rpmbuild/SPECS/mkmotd.spec"

echo "Building tarball ${TARBALL}"
tar -c -v --exclude='.git*' --exclude=build  -f - . -C "$SOURCEDIR" | gzip -9 > "$TARBALL"

echo "Running rpmbuild"
rpmbuild -ba "${HOME}/rpmbuild/SPECS/mkmotd.spec"
