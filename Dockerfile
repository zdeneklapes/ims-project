# CLion remote docker environment (How to build docker container, run and stop it)
#
# Build and run:
#   docker build -t clion/remote-cpp-env:0.5 -f Dockerfile.remote-cpp-env .
#   docker run -d --cap-add sys_ptrace -p 127.0.0.1:2222:22 --name clion_remote_env clion/remote-cpp-env:0.5
#   ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:2222"
#
# stop:
#   docker stop clion_remote_env
#
# ssh credentials (test user):
#   user@password

FROM ubuntu:20.04

WORKDIR /home/user/project
RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update \
  && apt-get install -y ssh \
      build-essential \
      gcc \
      g++ \
      gdb \
      clang \
      make \
      cmake \
      ninja-build \
      cmake \
      autoconf \
      automake \
      locales-all \
      dos2unix \
      rsync \
      tar \
      python \
      fish \
    && apt-get clean \
    && ln -s /usr/bin/make /usr/bin/gmake


COPY . .
RUN make -C ./third_party/simlib install \
    && ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test_clion \
    && mkdir /run/sshd \
    && useradd -m user \
    && yes password | passwd user \
    && usermod -s /bin/bash user \
    && yes root | passwd root

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]







#FROM ubuntu:latest
#ARG DEBIAN_FRONTEND=noninteractive
#WORKDIR /app
#COPY . /app
#RUN apt-get -y update  \
#    && apt-get install -y  \
#    && apt-get -y install g++ cmake git \
#    && make -C /app/third_party/simlib install \
#    && chmod +x /app/start.sh
#
#CMD ["./start.sh", "-c", "-b"]
#ENTRYPOINT ["/app/build/simulation"]
