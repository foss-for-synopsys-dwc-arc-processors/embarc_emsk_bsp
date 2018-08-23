die() {

	echo " *** ERROR: " $*

	exit 1

}
#set -x

[ $TRAVIS_OS_NAME != linux ] || {
    if [ "$STATUS" != "" ] && [ "$NAME" != "" ] ; then
        bash -c "$STATUS" pending "Local $NAME testing is in progress" || \
        die "Not able to post status to github, did you set EMBARC_BOT variable in travis ci setting page"
    fi

    sudo apt-get update || die
    sudo apt-get install lib32z1 || die
    sudo apt-get install dos2unix || die
    pip install --upgrade pip || die
    pip install PrettyTable || die
    pip install colorama || die
    pip install configparser || die
}
