#!/bin/bash
# -*- bash -*-

function usage
{
    MSG=$1
    
    if [[ ! -z "$MSG" ]] ; then
	echo $MSG
    fi

    echo "usage : $0 <version-#>"
}

VERSION=$1

if [ -z "$VERSION" ] ; then
    usage "Missing version number"
    exit -1
fi

make -f Makefile.mingw clean && make -f Makefile.mingw

# Misc files to include
MISC_CONTENTS="INSTALL.win32 AUTHORS COPYING ChangeLog NEWS README TODO"

# Find dlls
DLL_CONTENTS=$(find . -type f -name '*dll' | xargs echo)

# Create archive
zip --junk-paths pidgin-cmds-$VERSION.zip $MISC_CONTENTS $DLL_CONTENTS
