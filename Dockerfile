FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
WORKDIR /app
COPY . /app
RUN apt-get -y update  \
    && apt-get install -y  \
    && apt-get -y install g++ cmake git \
    && make -C /app/third_party/simlib install \
    && chmod +x /app/start.sh

CMD ["./start.sh", "-c", "-b"]
ENTRYPOINT ["/app/build/simulation"]
