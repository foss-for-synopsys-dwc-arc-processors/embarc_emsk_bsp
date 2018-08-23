die() {
    echo " *** ERROR: " $*
    exit 1

}
set -x

[ "$TRAVIS_OS_NAME" != "linux" ] || {

    U_NAME=${U_NAME:=embARC_Bot}
    U_EMAIL=${U_EMAIL:=info@embARC.org}
    git config --global user.name "${U_NAME}"
    git config --global user.email "${U_EMAIL}"

    export PATH=/tmp/arc_gnu_${GNU_VER}_prebuilt_elf32_le_linux_install/bin:$PATH || die
    git checkout -- . || die
    cd .travis || die
    {
    	BUILD_OPTS="BSP_ROOT=${BSP_ROOT} TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE} GNU_VER=${GNU_VER} EXAMPLES=${EXAMPLES}"

        python build.py ${BUILD_OPTS} || die
    }

}
