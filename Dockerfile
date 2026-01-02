
FROM ubuntu:22.04 AS builder


RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app

COPY . .

RUN mkdir build && cd build \
    && cmake .. \
    && make

FROM ubuntu:22.04

WORKDIR /app

COPY --from=builder /app/build/Project_Aegis .

COPY --from=builder /app/data ./data
COPY --from=builder /app/outputFiles ./outputFiles
