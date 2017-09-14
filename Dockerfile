FROM ubuntu
WORKDIR /mount
RUN apt-get update \
    && apt-get install -y \
        gcc \
        g++ \
        gcc-avr \
        avr-libc \
        cpputest \
        make \
    && rm -rf /var/lib/apt/lists/*
RUN mkdir /usr/lib/cpputest \
    && ln -s /usr/lib/x86_64-linux-gnu/libCppUTest.a /usr/lib/cpputest/libCppUTest.a \
    && ln -s /usr/lib/x86_64-linux-gnu/libCppUTestExt.a /usr/lib/cpputest/libCppUTestExt.a
ENV CPPUTEST_LIB /usr/lib/cpputest
ENV CPPUTEST_INCLUDE /usr/include    
CMD ["make"]