
FROM	ubuntu:groovy
COPY	./bin/*	/img_print/
WORKDIR	/img_print/mnt
RUN	apt-get update \
	&& DEBIAN_FRONTEND=Noninteractive apt-get install -y libvips-dev
ENTRYPOINT	["../img-print"]
