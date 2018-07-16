die() {
    echo " *** ERROR: " $*
    exit 1

}
set -x

[ $TRAVIS_OS_NAME != linux ] || {

    export PATH=/tmp/arc_gnu_2017.09_prebuilt_elf32_le_linux_install/bin:$PATH || die
    git checkout -- . || die

    cd board/emsk/configs/23 || die
    tcftool arcem7d.tcf -q -x C_defines,arc_core_config.h -x gcc.arg || die
    mv arc_core_config.h gcc.arg ../../../../example/hello/arcgnu || die
    cp ld/linker_gnu.ld ../../../../example/hello/arcgnu || die

    cd ../../../../.travis || die
    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 11 -o $CUR_CORE != arcem6 ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }
    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 22 -o $CUR_CORE != arcem7d ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }

    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 22 -o $CUR_CORE != arcem11d ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }
    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 23 -o $CUR_CORE != arcem7d ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }
    [ $TOOLCHAIN != gnu -o $BOARD != emsk -o $BD_VER != 23 -o $CUR_CORE != arcem11d ] || {

        python3 build.py "TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE}" || die
    }

}
