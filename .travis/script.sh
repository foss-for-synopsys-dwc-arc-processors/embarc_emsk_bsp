die() {
    echo " *** ERROR: " $*
    exit 1

}
set -x

[ $TRAVIS_OS_NAME != linux ] || {

    export PATH=/tmp/arc_gnu_${GNU_VER}_prebuilt_elf32_le_linux_install/bin:$PATH || die
    git checkout -- . || die
    cd .travis || die
    {

        python3 build.py "BSP_ROOT=${BSP_ROOT} TOOLCHAIN=${TOOLCHAIN} BOARD=${BOARD} BD_VER=${BD_VER} CUR_CORE=${CUR_CORE} GNU_VER=${GNU_VER}" || die
    }







}
