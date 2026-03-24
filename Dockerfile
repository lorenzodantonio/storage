FROM gcc:latest AS core_builder
COPY . /usr/src/storage
WORKDIR /usr/src/storage

FROM core_builder AS builder
RUN make build

FROM core_builder AS tester
RUN apt-get update && apt-get install -y lcov
CMD ["make", "test"]

FROM debian:bookworm-slim
WORKDIR /root/
COPY --from=builder /usr/src/storage/storage .
CMD ["./storage"]
