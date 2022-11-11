#!/bin/bash
complete -c timedatectl -s h -l help -d 'Print a short help text and exit'

################################################################################
# GLOBAL VARIABLES
################################################################################
# Color
RM="rm -rfd"
RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'

# Project
PROJECT_NAME="simulation"
ZIP_NAME="xbinov00-xlapes02"

################################################################################
# FUNCTIONS
################################################################################
function usage() {
    echo "USAGE:"
    echo "
    '-b' | '--build') build ;;
    '-r' | '--run') run ;;
    '-c' | '--clean') clean ;;
    '-z' | '--zip') zip_project ;;
    '-sz' | '--ssh-zdenek') ssh 'xlapes02';;
    '-sa' | '--ssh-andrej') ssh 'xbinov00';;
    '-h' | '--help' | *) usage ;;
	"
}

function error_exit() {
    printf "${RED}ERROR: $1${NC}\n"
    usage
    exit 1
}

function build() {
    if [ ! -d "build/" ]; then mkdir build; fi
    cd build || error_exit "cd"
    eval "cmake .."
    eval "make -j"
    cd .. || error_exit "cd"
}

function run() {
    ./build/$PROJECT_NAME
}

function clean() {
    ${RM} build
    ${RM} cmake-build-debug
    ${RM} .cache
    ${RM} *.zip
    ${RM} tags
    ${RM} cscope.out
}

function zip_project() {
    echo "TODO"
}

function ssh() {
	scp "$(pwd)/${ZIP_NAME}.zip" $1@eva.fit.vutbr.cz:/homes/eva/xl/$1
}

function count_loc() {
	cloc src/**/*.{cpp,hpp,h}
}

function tags() {
	ctags -R .
	cscope -Rb
}

################################################################################
# MAIN
################################################################################
[[ "$#" -eq 0 ]] && usage && exit 0
while [ "$#" -gt 0 ]; do
    case "$1" in
    '-b'  | '--build'		) build ;;
    '-r'  | '--run'			) run ;;
    '-c'  | '--clean'		) clean ;;
    '-z'  | '--zip'			) zip_project ;;
    '--cloc'              	) count_loc ;;
    '--tags'              	) tags ;;
    '-h'  | '--help' | *	) usage ;;
    esac
    shift
done
