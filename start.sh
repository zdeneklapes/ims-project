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
# HELPER
################################################################################
function error_exit() {
    printf "${RED}ERROR: $1${NC}\n"
    usage
    exit 1
}

################################################################################
# PROJECT
################################################################################
function build_cmake() {
    if [ ! -d "build/" ]; then mkdir build; fi
    eval "cmake .."
    cd .. || error_exit "cd"
}

function build_make() {
    cd build || error_exit "cd"
    eval "make -j"
    cd .. || error_exit "cd"
}

function run() {
    ./build/$PROJECT_NAME
}

function clean() {
    ${RM} build
    ${RM} cmake-build-debug
    ${RM} cmake-build-debug-docker
    ${RM} cmake-build-debug-remote-host
    ${RM} .cache
    ${RM} *.zip
    ${RM} tags
    ${RM} cscope.out
}

function zip_project() {
    echo "TODO"
}

################################################################################
# DOCKER
################################################################################
function rm_docker_images_volumes() {
    docker stop $(docker ps -aq)
    docker system prune -a -f
    docker volume prune -f
}

function docker_stop() {
    docker stop $(docker ps -q) && docker rm clion_remote_env
}

function docker_build() {
    docker build -t clion/remote-cpp-env:0.5 -f Dockerfile .
}

function docker_run() {
    docker run -d --cap-add sys_ptrace -p 127.0.0.1:2222:22 --name clion_remote_env clion/remote-cpp-env:0.5
}

################################################################################
# OTHERS
################################################################################
function usage() {
    echo "USAGE:
    '-b' | '--build') build ;;
    '-r' | '--run') run ;;
    '-c' | '--clean') clean ;;
    '-z' | '--zip') zip_project ;;
        #
    '--cloc') count_loc ;;
    '--tags') tags ;;
        #
    '-dc' | '--docker-clean') rm_docker_images_volumes ;;
    '-db' | '--docker-build') docker_build ;;
    '-dr' | '--docker-run') docker_run ;;
    '-ds' | '--docker-stop') docker_stop ;;
        #
    '-h' | '--help' | *) usage ;;
"
}

function count_loc() {
    cloc src/**/*.{cpp,hpp,h}
}

function tags() {
    ctags -R .
    cscope -Rb
}

function ssh() {
    scp "$(pwd)/${ZIP_NAME}.zip" $1@eva.fit.vutbr.cz:/homes/eva/xl/$1
}

function ssh() {
    scp "$(pwd)/${ZIP_NAME}.zip" $1@eva.fit.vutbr.cz:/homes/eva/xl/$1
}


################################################################################
# MAIN
################################################################################
[[ "$#" -eq 0 ]] && usage && exit 0
while [ "$#" -gt 0 ]; do
    case "$1" in
    '-bc' | '--build-cmake') build ;;
    '-bs' | '--build-make') build ;;
    '-r' | '--run') run ;;
    '-c' | '--clean') clean ;;
    '-z' | '--zip') zip_project ;;
        #
    '--cloc') count_loc ;;
    '--tags') tags ;;
        #
    '-dc' | '--docker-clean') rm_docker_images_volumes ;;
    '-db' | '--docker-build') docker_build ;;
    '-dr' | '--docker-run') docker_run ;;
    '-ds' | '--docker-stop') docker_stop ;;
        #
    '-h' | '--help' | *) usage ;;
    esac
    shift
done
