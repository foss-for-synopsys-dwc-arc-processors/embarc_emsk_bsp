die() {
    echo " *** ERROR: " $*
    exit 1

}
set -x

[ $TRAVIS_OS_NAME != linux ] || {

    export PATH=/tmp/arc_gnu_2017.09_prebuilt_elf32_le_linux_install/bin:$PATH || die
    git checkout -- . || die
    cd .travis || die
    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 11 ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER}" || die
    }
    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 22 ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER}" || die
    }

    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 23 ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER}" || die
    }


}
