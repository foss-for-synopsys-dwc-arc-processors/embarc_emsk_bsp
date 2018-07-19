die() {
    echo " *** ERROR: " $*
    exit 1

}
set -x

[ $TRAVIS_OS_NAME != linux ] || {

    export PATH=/tmp/arc_gnu_2017.09_prebuilt_elf32_le_linux_install/bin:$PATH || die
    git checkout -- . || die
    cd .travis || die
    [ $BSP_ROOT != . -o $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 11 -o $CUR_CORE != arcem6 ] || {

        python3 build.py "BSP_ROOT=${BSP_ROOT} TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }
    [ $BSP_ROOT != . -o $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 22 -o $CUR_CORE != arcem7d ] || {

        python3 build.py "BSP_ROOT=${BSP_ROOT} TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }

    [ $BSP_ROOT != . -o $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 22 -o $CUR_CORE != arcem11d ] || {

        python3 build.py "BSP_ROOT=${BSP_ROOT} TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }
    [ $BSP_ROOT != . -o $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 23 -o $CUR_CORE != arcem7d ] || {

        python3 build.py "BSP_ROOT=${BSP_ROOT} TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }
    [ $BSP_ROOT != . -o $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 23 -o $CUR_CORE != arcem11d ] || {

        python3 build.py "BSP_ROOT=${BSP_ROOT} TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }


}
