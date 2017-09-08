#!/bin/sh

#
# actual build script
# most of the steps are ported from the aranym.spec file
#
export BUILDROOT="${PWD}/.travis/tmp"
export OUT="${PWD}/.travis/out"

mkdir -p "${BUILDROOT}"
mkdir -p "${OUT}"

unset CC CXX

prefix=/usr
bindir=$prefix/bin
datadir=$prefix/share
icondir=$datadir/icons/hicolor

if test "$suse_version" -ge 1200; then
	with_nfosmesa=--enable-nfosmesa
fi
common_opts="--prefix=$prefix --enable-addressing=direct --enable-usbhost --disable-sdl2 $with_nfosmesa"

VERSION=`sed -n -e 's/#define.*VER_MAJOR.*\([0-9][0-9]*\).*$/\1./p
s/#define.*VER_MINOR.*\([0-9][0.9]*\).*$/\1./p
s/#define.*VER_MICRO.*\([0-9][0-9]*\).*$/\1/p' src/include/version.h | tr -d '\n'`

NO_CONFIGURE=1 ./autogen.sh

export VERSION

isrelease=false
ATAG=${VERSION}${archive_tag}
tag=`git tag --points-at ${TRAVIS_COMMIT}`
case $tag in
	ARANYM_*)
		isrelease=true
		;;
	*)
		ATAG=${VERSION}${archive_tag}-${SHORT_ID}
		;;
esac

export isrelease

case $CPU_TYPE in
	i[3456]86 | x86_64 | arm*) build_jit=true ;;
	*) build_jit=false ;;
esac

case "$TRAVIS_OS_NAME" in
linux)
	./configure $common_opts || exit 1
	make depend
	make || exit 1
	
	make DESTDIR="$BUILDROOT" install-strip || exit 1
	sudo chown root "$BUILDROOT${bindir}/aratapif"
	sudo chgrp root "$BUILDROOT${bindir}/aratapif"
	sudo chmod 4755 "$BUILDROOT${bindir}/aratapif"

	ARCHIVE="${PROJECT_LOWER}-${ATAG}.tar.xz"
	(
	cd "${BUILDROOT}"
	tar cvfJ "${OUT}/${ARCHIVE}" .
	)
	
	(
		export top_srcdir=`pwd`
		cd appimage
		BINTRAY_USER=aranym BINTRAY_REPO=aranym-files ./build.sh
	)
		
	;;

osx)
	DMG="${PROJECT_LOWER}-${VERSION}${archive_tag}.dmg"
	ARCHIVE="${PROJECT_LOWER}-${ATAG}.dmg"
	(
	cd src/Unix/MacOSX
	xcodebuild -derivedDataPath "$OUT" -project MacAranym.xcodeproj -configuration Release -scheme Packaging 
	)
	mv "$OUT/Build/Products/Release/$DMG" "$OUT/$ARCHIVE" || exit 1
	;;

esac

export ARCHIVE

if $isrelease; then
	make dist
	for ext in gz bz2 xz lz; do
		SRCARCHIVE="${PROJECT_LOWER}-${VERSION}.tar.${ext}"
		test -f "${SRCARCHIVE}" && mv "${SRCARCHIVE}" "$OUT"
	done
fi
