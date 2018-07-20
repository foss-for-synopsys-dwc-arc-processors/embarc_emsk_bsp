die() {

	echo " *** ERROR: " $*

	exit 1 

}
set -x 

[ $TRAVIS_OS_NAME != linux ] || {

    sudo apt-get update || die 
    sudo apt-get install lib32z1 || die
    sudo apt-get install dos2unix || die
    sudo apt-get install python3-pip
    wget https://pypi.python.org/packages/source/P/PrettyTable/prettytable-0.7.2.tar.gz || die
    tar xzf prettytable-0.7.2.tar.gz || die
    cd prettytable-0.7.2 || die
    python setup.py build || die
    python setup.py install || die
}
