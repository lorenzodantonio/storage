FROM gcc:latest AS builder
COPY . /usr/src/storage
WORKDIR /usr/src/storage
RUN make build

FROM builder AS tester
RUN apt-get update && apt-get install -y lcov
RUN make test

FROM debian:bookworm-slim
WORKDIR /root/
COPY --from=builder /usr/src/storage/storage .
CMD ["./storage"]
