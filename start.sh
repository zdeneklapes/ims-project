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
PROJECT_NAME="bread_factory"
ZIP_NAME="12_xlapes02_xbinov00"
DOCUMENTATION="documentation.pdf"

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
    DIR_BUILD="build"
    if [ -d ${DIR_BUILD} ]; then
        ${RM} ${DIR_BUILD}
    fi
    mkdir ${DIR_BUILD}
    cd ${DIR_BUILD} || error_exit "cd"
    eval "cmake .."
    cd .. || error_exit "cd"
}

function build_make() {
    cd build || error_exit "cd"
    eval "make -j"
    cd .. || error_exit "cd"
}

function run() {
    #    echo "1. Run..." && ./build/$PROJECT_NAME -h
    #    echo "1. Run..." && ./build/$PROJECT_NAME -h
    #    echo "2. Run..." && ./build/$PROJECT_NAME -o out.txt
    #    echo "3. Run..." && ./build/$PROJECT_NAME -mc 10000
    #    echo "4. Run..." && ./build/$PROJECT_NAME -mcap 10000
    #    echo "5. Run..." && ./build/$PROJECT_NAME -oc 10000
    #    echo "6. Run..." && ./build/$PROJECT_NAME -ocap 10000
    #    echo "7. Run..." && ./build/$PROJECT_NAME -fc 10000
    #    echo "8. Run..." && ./build/$PROJECT_NAME -fcap 10000
    ./build/$PROJECT_NAME
}

function run_valgrind() {
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./build/$PROJECT_NAME
}

function clean() {
    ${RM} build
    ${RM} cmake-build**
    ${RM} .cache
    ${RM} *.zip
    ${RM} tags
    ${RM} cscope.out
    ${RM} ${DOCUMENTATION}
}

function download_third_party() {
    DIR_LIBS="third_party"
    if [ -d "${DIR_LIBS}" ]; then
        ${RM} ${DIR_LIBS}
    fi
    mkdir ${DIR_LIBS}
    cd ${DIR_LIBS} || error_exit "cd"
    wget http://www.fit.vutbr.cz/~peringer/SIMLIB/source/simlib-3.09-20221108.tar.gz
    tar xvzf simlib-3.09-20221108.tar.gz
    rm simlib-3.09-20221108.tar.gz
    cd - || error_exit "cd"
}

################################################################################
# DOCKER
################################################################################
DOCKER_CONTAINER_VERSION="0.5"
DOCKER_NAME="clion/remote-cpp-env"
DOCKER_CONATINER_NAME="clion_remote_env"

function rm_docker_images_volumes() {
    docker stop $(docker ps -aq)
    docker system prune -a -f
    docker volume prune -f
}

function docker_stop_remove() {
    docker stop $(docker ps -q) && docker rm clion_remote_env
}

function docker_build() {
    docker build -t "${DOCKER_NAME}:${DOCKER_CONTAINER_VERSION}" -f Dockerfile .
}

function docker_run() {
    docker run -itd --cap-add sys_ptrace -p 127.0.0.1:2222:22 --name ${DOCKER_CONATINER_NAME} -v "$(pwd)":/home/user/project "${DOCKER_NAME}:${DOCKER_CONTAINER_VERSION}"
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

function pack() {
    make -C doc && cp doc/${DOCUMENTATION} .
    #    zip -r ${ZIP_NAME}.zip src CMakeLists.txt README.md doc start.sh ${DOCUMENTATION}
    tar -czvf ${ZIP_NAME}.tar.gz src CMakeLists.txt README.md doc start.sh ${DOCUMENTATION}
}

################################################################################
# MAIN
################################################################################
[[ "$#" -eq 0 ]] && usage && exit 0
while [ "$#" -gt 0 ]; do
    case "$1" in
    '-bc' | '--build-cmake') build_cmake ;;
    '-bm' | '--build-make') build_make ;;
    '-r' | '--run') run ;;
    '--valgrind') run_valgrind ;;
    '-c' | '--clean') clean ;;
    '-p' | '--pack') pack ;;
    '--download-third-party') download_third_party ;;
        #
    '--cloc') count_loc ;;
    '--tags') tags ;;
        #
    '-dc' | '--docker-clean') rm_docker_images_volumes ;;
    '-db' | '--docker-build') docker_build ;;
    '-dr' | '--docker-run') docker_run ;;
    '-dsr' | '--docker-stop-remove-container') docker_stop_remove ;;
        #
    '-h' | '--help' | *) usage ;;
    esac
    shift
done
